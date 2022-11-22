/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:00:02 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/22 18:43:56 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

// A l'etape n, on a besoin de lire fd[n][0] et d'ecrire dans
// fd[n + 1][1]. Cette fonction ferme tous les autres pipes
// Renvoie -1 en cas d'erreur
int	close_pipes(t_infos *infos, int n)
{
	int	i;
	int	exno;

	exno = 0;
	i = -1;
	while (++i < infos->ac - 1)
	{
		if ((i != n) && (i != n + 1)
			&& close((infos->fd)[i][0]) == -1
			&& close((infos->fd)[i][1]) == -1)
			exno = -1;
		if (i == n && close((infos->fd)[i][1]) == -1
			&& close((infos->fd)[i + 1][0]) == -1)
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
	return (free_tab((void **) cmdopts, -1));
}

void	exec_process(t_infos *infos, int i)
{
	char	**cmdopts;

	cmdopts = get_cmd_split(infos, i);
	if (!cmdopts)
		free_infos(infos, -5);
	infos->pids[i] = fork();
	if (infos->pids[i] == 0)
	{
		close_pipes(infos, i);
		if (dup2(infos->fd[i][0], STDIN_FILENO) == -1
			|| dup2(infos->fd[i + 1][1], STDOUT_FILENO) == -1)
			free_tab((void **) cmdopts, -1);
		// if (close(infos->fd[i][0]) == - 1
		// 	|| close(infos->fd[i + 1][1]) == -1)
		// 	free_tab((void **) cmdopts, -1);
		if (!cmdopts)
			free_infos(infos, -6);
		if (execve(cmdopts[0], cmdopts, infos->ev) == -1)
		{
			free_tab((void **) cmdopts, -1);
			free_infos(infos, -6);
		}
	}
	free_tab((void **) cmdopts, -1);
}

int	main(int ac, char **av, char **ev)
{
	int		i;
	t_infos	*infos;

	i = 0;
	infos = get_infos(ac, av, ev);
	if (dup2(infos->infile, STDIN_FILENO) == -1)
		free_infos(infos, -6);
	if (close(infos->infile) == -1)
		free_infos(infos, -7);
	while (++i < infos->ac - 1)
		exec_process(infos, i);
	i = 0;
	while (++i < infos->ac - 1)
		waitpid(infos->pids[i], NULL, 0);
	
	char	buff[1000];
	buff[999] = 0;
	read(infos->fd[infos->ac - 1][0], buff, 999);
	write(2, buff, 999);
	return (0);
}

