/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:02:11 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/29 20:55:11 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*strjoin_free(char *line, char *buffer)
{
	char	*temp;

	temp = line;
	line = ft_strjoin(line, buffer);
	if (line == NULL)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (line);
}

char	*line_trimmer(char *line)
{
	int		nl_index;
	int		i;
	char	*res;

	nl_index = find_nl(line);
	i = 0;
	if (nl_index == -1)
	{
		res = malloc(ft_strlen(line) + 1);
		if (res == NULL)
			return (NULL);
		while (line[i] != '\0')
		{
			res[i] = line[i];
			i++;
		}
	}
	else
	{
		res = malloc(nl_index + 2);
		if (res == NULL)
			return (NULL);
		while (i <= nl_index)
		{
			res[i] = line[i];
			i++;
		}
	}
	res[i] = '\0';
	return (res);
}

char	*line_after(char *line)
{
	int		nl_index;
	int		i;
	char	*res;

	nl_index = find_nl(line);
	i = 0;
	if (nl_index == -1)
	{
		res = malloc(1);
		if (res == NULL)
			return (NULL);
	}
	else
	{
		res = malloc(ft_strlen(line) - nl_index);
		if (res == NULL)
			return (NULL);
		while (line[nl_index + 1 + i] != '\0')
		{
			res[i] = line[nl_index + 1 + i];
			i++;
		}
	}
	res[i] = '\0';
	return (res);
}

char	*line_creator(int fd, char *rest)
{
	int			bytes;
	char		*line;
	char		buffer[BUFFER_SIZE + 1];

	if (rest == NULL)
		line = ft_strjoin("", "");
	else
		line = ft_strjoin(rest, "");
	if (line == NULL)
		return (NULL);
	bytes = 1;
	while (bytes != 0)
	{
		if (find_nl(line) != -1)
			break ;
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (free_utils(line, NULL, 2));
		buffer[bytes] = '\0';
		line = strjoin_free(line, buffer);
		if (line == NULL)
			return (NULL);
	}
	if (line[0] == '\0')
		return (free_utils(line, NULL, 2));
	return (line);
}

char	*get_next_line(int fd)
{
	static char	rest[BUFFER_SIZE + 1];
	char		*line;
	char		*return_line;
	char		*temp;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = line_creator(fd, rest);
	if (line == NULL)
	{
		rest[0] = '\0';
		return (NULL);
	}
	return_line = line_trimmer(line);
	if (return_line == NULL)
		return (free_utils(line, NULL, 2));
	temp = line_after(line);
	if (temp == NULL)
		return (free_utils(line, return_line, 3));
	free_utils(rest, temp, 1);
	free(line);
	return (return_line);
}
/*
int main()
{
	int fd = open("empty.txt", O_RDONLY);
	char *line;
	int i = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf(" Sentence %d :%s\n\n", i, line);
		i++;
	}
	return (0);
}
*/
/*
int main(void)
{
	int fd = open("empty.txt", O_RDONLY);
	char *line;
	line = get_next_line(fd);
	printf("%s//", line);
	//line = get_next_line(fd);
	//printf("%s//", line);
	//line = get_next_line(fd);
	//printf("%s//", line);
	//line = get_next_line(fd);
	//printf("%s//", line);
	return (0);
}
*/
