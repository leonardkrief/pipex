/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:00:02 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/23 06:37:47 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

// si n >= 0, ferme tous les pipes sauf fd[n][0] et fd[n + 1][1]
// si n < 0,  ferme tous les pipes sauf le read du dernier
// renvoie -1 en cas d'erreur
int	close_pipes(t_infos *infos, int n)
{
	int	i;
	int	exno;

	exno = 0;
	i = -1;
	printf("Closing fds %d, errno= %d : %s\n", n, errno, strerror(errno));
	if (n >= 0)
	{
		while (++i < infos->ac - 2)
		{
			if (i != n && close((infos->fd)[i][0]) == -1)
				exno = -1;
			else
				printf("Closed fd[%d][%d], errno= %d : %s\n", i, 0, errno, strerror(errno));
			if (i != n + 1 && close((infos->fd)[i][1]) == -1)
				exno = -1;
			else
				printf("Closed fd[%d][%d], errno= %d : %s\n", i, 1, errno, strerror(errno));
		}
		return (exno);
	}
	while (++i < infos->ac - 2)
	{
		if (i < (infos->ac - 3) && close((infos->fd)[i][0]) == -1)
			exno = -1;
		if (close((infos->fd)[i][1]) == -1)
			exno = -1;
	}
	return (exno);
}

// recupere dans un split la commande de argv[n] avec ses options
// et verifie que la commande existe. Renvoie NULL en cas d'erreur
char	**get_cmd_split(t_infos *infos, int n)
{
	int		i;
	char	*cmd;
	char	**cmdopts;

	cmdopts = ft_split(infos->av[n], ' ');
	if (!cmdopts)
		return (NULL);
	if (!access(cmdopts[0], F_OK) && !access(cmdopts[0], X_OK))
		return (cmdopts);
	i = -1;
	cmd = ft_strdup(cmdopts[0]);
	while (cmd && infos->paths[++i])
	{
		if (cmdopts[0])
			free(cmdopts[0]);
		cmdopts[0] = ft_strjoin(infos->paths[i], cmd);
		if (!access(cmdopts[0], F_OK) && !access(cmdopts[0], X_OK))
		{
			free(cmd);
			return (cmdopts);
		}
	}
	if (cmd)
		free(cmd);
	return (free_tab(cmdopts, -1));
}

void	exec_process(t_infos *infos, int i)
{
	char	**cmdopts;

	printf("While n°%d about to process, errno = %d:%s\n", i, errno, strerror(errno));
	cmdopts = get_cmd_split(infos, i + 2);
	printf("Got cmd n° %d, errno = %d:%s\n", i, errno, strerror(errno));
	if (!cmdopts)
		free_infos(infos, -5, "Invalid command or malloc failed");
	printf("(%d) about to fork, errno = %d:%s\n", i, errno, strerror(errno));
	infos->pids[i] = fork();
	if (infos->pids[i] < 0)
		free_infos(infos, -6, "Forking failed");
	if (infos->pids[i] == 0)
	{
		close_pipes(infos, 0);
		printf("(%d) pipes closed, errno = %d:%s\n", i, errno, strerror(errno));
		if (dup2(infos->fd[i][0], STDIN_FILENO) == -1
			|| dup2(infos->fd[i + 1][1], STDOUT_FILENO) == -1)
			free_tab(cmdopts, -1);
		if (close(infos->fd[i][0]) == - 1
			|| close(infos->fd[i + 1][1]) == -1)
			free_tab(cmdopts, -1);
		if (!cmdopts)
			free_infos(infos, -7, "Failed dup or close fd");
		printf("(%d) about to exec, errno = %d:%s\n", i, errno, strerror(errno));
		if (execve(cmdopts[0], cmdopts, infos->ev) == -1)
		{
			free_tab(cmdopts, -1);
			free_infos(infos, -8, "Failed exec");
		}
	}
	if (cmdopts)
		free_tab(cmdopts, -1);
}

int	main(int ac, char **av, char **ev)
{
	int		i;
	t_infos	*infos;

	infos = get_infos(ac, av, ev);
	// if (close(infos->infile) == -1)
	// 	free_infos(infos, -7, "Failed closing file descriptor");
	i = 1;
	while (++i < infos->ac - 1)
		exec_process(infos, i - 2);
	if (dup2(infos->infile, STDIN_FILENO) == -1)
		free_infos(infos, -7, "Failed duping file descriptor");
	if (dup2(infos->outfile, (infos->fd)[infos->ac - 3][1]) == -1)
		free_infos(infos, -7, "Failed duping file descriptor");
	
	while (++i < infos->ac - 1)
		waitpid(infos->pids[i], NULL, 0);
	//printf("%s", strerror(errno));
	return (0);
}

