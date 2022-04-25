/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 11:35:56 by jsubel            #+#    #+#             */
/*   Updated: 2021/12/21 10:37:02 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	if (src < dst)
	{
		i = len;
		while (i > 0)
		{
			i--;
			*(char *)(dst + i) = *(char *)(src + i);
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			*(char *)(dst + i) = *(char *)(src + i);
			i++;
		}
	}
	return ((void *)dst);
}

char	*ft_strcat(char *s1, char *s2)
{
	char	*dst;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = 0;
	len_s2 = ft_strlen(s2);
	if (s1)
		len_s1 = ft_strlen(s1);
	dst = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (s1)
		ft_memmove(dst, s1, len_s1);
	ft_memmove(dst + len_s1, s2, len_s2);
	dst[len_s1 + len_s2] = '\0';
	if (s1)
		free(s1);
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((char)c == s[i])
			return ((char *)s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	else
		return (NULL);
}
