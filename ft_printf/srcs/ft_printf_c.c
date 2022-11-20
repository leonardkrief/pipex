/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 04:04:27 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/16 01:16:15 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
	fonctionnement des flags

	'n' fonctionne
	'-' fonctionne seulement si - est en 1er
	'0' ne fonctionne pas
	'.' ne fonctionne pas
	'#' ne fonctionne pas
	' ' ne fonctionne pas
	'+' ne fonctionne pas
*/

int	ft_put_c(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_printf_c(const char *str, int i, va_list *argptr)
{
	int		len;
	int		nb_print;
	char	c;

	c = va_arg(*argptr, int);
	nb_print = ft_atoi(str + i);
	len = ft_max(-nb_print, nb_print);
	len = ft_max(len, 1);
	while (nb_print - 1 > 0)
	{
		nb_print--;
		ft_put_c(' ');
	}
	ft_put_c(c);
	while (nb_print + 1 < 0)
	{
		nb_print++;
		ft_put_c(' ');
	}
	return (len);
}
