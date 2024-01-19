/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:09:19 by muribe-l          #+#    #+#             */
/*   Updated: 2024/01/19 12:28:51 by muribe-l         ###   ########.fr       */
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
	if (last_pos >= ft_strlen(remanent))
		return (NULL);
	return (line);
}

char	*read_line(int fd, char *buffer)
{
	static char		*remanent;
	static ssize_t	bytes_read;
	char			*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	if (remanent)
	{
		printf("%s", remanent);
		if (bytes_read > 0)
		{
			temp = (char *)malloc(sizeof(char) * ft_strlen(remanent) + 1);
			ft_strlcpy(temp, remanent, ft_strlen(remanent) + 1);
			free(remanent);
			remanent = (char *)malloc(sizeof(char) * (bytes_read + ft_strlen(temp) + 1));
			ft_strlcpy(remanent, temp, ft_strlen(temp) + 1);
			free(temp);
			ft_strlcat(remanent, buffer, bytes_read + 1);
		}
		return (get_line_remanent(remanent));
	}
	remanent = (char *)malloc(sizeof(char) * bytes_read + 1);
	ft_strlcat(remanent, buffer, bytes_read + 1);
	return (get_line_remanent(remanent));
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*line;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	line = read_line(fd, buffer);
	free(buffer);
	return (line);
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
