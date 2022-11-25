/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:16:38 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/24 22:09:03 by lkrief           ###   ########.fr       */
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
# include "../ft_printf/includes/ft_printf.h"

# ifndef PROCESS_NUM
#  define PROCESS_NUM 1000
# endif

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
char	**get_paths(char **ev);
int		get_pipes(t_infos *infos);
t_infos	*get_infos(int ac, char **av, char **ev);

//pipex.c
//int		close_pipes(t_infos *infos, int n);

//utils.c
void	print_infos(t_infos *infos);
#endif