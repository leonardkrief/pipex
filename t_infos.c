/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_infos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:31:37 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/24 20:09:28 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

// si n<0, le tab se finit par NULL donc on free tranquille
// sinon, on free jusqua ce que i = n
void	*free_tab(char **to_be_free, int n)
{
	int	i;

	if (to_be_free)
	{
		i = -1;
		while ((n >= 0) && ++i < n)
		{
			if (to_be_free[i])
				free(to_be_free[i]);
		}
		while ((n < 0) && to_be_free[++i] != NULL)
		{
			if (to_be_free[i])
				free(to_be_free[i]);
		}
		free(to_be_free);
	}
	return (NULL);
}

void	free_infos(t_infos *infos, int exno, char *str)
{
	if (exno < -1 || exno == 0)
		free_tab(infos->paths, -1);
	if (exno < -2 || exno == 0)
		close(infos->infile);
	if (exno < -3 || exno == 0)
		close(infos->outfile);
	free(infos);
	if (exno == -1)
	{
		perror(str);
		exit(-1);
	}
}

// recupere toutes les valeurs de PATHS dans un split et ajoute un '/'
// a la fin de toutes les valeurs. Cest utile pour get_cmd_split
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
		if (paths)
			return (paths);
	}
	return (NULL);
}

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

t_infos	*get_infos(int ac, char **av, char **ev)
{
	t_infos	*infos;

	infos = malloc(sizeof(*infos));
	if (!infos)
		return (NULL);
	infos->ac = ac;
	infos->av = av;
	infos->ev = ev;
	infos->paths = get_paths(ev);
	if (infos->paths == NULL)
		free_infos(infos, -1, "Failed to create PATHS variable");
	infos->infile = open(av[1], O_RDONLY);
	if (infos->infile == -1)
		free_infos(infos, -2, "Failed to open the infile");
	// je check avec le flag rdwr mais peut etre quon doit seulement pouvoir wr
	// dans outfile ?
	infos->outfile = open(av[ac - 1], O_RDWR | O_CREAT, 0644);
	if (infos->outfile == -1)
		free_infos(infos, -3, "Failed to open or create the outfile");
	if (get_pipes(infos) == -1)
		free_infos(infos, -4, "Failed to create all the pipes");
	return (infos);
}
