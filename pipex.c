/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:00:02 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/26 20:32:41 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

// si n >= 0, ferme tous les pipes sauf fd[n - 1][0] et fd[n][1]
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
// Ex: si argv[n] = "ls -la -s", cmdopts = {"\usr\bin\ls", "-la", "-s"}
char	**get_cmd_split(t_infos *infos, int n)
{
	int		i;
	char	*cmd;
	char	**cmdopts;

	cmdopts = ft_split(infos->av[n], ' ');
	if (!cmdopts)
		return (NULL);
	if (access(cmdopts[0], F_OK | X_OK) == 0)
		return (cmdopts);
	i = -1;
	cmd = ft_strdup(cmdopts[0]);
	while (cmd && infos->paths[++i])
	{
		if (cmdopts[0])
			free(cmdopts[0]);
		cmdopts[0] = ft_strjoin(infos->paths[i], cmd);
		if (access(cmdopts[0], F_OK | X_OK) == 0)
		{
			free(cmd);
			return (cmdopts);
		}
	}
	if (cmd)
		free(cmd);
	return (free_tab(cmdopts, -1));
}

void	exec_cmd(t_infos *infos, char **cmdopts, int i)
{
	int	in;
	int	out;
	
	in = infos->infile;
	if (i > 0)
		in = infos->fd[i - 1][0];
	out = infos->outfile;
	if (i < infos->ac - 4)
		 out = infos->fd[i][1];
	fprintf(stderr, "(%d) check cmd exist : %s\n", i, cmdopts[0]);
	if (access(cmdopts[0], F_OK) != 0)
		free_tab_infos(cmdopts, infos, 1, NULL);
	fprintf(stderr, "(%d) check cmd exec\n", i);
	if (access(cmdopts[0], X_OK) != 0)
		free_tab_infos(cmdopts, infos, 2, NULL);
	fprintf(stderr, "(%d) cmd exist + exec\n", i);
	if (close_pipes(infos, i) == -1)
		free_tab_infos(cmdopts, infos, -4, "Failed closing pipes");
	if (dup2(in, STDIN_FILENO) == -1)
		free_tab_infos(cmdopts, infos, -4, "Failed duping file");
	if (close(in) == -1)
		free_tab_infos(cmdopts, infos, -4, "Failed closing file");
	if (dup2(out, STDOUT_FILENO) == -1)
		free_tab_infos(cmdopts, infos, -4, "Failed duping file");
	if (close(out) == -1)
		free_tab_infos(cmdopts, infos, -4, "Failed closing file");
	fprintf(stderr, "(%d) about to exec", i);
	if (execve(cmdopts[0], cmdopts, infos->ev) == -1)
		free_tab_infos(cmdopts, infos, -4, "ejkvlewji");
	// faut il free_infos avant l'exec ??
}

void	exec_process(t_infos *infos, int i)
{
	char	**cmdopts;

	cmdopts = get_cmd_split(infos, i + 2);
	infos->pids[i] = fork();
	if (infos->pids[i] < 0)
		free_infos(infos, -6, "Forking failed");
	if (infos->pids[i] == 0)
	{
		
		if (i == 0)
		{
			if (access(infos->av[1], F_OK) != 0)
				free_tab_infos(cmdopts, infos, 2, NULL);
			if (access(infos->av[1], R_OK) != 0)
				free_tab_infos(cmdopts, infos, 3, NULL);
			infos->infile = open(infos->av[1], O_RDONLY);
			if (infos->infile == -1)
				free_tab_infos(cmdopts, infos, -4, NULL);
		}
		if (i == infos->ac - 4)
		{
			if (access(infos->av[infos->ac - 1], F_OK) == 0
				&& access(infos->av[infos->ac - 1], W_OK) != 0)
				free_tab_infos(cmdopts, infos, 3, NULL);
			infos->outfile = open(infos->av[infos->ac - 1], O_WRONLY | O_CREAT, 0644);
			if (infos->outfile == -1)
				free_tab_infos(cmdopts, infos, -4, NULL);
		}
		exec_cmd(infos, cmdopts, i);
	}
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
		if (close_pipes(infos, -1) == -1)
			free_infos(infos, -7, "Failed closing some pipes");
		i = -1;
		while (++i < infos->ac - 3)
			waitpid(infos->pids[i], NULL, 0);
		// if (close(infos->infile) == -1)
		// 	free_infos(infos, -7, "Failed closing file descriptor");
		// if (close(infos->outfile) == -1)
		// 	free_infos(infos, -7, "Failed closing file descriptor");
		free_infos(infos, 0, NULL);
		return (0);
	}
}
