/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 08:47:27 by jsubel            #+#    #+#             */
/*   Updated: 2022/04/21 09:26:51 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static void	ft_store_remainder(char *remainder, char **remainder_array, int fd)
{
	size_t	str_len;
	char	*remainder_string;

	str_len = ft_strlen(remainder);
	if (str_len > 0)
	{
		remainder_string = malloc(sizeof(char) * (str_len + 1));
		ft_memmove(remainder_string, remainder, str_len);
		remainder_string[str_len] = '\0';
		remainder_array[fd] = remainder_string;
	}
	else
		remainder_array[fd] = NULL;
}

static char	*return_line(char *str, int fd, char **rmndr_array, char *buffer)
{
	char	*returnstr;
	char	*remainder;
	size_t	str_len;

	remainder = (ft_strchr(str, '\n') + 1);
	ft_store_remainder(remainder, rmndr_array, fd);
	remainder[0] = '\0';
	str_len = ft_strlen(str);
	returnstr = malloc(sizeof(char) * (str_len + 1));
	ft_memmove(returnstr, str, str_len + 1);
	free(buffer);
	free(str);
	return (returnstr);
}

static char	*ft_freeturn(char *buffer, char *returnstring)
{
	free(buffer);
	return (returnstring);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*returnstring;
	int			read_len;
	static char	*remainder[1024];

	returnstring = NULL;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (remainder[fd])
	{
		returnstring = ft_strcat(returnstring, remainder[fd]);
		free(remainder[fd]);
		remainder[fd] = NULL;
		if (ft_strchr(returnstring, '\n'))
			return (return_line(returnstring, fd, remainder, buffer));
	}
	read_len = read(fd, buffer, BUFFER_SIZE);
	while (read_len > 0)
	{
		buffer[read_len] = '\0';
		returnstring = ft_strcat(returnstring, buffer);
		if (ft_strchr(returnstring, '\n'))
			return (return_line (returnstring, fd, remainder, buffer));
		read_len = read(fd, buffer, BUFFER_SIZE);
	}
	return (ft_freeturn(buffer, returnstring));
}
