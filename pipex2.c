/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:00:02 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/22 02:15:02 by lkrief           ###   ########.fr       */
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

void	*err_out_fd(int *fd[][2], int n)
{
	int	i;

	i = 0;
	while (++i < n)
	{
		if (close((*fd)[i][0] == -1 && close((*fd)[i][1] == -1)))
			err_out("Failed to close", NULL);
	}
	exit (-1);
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

void	pipe_from_to(int infile, int outfile, char **cmdopts, char **ev)
{
	int		i;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		err_out("Forking failed", NULL);
	if (pid == 0)
		exec_from_to((*fd)[i], *cmdopts, paths, ev);
	if (close((*fd)[i][0]) == -1)
		err_out("Closing file failed", NULL);
	waitpid(pid, NULL, 0);
	(*fd)[0][0]++;
	(*cmdopts)++;
	if ((*fd)[0][0] < (*fd)[0][1] - 1)
		pipe_from_to(fd, cmdopts, paths, ev);
}

int	main(int ac, char **av, char **ev)
{
	int		a;
	int		i;
	int		fd[ac][2];
	pid_t	pid[ac - 2];
	
	if (ac >= 4)
	{
		fd[0][0] = 0;
		fd[0][1] = ac;
		while (++fd[0][0] < ac - 1)
		{
			if (pipe(fd[fd[0][0]]) == -1)
				err_out_fd(&fd, fd[0][0] - 1);
		}
		fd[0][0] = 1;
		fd[ac - 1][0] = open(av[1], O_RDONLY);
		fd[ac - 1][1] = open(av[ac - 1], O_RDWR | O_CREAT, 0644);
		char **paths = get_paths(ev);
		av++;
		pipe_from_to(&fd, &av, paths, ev);
	}
}

