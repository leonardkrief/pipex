/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 01:01:33 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/29 05:11:35 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void here_doc(t_infos *infos, char *LIMITER, char *line)
{
	if (access("here_doc", F_OK) == 0)
		unlink("here_doc");
	infos->infile = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (infos->infile == -1)
		free_infos(infos, -1, "Failed open");
	line = get_next_line(0, infos->ac - 4);
	if (!line)
		free_infos(infos, -1, "Failed malloc");
	while (line && ft_strncmp(line, LIMITER, ft_strlen(line) - 1))
	{
		if (write(infos->infile, line, ft_strlen(line)) < 0)
			free_infos(infos, -1, "Failed write");
		if (line)
			free(line);
		line = get_next_line(0, infos->ac - 4);
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