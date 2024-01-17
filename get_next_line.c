/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:09:19 by muribe-l          #+#    #+#             */
/*   Updated: 2024/01/17 17:58:58 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*read_line(int fd, char *buffer)
{
	static char	*remanent;
	int			i;
	ssize_t		bytes_read;
	char		*line;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if(bytes_read == -1)
		return (NULL);
	i = 0;
	line = NULL;
	if (remanent)
		buffer -= ft_strlen(remanent);
	while (i < bytes_read)
	{
		if (buffer[i] == '\n')
		{
			printf("<salto>");
			if (remanent)
			{
				free(line);
				line = (char *)malloc(sizeof(char) * (i + ft_strlen(remanent) - 1));
			}
			else
				line = (char *)malloc(sizeof(char) * (i - 1));
			if (!line)
				return(NULL);
			if (remanent)
			{
				ft_strlcpy(line, remanent, ft_strlen(remanent));
				free(remanent);
			}
			ft_strlcat(line, buffer, i - 1);
			remanent = (char *)malloc(sizeof(char) * (bytes_read - i));
			if (!remanent)
				return(NULL);
			ft_strlcpy(remanent, &buffer[i], (bytes_read - i));
			return(line);
		}
		else if (buffer[i] == '\0')
		{
			printf("<amaitu>");
			if (remanent)
				free(remanent);
			if (line)
				free(line);
			line = (char *)malloc(sizeof(char) * i);
			if (!line)
				return(NULL);
			ft_strlcat(line, buffer, i);
		}
		i++;
	}
	return (line);
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
}
