/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
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
	'#' fonctionne
	' ' ne fonctionne pas
	'+' ne fonctionne pas
*/

int	ft_put_x(long d, int n, int plus, int space)
{
	int	nb_print;

	nb_print = 0;
	if (plus > 0 && d >= 0)
		nb_print += ft_put_c('+');
	else if (space > 0 && d >= 0)
		nb_print += ft_put_c(' ');
	nb_print += ft_put_base(d, "0123456789abcdef", 16, n - nb_print + (d < 0));
	return (nb_print);
}

void	ft_seq_x(t_seq *s, long d)
{
	s->len = ft_len_base(d, 16);
	if (s->n_dot < 0)
	{
		s->n -= s->len;
		s->n -= 2 * (s->hash > 0);
		if (s->n > 0 && s->zero > 0 && s->minus < 0)
		{
			s->len += s->n;
			s->n = 0;
		}
	}
	else
	{
		s->len = ft_max(s->len, s->n_dot + (d < 0));
		s->n -= s->len;
		s->n -= 2 * (s->hash > 0);
	}
}

int	ft_printf_x(const char *str, int i, va_list *argptr)
{
	unsigned int	d;
	int				nb_print;
	t_seq			s;

	d = va_arg(*argptr, unsigned int);
	ft_init_seq(str, &i, "x", &s);
	ft_seq_x(&s, d);
	nb_print = (s.n >= 0) * s.n + s.len + 2 * (s.hash > 0 && d != 0);
	while (s.n > 0 && s.minus < 0)
		s.n -= ft_put_c(' ');
	if (s.hash > 0 && d != 0)
		ft_put_s("0x", 2);
	ft_put_x(d, s.len, s.plus, s.space);
	while (s.n > 0 && s.minus > 0)
		s.n -= ft_put_c(' ');
	return (nb_print);
}
