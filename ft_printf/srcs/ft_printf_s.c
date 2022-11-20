/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 04:04:27 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/16 20:25:39 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
	fonctionnement des flags

	'n' fonctionne
	'-' fonctionne seulement si - est en 1er
	'0' ne fonctionne pas
	'.' fonctionne
	'#' ne fonctionne pas
	' ' ne fonctionne pas
	'+' ne fonctionne pas
*/

int	ft_put_s(char *s, int n)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] && i < n)
		len += ft_put_c(s[i++]);
	return (len);
}

int	ft_atoi_after_dot(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '.' && str[i] != 's')
		i++;
	if (str[i] == 's')
		return (2147483647);
	else if (str[i++] == '.')
		return (ft_atoi(str + i));
	else
		return (-2147483648);
}

int	ft_printf_s_minus(const char *str, int i, char *s)
{
	int		len;
	int		nb_print_s;

	nb_print_s = ft_min(((int)ft_strlen(s)), ft_atoi_after_dot(str + i));
	len = ft_max(-ft_atoi(str + i), nb_print_s);
	ft_put_s(s, nb_print_s);
	while (nb_print_s < len)
	{
		nb_print_s++;
		ft_put_c(' ');
	}
	return (len);
}

int	ft_printf_s_nominus(const char *str, int i, char *s)
{
	int		len;
	int		tmp;
	int		nb_print_s;

	nb_print_s = ft_min(((int)ft_strlen(s)), ft_atoi_after_dot(str + i));
	len = ft_max(ft_atoi(str + i), nb_print_s);
	tmp = nb_print_s;
	while (nb_print_s < len)
	{
		nb_print_s++;
		ft_put_c(' ');
	}
	ft_put_s(s, tmp);
	return (len);
}

int	ft_printf_s(const char *str, int i, va_list *argptr)
{
	char	*s;

	s = va_arg(*argptr, char *);
	if (s == NULL)
		return (ft_put_s("(null)", 6));
	else if (str[i] == '-')
		return (ft_printf_s_minus(str, i, s));
	else
		return (ft_printf_s_nominus(str, i, s));
}
