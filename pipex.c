/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:00:02 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/20 16:17:48 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

void	*err_out(const char *str, void *to_be_free, void *value)
{
	if (to_be_free)
		free(to_be_free);
	perror(str);
	return (value);
}

char	*whereis(const char *cmd, char **environ)
{
	int		fd[2];
	pid_t	pid;
	char	*output;
	char	*vect[] = {"/usr/bin/whereis", (char *)cmd, NULL};

	if (pipe(fd) == -1)
		return (err_out("Piping failed", NULL, NULL));
	pid = fork();
	// faut il proteger le fork ?
	if (pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (err_out("Duplication failed", NULL, NULL));
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
			return (err_out("Close failed", NULL, NULL));
		execve("/usr/bin/whereis", vect, environ);
	}
	waitpid(pid, NULL, 0);
	output = get_next_line(fd[0]);
	if (close(fd[0]) == -1 || close(fd[1]) == -1)
		return (err_out("Close failed", output, NULL));
	return (output);
}

char	*pathname(const char *cmd, char **environ)
{
	int		i;
	char	*output;
	char	*tmp;
	char	**stock;

	output = whereis(cmd, environ);
	tmp = ft_strtrim(output, cmd);
	if (output)
		free(output);
	output = ft_strtrim(tmp, ":");
	if (tmp)
		free(tmp);
	stock = ft_split(output, ' ');
	if (output)
		free(output);
	if (stock)
	{
		output = ft_strdup(stock[0]);
		i = -1;
		while (stock[++i])
			free(stock[i]);
		free(stock);
	}
	return (output);
}
int	main(int argc, char **argv, char **environ)
{
	char	*path;

	path = pathname(argv[1], environ);
	printf("%s", path);
	// char *vect[] = {"/bin/ls", ".", NULL};
	// execve("/bin/ls", vect, environ);
}
