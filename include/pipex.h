/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:16:38 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/20 17:14:05 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "../libft/libft.h"
#include "../ft_printf/includes/ft_printf.h"
#include "get_next_line.h"

void	*err_out(const char *str, void *to_be_free, void *value);
char	*get_pathname(const char *cmd, char **environ);

#endif