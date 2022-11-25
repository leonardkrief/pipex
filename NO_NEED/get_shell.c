/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:34:52 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/25 16:08:00 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/pipex.h"

char	*get_shell(char **ev)
{
	int		i;
	char	**tmp;
	char	*shell;

	tmp = NULL;
	shell = NULL;
	if (ev)
	{
		i = -1;
		while (ev[++i] && !tmp)
		{
			if (ft_strnstr(ev[i], "SHELL=", 6) == ev[i])
				tmp = ft_split(ev[i], '/');
		}
		i = 0;
		while (tmp && tmp[i])
			i++;
		if (i > 0)
			shell = ft_strdup(tmp[i - 1]);
		if (tmp)
			free_tab(tmp, -1);
		return (shell);
	}
	return (NULL);
}

int main(int ac, char **av, char **ev)
{
    char	*cmdopts2[3] = {"grep", "monchef", NULL};

    // int a = execve(cmdopts2[0], cmdopts2, ev);
    // fprintf(stderr, "%d\n", a);
    

    int i = -1;
    while (ev[++i])
        printf("%s\n", ev[i]);
    printf("%s\n", get_shell(ev));

	// perror(strerror(-10));
	// perror("rkenfvlkndolnol");
}