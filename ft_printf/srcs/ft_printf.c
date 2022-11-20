/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 04:04:27 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/16 01:16:15 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	ft_argtype(const char *str, int i)
{
	while (str[i] && !ft_belongs(str[i], "cspdiuxX") && str[i] != '%')
		i++;
	return (str[i]);
}

int	ft_printfmod(const char *str, int i, va_list *argptr)
{
	int		len;
	char	t;

	len = 0;
	t = ft_argtype(str, i);
	if (t == 'c')
		len = ft_printf_c(str, i, argptr);
	else if (t == 's')
		len = ft_printf_s(str, i, argptr);
	else if (t == 'p')
		len = ft_printf_p(str, i, argptr);
	else if (t == 'd' || t == 'i')
		len = ft_printf_d(str, i, argptr);
	else if (t == 'u')
		len = ft_printf_u(str, i, argptr);
	else if (t == 'x')
		len = ft_printf_x(str, i, argptr);
	else if (t == 'X')
		len = ft_printf_xbig(str, i, argptr);
	else if (t == '%')
		len = ft_printf_percent();
	return (len);
}

void	ft_printf_aux(const char *str, int *i, int *count_print)
{
	ft_putchar_fd(str[*i], 1);
	(*i)++;
	(*count_print)++;
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count_print;
	va_list	argptr;

	i = 0;
	count_print = 0;
	va_start(argptr, str);
	while (str[i])
	{
		if (str[i] && str[i] != '%')
			ft_printf_aux(str, &i, &count_print);
		else if (str[i] == '%')
		{
			i++;
			count_print += ft_printfmod(str, i, &argptr);
			while (str[i] && !ft_belongs(str[i], "cspdiuxX") && str[i] != '%')
				i++;
			if (str[i])
				i++;
		}
	}
	va_end(argptr);
	return (count_print);
}
