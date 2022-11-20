/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 01:15:01 by lkrief            #+#    #+#             */
/*   Updated: 2022/09/25 02:09:18 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	size_t			len;
	unsigned int	m;
	char			*s;

	len = 1;
	m = (-(n < 0) + (n >= 0)) * n;
	while (m >= 10)
	{
		m /= 10;
		len++;
	}
	s = malloc(sizeof(*s) * (len + (n < 0) + 1));
	if (!s)
		return (NULL);
	s[len + (n < 0)] = '\0';
	if (n < 0)
		s[0] = '-';
	m = (-(n < 0) + (n >= 0)) * n;
	while (len > 0)
	{
		s[--len + (n < 0)] = '0' + (m % 10);
		m /= 10;
	}
	return (s);
}
