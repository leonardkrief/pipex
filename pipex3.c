/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:00:02 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/22 04:38:48 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

void	*err_out(const char *str, void *to_be_free)
{
	if (to_be_free)
		free(to_be_free);
	perror(str);
	exit (-1);
}

void	*err_out_struct(t_infos *infos, int exno, int n)
{
	return (NULL);
}

char	**get_paths(char **ev)
{
	int		i;

	i = -1;
	if (ev)
	{
		while (ev[++i])
		{
			if (ft_strnstr(ev[i], "PATH=", 5) == ev[i])
				return (ft_split(ev[i] + 5, ':'));
		}
	}
	return (NULL);
}

void	*free_pipes(int **fd, int i)
{
	int	n;

	if (fd)
	{
		n = -1;
		while (++n < i)
		{
			if (fd[i])
			{
				if (close(fd[i][0]) == -1 || close(fd[i][1]) == -1)
					perror("Error while closing pipes");
				free(fd[i]);
			}
		}
	}
}

int	**get_pipes(int ac)
{
	int	i;
	int	**fd;

	fd = malloc(sizeof(*fd) * (ac - 2));
	if (fd == NULL)
		return (NULL);
	i = -1;
	while (++i < ac - 2)
	{
		fd[i] = malloc(sizeof(**fd) * 2);
		if (fd[i] == NULL)
			return(free_pipes(fd, i));
		if (pipe(fd[i]) == -1)
			free_pipes(fd, i);
	}
	return (fd);
}

char	*valid_cmd(char **paths, char	*cmd)
{
	int		i;
	char	*candidate;
	char	*tmp;

	i = -1;
	if (access(cmd, F_OK && X_OK) == 0)
		return (ft_strdup(cmd));
	if (paths)
	{
 		while (paths[++i])
		{
			tmp = ft_strjoin(paths[i], "/");
			candidate = ft_strjoin(tmp, cmd);
			if (tmp)
				free(tmp);
			if (access(candidate, F_OK && X_OK) == 0)
				return (candidate);
			if (candidate)
				free(candidate);
		}
	}
	return (NULL);
}

// cmdopts = ft_split(av[i])
// paths = get_paths(ev);
void	exec_from_to(int fd[2], char **cmdopts, char **paths, char **ev)
{
	int		err;
	char	*cmd;

	if (cmdopts)
	{
		cmd = valid_cmd(paths, cmdopts[0]);
		if (!cmd)
			err_out("Unvalid command", NULL);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			err_out("Duplication stdin failed", NULL);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			err_out("Duplication stdout failed", NULL);
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
			err_out("Closing files failed", NULL);
		err = execve(cmd, cmdopts, ev);
		if (err == -1)
			err_out("Failed exec", NULL);
	}
	else
		err_out("No cmd opts", NULL);
}

t_infos	*get_infos(int ac, char **av, char **ev)
{
	t_infos *infos;
	int		fd[ac - 2][2];
	
	infos = malloc(sizeof(*infos));
	if (!infos)
		return (NULL);
	infos->ac = ac;
	infos->av = av;
	infos->ev = ev;
	infos->paths = get_paths(ev);
	if (infos->paths == NULL)
		err_out_struct(infos, 0);
	infos->infile = open(av[1], O_RDONLY);
	if (infos->infile == -1)
		err_out_struct(infos, 1);
	infos->outfile = open(av[ac - 1], O_RDWR | O_CREAT, 0644);
	if (infos->outfile == -1)
		err_out_struct(infos, 2);
	infos->fd = get_pipes(ac);
	if (infos->fd == NULL)
		err_out_struct(infos, 3);
	return (infos);
}

void	print_infos(t_infos *infos)
{
	int	i;

	i = -1;
	printf("ac = %d\n", infos->ac);
	printf("av = ");
	while (infos->av[++i])
		printf("%s ", infos->av[i]);
	printf("\n");
	i = -1;
	// printf("ev = ");
	// while (infos->ev[++i])
	// 	printf("%s ", infos->ev[i]);
	// i = -1;
	printf("paths = ");
	while (infos->paths[++i])
		printf("%s ", infos->paths[i]);
	printf("\n");
	printf("infile = %d\n", infos->infile);
	printf("outfile = %d\n", infos->outfile);
	i = -1;
	while (++i < ((infos->ac - 2)))
		printf("fd[%d] = %d %d\n", i, (infos->fd)[i][0], (infos->fd)[i][1]);
}

int main(int ac, char **av, char **ev)
{
	t_infos	*infos;

	infos = get_infos(ac, av, ev);
	print_infos(infos);
}