/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexshort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:00:02 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/23 05:16:44 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

int	main(int ac, char **av, char **ev)
{
	int		i;
	int		j;
	int		x;
	int		nb = atoi(av[1]);
	pid_t	pids[100];
	int		pipes[100][2];
	char buff[1000];

	i = -1;
	while (++i < nb + 1)
	{
		if (pipe(pipes[i]) == -1)
			return (-1);
	}

	i = -1;
	while (++i < nb)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (-2);
		if (pids[i] == 0)
		{
			j = -1;
			while(++j < nb + 1)
			{
				if (i != j)
					close(pipes[j][0]);
				if (i + 1 != j)
					close(pipes[j][1]);
			}
			read(pipes[i][0], buff, 100);
			printf("(%d): Received\n", i);
			x++;
			write(pipes[i + 1][1], buff , 100);
			printf("(%d): Sent\n", i);
			close(pipes[i][0]);
			close(pipes[i + 1][1]);
			return 0;
		}
	}
	int fd = open("tests/infile1", O_RDONLY);
	read(fd, buff, 999);
	buff[100] = 0;
	write(pipes[0][1], buff, 100);
	printf("Main process sent %s\n", buff);
	read(pipes[nb][0], buff, 100);
	printf("Final result is %s\n", buff);

	j = -1;
	while(++j < nb + 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}

	i = -1;
	while (++i < nb)
		waitpid(pids[i], NULL, 0);
}

