/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:16:38 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/26 19:14:33 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <errno.h>

# define PROCESS_NUM 1024

typedef struct s_infos{
	int		ac;
	char	**av;
	char	**ev;
	char	**paths;
	int		infile;
	int		outfile;
	int		fd[PROCESS_NUM][2];
	pid_t	pids[PROCESS_NUM];
}	t_infos;

//t_infos.c
void	*free_tab(char **to_be_free, int n);
void	free_infos(t_infos *infos, int exno, char *str);
void	free_tab_infos(char **cmdopts, t_infos *infos, int exno, char *str);
char	**get_paths(char **ev);
int		get_pipes(t_infos *infos);
t_infos	*get_infos(int ac, char **av, char **ev);

//pipex.c
int		close_pipes(t_infos *infos, int n);
char	**get_cmd_split(t_infos *infos, int n);
void	exec_cmd(t_infos *infos, char **cmdopts, int i);
void	exec_process(t_infos *infos, int i);

#endif