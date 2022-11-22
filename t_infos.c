/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_infos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:31:37 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/22 18:41:47 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

// si n<0, le tab se finit par NULL donc on free tranquille
// sinon, on free jusqua ce que i = n
void	*free_tab(void **to_be_free, int n)
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

void	free_infos(t_infos *infos, int exno)
{
	if (exno < -1 || exno == 1)
		free_tab((void **) infos->paths, -1);
	if (exno < -2 || exno == 1)
		close(infos->infile);
	if (exno < -3 || exno == 1)
		close(infos->outfile);
	free(infos);
	if (exno == -1)
		perror("Failed to create PATHS variable");
	else if (exno == -2)
		perror("Failed to open the infile");
	else if (exno == -3)
		perror("Failed to open or create the outfile");
	else if (exno == -4)
		perror("Failed to create all the pipes");
	else if (exno == -5)
		perror("Invalid command or malloc failed");
	else if (exno == -6)
		perror("Failed duplicating file descriptor");
	else if (exno == -7)
		perror("Failed closing file descriptor");
	if (exno < 0)
		exit(-1);
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
	while (++i < infos->ac - 1)
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
		free_infos(infos, -1);
	infos->infile = open(av[1], O_RDONLY);
	if (infos->infile == -1)
		free_infos(infos, -2);
	infos->outfile = open(av[ac - 1], O_RDWR | O_CREAT, 0644);
	if (infos->outfile == -1)
		free_infos(infos, -3);
	if (get_pipes(infos) == -1)
		free_infos(infos, -4);
	return (infos);
}
