/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:00:02 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/20 17:13:53 by lkrief           ###   ########.fr       */
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

// Je crois qu'il y a une difference mac vs linux pour obtenir le pathname
// MAC       --------->      whereis  -bq <cmd>
// LINUX    je crois que     which <cmd>
// A verifier et voir si je peux rendre le code adaptatif ?
char	*get_pathname(const char *cmd, char **environ)
{
	int		fd[2];
	pid_t	pid;
	char	*output;
	char	*vect[] = {"/usr/bin/whereis", "-bq", (char *)cmd, NULL};

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

int	main(int argc, char **argv, char **environ)
{
	int		i = -1;
	char	*path;

	if (argc && argv)
		path= NULL;
	path = get_pathname(argv[1], environ);
	printf("%s", path);
	while (environ[++i])
		printf("%d : %s\n", i, environ[i]);
	// char *vect[] = {"/bin/ls", ".", NULL};
	// execve("/bin/ls", vect, environ);
}
