/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 04:04:27 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/16 01:16:15 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
	FLAGS

	'n' fonctionne
	'-' fonctionne seulement si - est en 1er
	'0' fonctionne
	'.' fonctionne
	'#' ne fonctionne pas
	' ' fonctionne
	'+' fonctionne
*/

void	ft_putunbr_fd(unsigned int u, int fd)
{
	if (u >= 10)
		ft_putunbr_fd(u / 10, fd);
	ft_putchar_fd('0' + u % 10, 1);
}

int	ft_put_u(unsigned int u)
{
	int	i;

	i = 1;
	while (u >= 10)
	{
		i++;
		u /= 10;
	}
	ft_putunbr_fd(u, 1);
	return (i);
}

int	ft_printf_u(const char *str, int i, va_list *argptr)
{
	unsigned int	d;
	int				nb_print;
	t_seq			s;

	d = va_arg(*argptr, unsigned int);
	ft_init_seq(str, &i, "u", &s);
	ft_seq_d(&s, d);
	nb_print = (s.n >= 0) * s.n + s.len;
	while (s.n > 0 && s.minus < 0)
		s.n -= ft_put_c(' ');
	ft_put_d(d, s.len, s.plus, s.space);
	while (s.n > 0 && s.minus > 0)
		s.n -= ft_put_c(' ');
	return (nb_print);
}
