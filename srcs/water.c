/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   water.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:31:37 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/29 09:50:32 by lkrief           ###   ########.fr       */
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
		if (exno != -1)
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
	if (exno % 10 == 1)
	{
		ft_putstr_fd(cmdopts[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	if (exno % 10 == 2 || exno % 10 == 4)
		errno = 2;
	if (exno % 10 == 3 || exno % 10 == 5)
	{
		errno = 13;
		ft_putstr_fd("bash: ", STDERR_FILENO);
	}
	if (*(infos->i) == 2 && exno / 10 == 1 && close(infos->infile) == -1)
		perror("Failed closing infile");
	if (*(infos->i) == infos->ac - 2 && exno / 10 >= 1 \
		&& close(infos->outfile) == -1)
		perror("Failed closing infile");
	close_pipes(infos, -1);
	free_tab(cmdopts, -1);
	free_infos(infos, exno, str);
}
