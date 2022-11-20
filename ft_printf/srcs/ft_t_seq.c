/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_seq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 05:18:55 by leonardkrie       #+#    #+#             */
/*   Updated: 2022/11/16 01:16:15 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_minus_seq(t_seq *s)
{
	s->minus = -1;
	s->zero = -1;
	s->hash = -1;
	s->space = -1;
	s->plus = -1;
	s->n = -1;
	s->dot = -1;
	s->n_dot = -1;
	s->len = -1;
}

void	ft_init_seq(const char *str, int *i, char *set, t_seq *s)
{
	ft_minus_seq(s);
	while (str[*i] && !ft_belongs(str[*i], set))
	{
		if (!ft_belongs(str[*i], "#+- .0123456789"))
			(*i)++;
		while (ft_belongs(str[*i], "#0+- "))
		{
			s->minus = ft_max(s->minus, -1 + 2 * (str[*i] == '-'));
			s->zero = ft_max(s->zero, -1 + 2 * (str[*i] == '0'));
			s->hash = ft_max(s->hash, -1 + 2 * (str[*i] == '#'));
			s->space = ft_max(s->space, -1 + 2 * (str[*i] == ' '));
			s->plus = ft_max(s->plus, -1 + 2 * (str[*i] == '+'));
			(*i)++;
		}
		s->n += ft_belongs(str[*i], "0123456789") * (1 + ft_atoi(str + (*i)));
		while (ft_belongs(str[*i], "0123456789"))
			(*i)++;
		s->dot = ft_max(s->dot, -1 + 2 * (str[*i] == '.'));
		(*i) += (str[*i] == '.');
		s->n_dot += ft_belongs(str[*i], "0123456789") * ft_atoi(str + (*i));
		s->n_dot += ft_belongs(str[*i], "0123456789");
		while (ft_belongs(str[*i], "0123456789"))
			(*i)++;
	}
	(*i) += (str[*i] != '\0');
}

void	ft_print_seq(t_seq s)
{
	ft_put_s("'n' -> ", 100);
	ft_printf("%d", s.n);
	ft_put_s("\n'-' -> ", 100);
	ft_printf("%d", s.minus);
	ft_put_s("\n'0' -> ", 100);
	ft_printf("%d", s.zero);
	ft_put_s("\n'.' -> ", 100);
	ft_printf("%d", s.dot);
	ft_put_s("\n'n.' -> ", 100);
	ft_printf("%d", s.n_dot);
	ft_put_s("\n'#' -> ", 100);
	ft_printf("%d", s.hash);
	ft_put_s("\n' ' -> ", 100);
	ft_printf("%d", s.space);
	ft_put_s("\n'+' -> ", 100);
	ft_printf("%d", s.plus);
	ft_put_s("\n'len' -> ", 100);
	ft_printf("%d", s.len);
}
