/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 03:04:03 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/29 04:07:14 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

size_t	ft_strlen(const char *s)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i++])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return ((char *) s + i);
	else
		return (NULL);
}

void	ft_reset_buff(char *buff)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	while (buff[i])
		buff[j++] = buff[i++];
	buff[j] = '\0';
}

char	*ft_strjoin_gnl(char const *res, char const *buff)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (buff[0] == 0)
		return (NULL);
	if (res == NULL)
		join = malloc(sizeof(*join) * (ft_strlen(buff) + 1));
	else
		join = malloc(sizeof(*join) * (ft_strlen(res) + \
			ft_strlen(buff) + 1));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (res && res[i])
		join[j++] = res[i++];
	i = 0;
	while (buff[i] && buff[i] != '\n')
		join[j++] = buff[i++];
	if (buff[i] == '\n')
		join[j++] = '\n';
	join[j] = '\0';
	return (join);
}

void	aux_gnl(char **res, char *buff)
{
	char	*tmp;

	tmp = *res;
	*res = ft_strjoin_gnl(*res, buff);
	if (tmp)
		free(tmp);
}

char	*one_line(char *buff, int fd)
{
	int		ret;
	char	*res;

	res = NULL;
	ret = 0;
	aux_gnl(&res, buff);
	if (!ft_strchr(buff, '\n'))
		ret = read(fd, buff, BUFFER_SIZE);
	while (ret && !ft_strchr(buff, '\n'))
	{
		buff[ret] = '\0';
		aux_gnl(&res, buff);
		ret = read(fd, buff, BUFFER_SIZE);
	}
	if (ret)
	{
		buff[ret] = '\0';
		aux_gnl(&res, buff);
	}
	ft_reset_buff(buff);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];

	if (BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0)
		return (NULL);
	return (one_line(buff, fd));
}

int main()
{
    int     fd;
    char    *next;

	fd = open("bibitest", O_CREAT | O_RDWR, 0644);
    write(fd, "CEST CHAUD\nCA VA\nBOSS PIPEX\nLE PAIN NE TOMBE PAS DU CIEL\nLA PAROLE CIRCULE ENTRE LES COLONNES", 94);
    close(fd);
    fd = open("bibitest", O_RDWR);

    next = get_next_line(fd);
    printf("%s", next);
    free(next);

    next = get_next_line(fd);
    printf("%s", next);
    free(next);
    
    next = get_next_line(fd);
    printf("%s", next);
    free(next);

    next = get_next_line(fd);
    printf("%s", next);
    free(next);

    next = get_next_line(fd);
    printf("%s", next);
    free(next);

 
}