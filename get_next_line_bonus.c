/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwaldon <vwaldon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:46:34 by vwaldon           #+#    #+#             */
/*   Updated: 2022/01/04 19:44:13 by vwaldon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strdup_gnl(char *s1)
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	if (!s1[i])
		return (NULL);
	len = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s1[i] != '\n' && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	if (s1[i] == '\n')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*dst;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dst = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!dst)
		return (NULL);
	while (i < len1)
	{
		dst[i] = s1[i];
		i++;
	}
	while (j < len2)
		dst[i++] = s2[j++];
	dst[i] = '\0';
	free(s1);
	free(s2);
	return (dst);
}

static char	*ft_newline(char *s1)
{
	char	*newline;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (s1[i] != '\n' && s1[i])
		i++;
	if (s1[i] == '\n')
	{
		len = ft_strlen(s1);
		newline = malloc(sizeof(char) * (len - i));
		if (!newline)
			return (NULL);
		i++;
		while (s1[i])
			newline[j++] = s1[i++];
		newline[j] = '\0';
		free(s1);
		return (newline);
	}
	free (s1);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*rest[OPEN_MAX];
	char		*line;
	char		*buffer;
	ssize_t		read_byte;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1 || fd > OPEN_MAX)
		return (NULL);
	read_byte = 1;
	while (!ft_strchr(rest[fd], '\n') && read_byte > 0)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		read_byte = read(fd, buffer, BUFFER_SIZE);
		buffer[read_byte] = '\0';
		rest[fd] = ft_strjoin_gnl(rest[fd], buffer);
	}
	line = ft_strdup_gnl(rest[fd]);
	rest[fd] = ft_newline(rest[fd]);
	return (line);
}
