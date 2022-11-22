/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:57:18 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/22 18:42:45 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

void	print_infos(t_infos *infos)
{
	int	i;

	i = -1;
	printf("ac= %d\n", infos->ac);
	printf("av= ");
	while (infos->av[++i])
		printf("%s ", infos->av[i]);
	printf("\n");
	i = -1;
	printf("ev = ");
	while (infos->ev[++i])
		printf("%s ", infos->ev[i]);
	i = -1;
	printf("PATHS= ");
	while (infos->paths[++i])
		printf("%s ", infos->paths[i]);
	printf("\n");
	printf("infile = %d\n", infos->infile);
	printf("outfile = %d\n", infos->outfile);
	i = -1;
	while (++i < ((infos->ac)))
		printf("fd[%d] = %d %d\n", i, (infos->fd)[i][0], (infos->fd)[i][1]);
}
