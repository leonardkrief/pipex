/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z2.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:00:02 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/24 21:28:57 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

int	main(int ac, char **av, char **ev)
{
	int		i;
	char	*cmdopts1[2] = {"/usr/bin/cat", NULL};
	char	*cmdopts2[3] = {"/usr/bin/grep", "monchef", NULL};
	int		pipes[2];
	pid_t	pids[2];
	int		fd1;
	int		fd2;

	pipe(pipes);

	fd1 = open("infile", O_RDONLY);
	fd2 = open("outfile", O_WRONLY);

	pids[0] = fork();
	if (pids[0] == 0)
	{
		close(pipes[0]);
		dup2(fd1, STDIN_FILENO);
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[1]);
		perror("p1");
		execve(cmdopts1[0], cmdopts1, ev);
		perror("exec1");
		return (0);
	}

	pids[1] = fork();
	if (pids[1] == 0)
	{
		close(pipes[1]);
		dup2(pipes[0], STDIN_FILENO);
		dup2(fd2, STDOUT_FILENO);
		close(pipes[0]);
		perror("p2");
		execve(cmdopts2[0], cmdopts2, ev);
		perror("exec1");
		return 0;
	}

	close(pipes[0]);

	close(fd1);
	close(fd2);
	
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);

}