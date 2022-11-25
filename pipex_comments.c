/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_comments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:00:02 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/25 14:09:27 by lkrief           ###   ########.fr       */
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
	if (n >= 0)
	{
		while (++i < infos->ac - 4)
		{
			if (i != n - 1 && close((infos->fd)[i][0]) == -1)
				exno = -1;
			if (i != n && close((infos->fd)[i][1]) == -1)
				exno = -1;
		}
		return (exno);
	}
	while (++i < infos->ac - 4)
	{
		if (close((infos->fd)[i][0]) == -1)
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
	if (!access(cmdopts[0], F_OK | X_OK))
		return (cmdopts);
	i = -1;
	cmd = ft_strdup(cmdopts[0]);
	while (cmd && infos->paths[++i])
	{
		if (cmdopts[0])
			free(cmdopts[0]);
		cmdopts[0] = ft_strjoin(infos->paths[i], cmd);
		if (!access(cmdopts[0], F_OK | X_OK))
		{
			free(cmd);
			return (cmdopts);
		}
	}
	if (cmd)
		free(cmd);
	return (free_tab(cmdopts, -1));
}
// set follow-fork-mode child
// run tests/infile1 cat tests/outfile1
void	exec_process(t_infos *infos, int i)
{
	char	**cmdopts;

	cmdopts = get_cmd_split(infos, i + 2);
	if (!cmdopts)
		free_infos(infos, -5, "Invalid command or malloc failed");
	infos->pids[i] = fork();
	if (infos->pids[i] < 0)
		free_infos(infos, -6, "Forking failed");
	if (infos->pids[i] == 0)
	{
		if (close_pipes(infos, i) == -1)
			fprintf(stderr, "(%d)Error closing files\n", i);
		if (i == 0)
		{
			if (dup2(infos->infile, STDIN_FILENO) == -1)
				fprintf(stderr, "(%d)Failed dupping infile to stdin\n", i);
			if (close(infos->infile) == -1)
				fprintf(stderr, "(%d)Failed closing infile\n", i);
		}
		else
		{
			if (dup2(infos->fd[i - 1][0], STDIN_FILENO) == -1)
				fprintf(stderr, "(%d)Dupped fd[%d][0] to stdin\n", i, i - 1);
			if (close(infos->fd[i - 1][0]))
				fprintf(stderr, "(%d)Failed closing fd[%d][0]\n", i, i - 1);
		}
		if (i == infos->ac - 4)
		{
			dup2(infos->outfile, STDOUT_FILENO);
			close(infos->outfile);
			fprintf(stderr, "(%d)Dupped outfile to stdout\n", i);
		}
		else
		{
			dup2(infos->fd[i][1], STDOUT_FILENO);
			close(infos->fd[i][1]);
			fprintf(stderr, "(%d)Dupped fd[%d][1] to stdout\n", i, i);
		}
		fprintf(stderr, "(%d)Process about to exec: %s\n\n", i, cmdopts[0]);
		execve(cmdopts[0], cmdopts, infos->ev);
		fprintf(stderr, "(%d)Process failed to exec\n", i);
		free_tab(cmdopts, -1);
		free_infos(infos, -8, "Failed exec");
	}
	if (cmdopts)
		free_tab(cmdopts, -1);
}

int	main(int ac, char **av, char **ev)
{
	int		i;
	t_infos	*infos;

	if (ac >= 4)
	{
		infos = get_infos(ac, av, ev);

		i = 1;
		while (++i < infos->ac - 1)
			exec_process(infos, i - 2);
		close_pipes(infos, -1);
		
		i = -1;
		while (++i < infos->ac - 3)
		{
			waitpid(infos->pids[i], NULL, 0);
			fprintf(stderr, "(%d) terminated\n", i);
		}
		// if (close(infos->infile) == -1)
		// 	free_infos(infos, -7, "Failed closing file descriptor");
		// if (close(infos->outfile) == -1)
		// 	free_infos(infos, -7, "Failed closing file descriptor");

		free_infos(infos, 0, NULL);
		return (0);
	}
}
