/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexshort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:00:02 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/23 05:04:43 by lkrief           ###   ########.fr       */
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
			read(pipes[i][0], &x, sizeof(x));
			printf("(%d): Received %d\n", i, x);
			x++;
			write(pipes[i + 1][1], &x, sizeof(x));
			printf("(%d): Sent %d\n", i, x);
			close(pipes[i][0]);
			close(pipes[i + 1][1]);
			return 0;
		}
	}


	x = 11;

	write(pipes[0][1], &x, sizeof(x));
	printf("Main process sent %d\n", x);
	x++;
	read(pipes[nb][0], &x, sizeof(x));
	printf("Final result is %d\n", x);

	j = -1;
	while(++j < nb + 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}
	
	i = -1;
	while (++i < nb)
		wait(NULL);
}

