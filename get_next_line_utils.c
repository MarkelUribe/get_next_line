/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:09:54 by muribe-l          #+#    #+#             */
/*   Updated: 2024/01/29 15:12:24 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_memcpy(char *dst, char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

char	*ft_strjoin(char *line, char *buf)
{
	char	*new_line;
	size_t	line_len;
	size_t	buf_len;

	line_len = ft_strlen(line);
	buf_len = ft_strlen(buf);
	new_line = (char *)malloc(sizeof(char) * (line_len + buf_len + 1));
	if (new_line == NULL)
		return (NULL);
	ft_memcpy(new_line, line, line_len);
	ft_memcpy(new_line + line_len, buf, buf_len);
	new_line[line_len + buf_len] = '\0';
	free(line);
	return (new_line);
}
