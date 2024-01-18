/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:09:19 by muribe-l          #+#    #+#             */
/*   Updated: 2024/01/18 15:05:59 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*free_all(char *buffer, char *remanent, char *line)
{
	if (buffer)
		free(buffer);
	if (remanent)
		free(remanent);
	if (line)
		free(line);
	return (NULL);
}

char	*get_line_remanent(char *remanent)
{
	static int	last_pos;
	char		*line;
	int			i;

	if (!last_pos)
		last_pos = 0;
	i = 0;
	while (remanent[last_pos + i] != '\n' && remanent[last_pos + i] != '\0')
		i++;
	line = (char *)malloc(sizeof(char) * i);
	if (!line)
	{
		free (remanent);
		return (NULL);
	}
	ft_strlcpy(line, &remanent[last_pos], i);
	last_pos += i;
	return (line);
}

char	*read_line(int fd, char *buffer)
{
	static char		*remanent;
	static ssize_t	bytes_read;
	int				size;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (remanent)
	{
		if (bytes_read > 0)
		{
			size = ft_strlen(remanent);
			free(remanent);
			remanent = (char *)malloc(sizeof(char) * (bytes_read + size));
			ft_strlcat(remanent, buffer, bytes_read);
		}
		free(buffer);
		return (get_line_remanent(remanent));
	}
	if (bytes_read <= 0)
		return (NULL);
	remanent = (char *)malloc(sizeof(char) * bytes_read);
	ft_strlcat(remanent, buffer, bytes_read);
	free(buffer);
	return (get_line_remanent(remanent));
}

char	*get_next_line(int fd)
{
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	return (read_line(fd, buffer));
}

#include <fcntl.h>
int	main(void)
{
	char	*s;
	int		file;

	file = open("test.txt", O_RDONLY);
	s = get_next_line(file);
	while(s)
	{
		printf("%s\n", s);
		s = get_next_line(file);
	}
	free(s);
	close(file);
}
