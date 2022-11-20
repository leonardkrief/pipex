/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
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

int	ft_len_p(void *p)
{
	unsigned long long	z;
	int					r;

	r = 3;
	z = ((unsigned long long)p);
	while (z >= 16)
	{
		z /= 16;
		r++;
	}
	return (r);
}

int	ft_put_p(void *p)
{
	int					len;
	unsigned long long	a;
	unsigned long long	b;

	len = 0;
	a = ((unsigned long long)p);
	b = a;
	while (b > 0)
	{
		len++;
		b /= 16;
	}
	if (p != NULL)
	{
		len += ft_put_s("0x", 2);
		ft_putullbase_fd(a, "0123456789abcdef", 16, 1);
	}
	else
		len += ft_put_s("(nil)", 5);
	return (len);
}

int	ft_printf_p(const char *str, int i, va_list *argptr)
{
	int		len;
	int		nb_print;
	int		len_p;
	void	*p;

	p = va_arg(*argptr, void *);
	len_p = ft_len_p(p);
	nb_print = ft_atoi(str + i);
	while (nb_print - len_p > 0)
	{
		nb_print--;
		ft_put_c(' ');
	}
	len = ft_max(ft_max(-nb_print, nb_print), ft_put_p(p));
	while (nb_print + len_p < 0)
	{
		nb_print++;
		ft_put_c(' ');
	}
	return (len);
}
