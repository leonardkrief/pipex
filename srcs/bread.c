/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bread.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 01:01:33 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/29 10:33:10 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	get_pipes(t_infos *infos)
{
	int	i;
	int	j;

	i = -1;
	while (++i < infos->ac - 4)
	{
		if (pipe((infos->fd)[i]) == -1)
		{
			j = -1;
			while (++j < i)
			{
				close((infos->fd)[j][0]);
				close((infos->fd)[j][1]);
			}
			return (-1);
		}
	}
	return (0);
}

// recupere toutes les valeurs de PATHS dans un split et ajoute un '/'
// a la fin de toutes les valeurs. cest utile pour get_cmd_split
char	**get_paths(char **ev)
{
	int		i;
	char	*tmp;
	char	**paths;

	paths = NULL;
	if (ev)
	{
		i = -1;
		while (ev[++i] && !paths)
		{
			if (ft_strnstr(ev[i], "PATH=", 5) == ev[i])
				paths = ft_split(ev[i] + 5, ':');
		}
		i = -1;
		while (paths && paths[++i])
		{
			tmp = paths[i];
			paths[i] = ft_strjoin(tmp, "/");
			if (tmp)
				free(tmp);
		}
		return (paths);
	}
	return (NULL);
}

t_infos	*get_infos(int ac, char **av, char **ev)
{
	t_infos	*infos;

	infos = malloc(sizeof(*infos));
	if (!infos)
		return (NULL);
	infos->here_doc = 0;
	if (!ft_strcmp(av[1], "here_doc"))
		infos->here_doc = 1;
	infos->ac = ac - infos->here_doc;
	infos->av = av;
	infos->ev = ev;
	infos->paths = get_paths(ev);
	if (infos->paths == NULL)
		free_infos(infos, -1, "Failed to create PATHS variable");
	if (get_pipes(infos) == -1)
		free_infos(infos, -4, "Failed to create all pipes");
	return (infos);
}

// si n >= 0, ferme tous les pipes sauf fd[n - 1][0] et fd[n][1]
// si n < 0,  ferme tous les pipes sauf le read du dernier
// renvoie -1 en cas d'erreur
int	close_pipes(t_infos *infos, int n)
{
	int	i;
	int	exno;

	exno = 0;
	i = -1;
	if (n >= 0)
	{
		while (++i < infos->ac - 4)
		{
			if (i != n - 1 && close((infos->fd)[i][0]) == -1)
				exno = -1;
			if (i != n && close((infos->fd)[i][1]) == -1)
				exno = -1;
		}
		return (exno);
	}
	while (++i < infos->ac - 4)
	{
		if (close((infos->fd)[i][0]) == -1)
			exno = -1;
		if (close((infos->fd)[i][1]) == -1)
			exno = -1;
	}
	return (exno);
}

void	here_doc(t_infos *infos, char *LIMITER, char *line)
{
	if (access("here_doc", F_OK) == 0)
		unlink("here_doc");
	infos->infile = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (infos->infile == -1)
		free_infos(infos, -1, "Failed open");
	line = get_next_line(0);
	if (!line)
		free_infos(infos, -1, "Failed malloc");
	while (line && ft_strncmp(line, LIMITER, ft_strlen(line) - 1))
	{
		if (write(infos->infile, line, ft_strlen(line)) < 0)
			free_infos(infos, -1, "Failed write");
		if (line)
			free(line);
		line = get_next_line(0);
		if (!line)
			free_infos(infos, -1, "Failed malloc");
	}
	if (line)
		free(line);
	if (close(infos->infile) == -1)
		free_infos(infos, -1, "Failed close");
	infos->av[2] = infos->av[1];
	infos->av++;
}
