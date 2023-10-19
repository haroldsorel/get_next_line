/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:01:55 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/19 02:25:15 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int	find_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}


char	*strjoin_free(char *line, char *buffer)
{
	char	*temp;

	temp = line;
	line = ft_strjoin(line, buffer);
	if (line == NULL)
		return (NULL);
	free(temp);
	return (line);
}


char	*line_rest(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);	
}

char	*line_trimmer(char *line)
{
	char	*res;
	int		nl_index;
	int		i;

	nl_index = find_nl(line);
	i = 0;
	if (nl_index == -1)
		return (line);
	res = malloc(nl_index + 2);
	while (i <= nl_index)
	{
		res[i] = line[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}


char	*line_creator(int fd, char *line)
{
	char	buffer[BUFFER_SIZE + 1];
	int	bytes;

	bytes = 1;
	if (line == NULL)
	{
		line = malloc(1);
		if (line == NULL)
			return (NULL);
		line[0] = '\0';
	}
	while (bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		//printf("buffer : %s          ->          ", buffer);
		if (bytes == -1)
			return (NULL);
		buffer[bytes] = '\0';
		line = strjoin_free(line, buffer);
		//printf("line : %s\n", line);
		if (ft_strchr(line, '\n') != NULL)
			return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char *buffer;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = line_creator(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	line = line_trimmer(buffer);
	buffer = line_rest(buffer);
	return (line);
}

int main()
{
	int fd = open("test.txt", O_RDONLY);
	char *line;
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	return (0);
}

