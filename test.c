/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:11:11 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/14 00:47:22 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int main(int argc, char *argv[])
{
	const char	*filename;
	int 			fd;
	char		*line;
	int			i;
	i = 0;
	if (argc != 3)
	{
		printf("Incorrect Input");
		return (-1);
	}
	filename = argv[1];
	fd = open(filename, O_RDONLY);
	while ((line = get_next_line(fd)) && i <= (argv[2][0] - '0' - 1))
	{
		printf("%s", line);
		i++;
	}
	close(fd);
	return (0);
}
