/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:01:21 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/14 00:30:01 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdio.h> //to be removed
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2);
char	*get_next_line(int fd);
char	*ft_substr(char const *str, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *str, int c);
void	ft_bzero(void *ptr, size_t n);

#endif
