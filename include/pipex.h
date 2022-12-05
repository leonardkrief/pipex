/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:16:38 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/05 19:32:28 by lkrief           ###   ########.fr       */
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
# include <errno.h>
# include "../libft/libft.h"

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
	int		here_doc;
	int		*i;
	int		in;
	int		out;
}	t_infos;

//water.c
void	*free_tab(char **to_be_free, int n);
void	free_infos(t_infos *infos, int exno, char *str);
void	*free_tab_str(char **to_be_free, char *str);
void	free_tab_infos(char **cmdopts, t_infos *infos, int exno, char *str);

//bread.c
int		get_pipes(t_infos *infos);
char	**get_paths(char **ev);
t_infos	*get_infos(int ac, char **av, char **ev);
int		close_pipes(t_infos *infos, int n);
void	here_doc(t_infos *infos, char *LIMITER, char *next_line);

//pipex.c
char	**get_cmd_split(t_infos *infos, int n);
void	check_in_n_out(char **cmdopts, t_infos *infos, int i);
void	exec_cmd(t_infos *infos, char **cmdopts, int i);
void	exec_process(t_infos *infos, int i);

#endif