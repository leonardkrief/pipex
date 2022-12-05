/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:00:02 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/05 19:28:09 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
	i = -1;
	cmd = ft_strdup(cmdopts[0]);
	if (!cmd)
		return (free_tab(cmdopts, -1));
	while (cmd && cmd[0] != '/' && infos->paths[++i])
	{
		free(cmdopts[0]);
		cmdopts[0] = ft_strjoin(infos->paths[i], cmd);
		if (!cmdopts[0])
			return (free_tab_str(cmdopts, cmd));
		if (access(cmdopts[0], F_OK | X_OK) == 0)
			free(cmd);
		if (access(cmdopts[0], F_OK | X_OK) == 0)
			return (cmdopts);
	}
	free(cmdopts[0]);
	cmdopts[0] = cmd;
	return (cmdopts);
}

void	exec_cmd(t_infos *infos, char **cmdopts, int i)
{
	infos->in = infos->infile;
	if (i > 0)
		infos->in = infos->fd[i - 1][0];
	infos->out = infos->fd[i][1];
	if (i == infos->ac - 4)
		infos->out = infos->outfile;
	if (ft_strchr(cmdopts[0], '/') && access(cmdopts[0], F_OK) != 0)
		free_tab_infos(cmdopts, infos, 12, cmdopts[0]);
	else if (!ft_strchr(cmdopts[0], '/'))
		free_tab_infos(cmdopts, infos, 11, NULL);
	if (access(cmdopts[0], X_OK) != 0)
		free_tab_infos(cmdopts, infos, 12, NULL);
	if (dup2(infos->in, STDIN_FILENO) == -1)
		free_tab_infos(cmdopts, infos, 16, "Dup infile");
	if (close(infos->in) == -1)
		free_tab_infos(cmdopts, infos, 16, "Infile");
	if (dup2(infos->out, STDOUT_FILENO) == -1)
		free_tab_infos(cmdopts, infos, 27, "Dup outfile");
	if (close(infos->out) == -1)
		free_tab_infos(cmdopts, infos, 27, "Outfile");
	if (close_pipes(infos, i) == -1)
		free_tab_infos(cmdopts, infos, -4, "Pipes");
	execve(cmdopts[0], cmdopts, infos->ev);
	free_tab_infos(cmdopts, infos, -4, "Exec");
}

void	check_in_n_out(char **cmdopts, t_infos *infos, int i)
{
	if (i == 0)
	{
		if (access(infos->av[1], F_OK) != 0)
			free_tab_infos(cmdopts, infos, 2, infos->av[1]);
		if (access(infos->av[1], R_OK) != 0)
			free_tab_infos(cmdopts, infos, 5, infos->av[1]);
		infos->infile = open(infos->av[1], O_RDONLY);
		if (infos->infile == -1)
			free_tab_infos(cmdopts, infos, 10, NULL);
	}
	if (i == infos->ac - 4)
	{
		if (access(infos->av[infos->ac - 1], F_OK) == 0
			&& access(infos->av[infos->ac - 1], W_OK) != 0)
			free_tab_infos(cmdopts, infos, 5, infos->av[infos->ac - 1]);
		infos->outfile = open(infos->av[infos->ac - 1], \
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (infos->outfile == -1)
			free_tab_infos(cmdopts, infos, -4, NULL);
	}
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
		if (!cmdopts)
			free_tab_infos(cmdopts, infos, -4, "Malloc failed");
		check_in_n_out(cmdopts, infos, i);
		exec_cmd(infos, cmdopts, i);
	}
	if (cmdopts)
		free_tab(cmdopts, -1);
}

int	main(int ac, char **av, char **ev)
{
	int		i;
	t_infos	*infos;

	if (ac >= 5)
	{
		infos = get_infos(ac, av, ev);
		if (!infos)
			exit(-1);
		if (infos->here_doc)
			here_doc(infos, av[2], NULL);
		i = 1;
		infos->i = &i;
		while (++i < infos->ac - 1)
			exec_process(infos, i - 2);
		if (close_pipes(infos, -1) == -1)
			free_infos(infos, -7, "Failed closing some pipes");
		i = -1;
		while (++i < infos->ac - 3)
			waitpid(infos->pids[i], NULL, 0);
		if (infos->here_doc)
			unlink("here_doc");
		free_infos(infos, 0, NULL);
		return (0);
	}
}
