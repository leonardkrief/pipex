/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_infos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:31:37 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/29 05:51:07 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
	char	*tmp;

	if (infos)
	{
		if (exno < -1 || exno == 0)
			free_tab(infos->paths, -1);
		if ((exno == -2) && close(infos->infile) == -1)
			perror("Failed to close infile");
		if ((exno == -3) && close(infos->outfile) == -1)
			perror("Failed to close outfile");
		free(infos);
		if (exno != 0)
		{
			tmp = NULL;
			if (exno == 2 || exno == 3)
				tmp = ft_strjoin("bash: ", str);
			if (!tmp && str)
				perror(str);
			else if (tmp && str)
				perror(tmp);
			if (tmp)
				free(tmp);
			exit(-1);
		}
	}
}

void	*free_tab_str(char **to_be_free, char *str)
{
	free_tab(to_be_free, -1);
	if (str)
		free(str);
	return (NULL);
}

// exno == 0 si cmdopts[0] nexiste pas
// exno == 2 ou 4 si un fichier nexiste pas
// exno == 3 ou 5 si un fichier ne donne pas les droits
void	free_tab_infos(char **cmdopts, t_infos *infos, int exno, char *str)
{
	if (exno == 1)
	{
		ft_putstr_fd(cmdopts[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	if (exno == 2 || exno == 4)
		errno = 2;
	if (exno == 3 || exno == 5)
	{
		errno = 13;
		ft_putstr_fd("bash: ", STDERR_FILENO);
	}
	free_infos(infos, exno, str);
	free_tab(cmdopts, -1);
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
		fprintf(stderr, "opened pipe %d\n", i);
	}
	return (0);
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
