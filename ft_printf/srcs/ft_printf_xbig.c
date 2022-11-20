/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xbig.c                                   :+:      :+:    :+:   */
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

	'nft_put_X' fonctionne
	'-' fonctionne seulement si - est en 1er
	'0' fonctionne
	'.' fonctionne
	'#' fonctionne
	' ' ne fonctionne pas
	'+' ne fonctionne pas
*/

int	ft_put_xbig(long d, int n, int plus, int space)
{
	int	nb_print;

	nb_print = 0;
	if (plus > 0 && d >= 0)
		nb_print += ft_put_c('+');
	else if (space > 0 && d >= 0)
		nb_print += ft_put_c(' ');
	nb_print += ft_put_base(d, "0123456789ABCDEF", 16, n - nb_print + (d < 0));
	return (nb_print);
}

int	ft_printf_xbig(const char *str, int i, va_list *argptr)
{
	int				nb_print;
	t_seq			s;
	unsigned int	d;

	d = va_arg(*argptr, unsigned int);
	ft_init_seq(str, &i, "X", &s);
	ft_seq_x(&s, d);
	nb_print = (s.n >= 0) * s.n + s.len + 2 * (s.hash > 0 && d != 0);
	while (s.n > 0 && s.minus < 0)
		s.n -= ft_put_c(' ');
	if (s.hash > 0 && d != 0)
		ft_put_s("0X", 2);
	ft_put_xbig(d, s.len, s.plus, s.space);
	while (s.n > 0 && s.minus > 0)
		s.n -= ft_put_c(' ');
	return (nb_print);
}
