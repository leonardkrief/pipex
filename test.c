/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:31:37 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/19 18:59:59 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
	int	i;
	int	j;
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		i = 0;
		close(fd[0]);
		while (1)
		{
			printf("Child process sent: %d\n", i);
			if(write(fd[1], &i, sizeof(i)) == -1)
				return 3;
			i++;
			usleep(5000);
			printf("Child process sleeps for %.3f secs\n", 5000./1000000.);
		}
		close (fd[1]);
	}
	else
	{
		j = 0;
		close (fd[1]);
		do
		{
			kill(pid, SIGCONT);
			printf("Parent process allows pid = %d\n", pid);
			if (read(fd[0], &j, sizeof(j)) == -1)
				return 2;
			printf("Parent process received: %d\n", j);
			kill(pid, SIGSTOP);
			printf("Parent process stops pid = %d\n", pid);
		} while (j < 5);
		close(fd[0]);
	}
}
