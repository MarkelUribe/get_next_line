/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:09:19 by muribe-l          #+#    #+#             */
/*   Updated: 2024/02/09 16:04:58 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *str, char *buffer, size_t bytes_read)
{
	char	*line;
	int		i;

	if (!ft_strchr(str, '\n') && bytes_read == 0 && ft_strlen(str) <= 0)
		return (free(str), ft_bzero(buffer, ft_strlen(buffer)), NULL);
	else if (!ft_strchr(str, '\n') && bytes_read == 0)
		return (str);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 2);
	if (!line)
		return (free(str), ft_bzero(buffer, ft_strlen(buffer)), NULL);
	ft_memcpy(line, str, i);
	line[i] = '\n';
	line[i + 1] = '\0';
	if (str[i] == '\n')
		i++;
	ft_memcpy(buffer, &str[i], ft_strlen(&str[i]));
	buffer[ft_strlen(&str[i])] = '\0';
	free(str);
	return (line);
}

static int	buffer_check(char *buffer, char **line)
{
	*line = (char *)malloc(sizeof(char));
	if (!*line)
		return (ft_bzero(buffer, ft_strlen(buffer)), 0);
	*line[0] = '\0';
	if (ft_strlen(buffer) > 0)
	{
		*line = ft_strjoin(*line, buffer);
		if (!*line)
			return (ft_bzero(buffer, ft_strlen(buffer)), 0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	size_t		bytes_read;

	buffer_check(buffer, &line);
	bytes_read = 1;
	while (fd >= 0 || BUFFER_SIZE > 0)
	{
		while (bytes_read > 0 && !ft_strchr(line, '\n'))
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if ((int)bytes_read == -1)
				return (free(line), ft_bzero(buffer, ft_strlen(buffer)), NULL);
			buffer[bytes_read] = '\0';
			line = ft_strjoin(line, buffer);
			if (!line)
				return (ft_bzero(buffer, ft_strlen(buffer)), NULL);
		}
		return (get_line(line, buffer, bytes_read));
	}
	return (free(line), NULL);
}

/* #include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*s;
	int		file;

	file = open("test.txt", O_RDONLY);
	while((s = get_next_line(file)) != NULL)
	{
		printf("%s//SALTO//\n", s);
		free(s);
	}
	close(file);
} */
