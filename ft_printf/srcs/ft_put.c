/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 04:04:27 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/16 01:16:15 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_len_base(long d, int len_base)
{
	int				r;
	unsigned int	z;

	r = 1;
	z = (-(d < 0) + (d >= 0)) * d;
	if (d < 0)
		r++;
	while (z >= ((unsigned int)len_base))
	{
		z /= len_base;
		r++;
	}
	return (r);
}

void	ft_put_positive_base(long d, char *base, int len_base)
{
	unsigned int	z;

	z = (-(d < 0) + (d >= 0)) * d;
	if (z >= ((long)len_base))
		ft_put_positive_base(z / len_base, base, len_base);
	ft_put_c(base[z % len_base]);
}

int	ft_put_base(long d, char *base, int len_base, int n)
{
	int	size;
	int	nb_print;

	size = ft_len_base(d, len_base);
	nb_print = 0;
	if (n > 0)
	{
		if (d < 0)
		{
			nb_print += ft_put_c('-');
			n--;
		}	
		while (n > size)
		{
			nb_print += ft_put_c('0');
			n--;
		}
		ft_put_positive_base(d, base, len_base);
		nb_print += size;
	}
	return (nb_print);
}

// %p
void	ft_putullbase_fd(unsigned long long z, char *base, int lenbas, int fd)
{
	if (z >= ((unsigned long long)lenbas))
		ft_putullbase_fd(z / lenbas, base, lenbas, fd);
	ft_putchar_fd(base[z % lenbas], fd);
}

int	ft_printf_percent(void)
{
	ft_putchar_fd('%', 1);
	return (1);
}
