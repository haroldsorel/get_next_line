/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:02:19 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/14 15:33:33 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*get_rest(char	*s1)
{
	int		i;
	char	*s2;

	i = 0;
	while (s1[i] != '\n')
		i++;
	s2 = malloc(i + 10);
	i = 0;
	while (s1[i] != '\n')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i++] = '\n';
	s2[i] = '\0';
	return (s2);
}

int	fill_buffer(int fd, char *buffer)
{
	ft_bzero(buffer, BUFFER_SIZE + 1);
	if (read(fd, buffer, BUFFER_SIZE) > 0)
		return (0);
	else
		return (-1);
}

char	*fill_line(int fd, char *line, char *buffer)
{
	char	*rest;
	int		bytes;

	if (buffer == NULL)
		return (NULL);
	if (buffer[0] != '\0')
	{
		rest = ft_strchr(buffer, '\n');
		rest++;
		line = ft_strjoin(line, rest);
	}
	bytes = fill_buffer(fd, buffer);
	while ((bytes == 0) && ft_strchr(buffer, '\n') == NULL)
	{
		line = ft_strjoin(line, buffer);
		bytes = fill_buffer(fd, buffer);
	}
	if (bytes == -1)
		return (NULL);
	else
	{
		rest = get_rest(buffer);
		line = ft_strjoin(line, get_rest(rest));
		free(rest);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (buffer == NULL)
		buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	line = ft_calloc(1, 1);
	if (buffer == NULL || line == NULL)
		return (NULL);
	line = fill_line(fd, line, buffer);
	if (line == NULL)
	{
		free(line);
		free(buffer);
		return (NULL);
	}
	return (line);
}
