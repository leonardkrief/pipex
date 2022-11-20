/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 01:56:32 by lkrief            #+#    #+#             */
/*   Updated: 2022/09/25 01:57:15 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp_d;
	unsigned char	*tmp_s;

	if (!dest && dest == src)
		return (NULL);
	tmp_s = (unsigned char *) src;
	tmp_d = (unsigned char *) dest;
	i = -1;
	while (++i < n)
		tmp_d[i] = tmp_s[i];
	return (dest);
}
