/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:09:19 by muribe-l          #+#    #+#             */
/*   Updated: 2024/01/22 20:06:18 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	buffer = ft_strjoin(buffer, &buffer[i]);
	if (i >= ft_strlen(buffer))
		return (NULL);
	line = ft_strjoin(line, buffer[i]);
	if (!line)
		return (NULL);
	if (!line)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	size_t		bytes_read;

	//Leer el resto anterior de buffer
	line = NULL;
	bytes_read = 1;
	if (buffer)
	{
		line = get_line(buffer);
		if (line)
			return (line);
	}
	while(1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(line), NULL);
		else if (bytes_read == 0)
			return (line);
		buffer[bytes_read] = '\0';
		line = ft_strjoin(line, buffer);
		if (!line)
			return (NULL);
	}
	//Dejar el resto en buffer
	return (line);
}

#include <fcntl.h>
int	main(void)
{
	char	*s;
	int		file;

	file = open("test.txt", O_RDONLY);
	while((s = get_next_line(file)) != NULL)
	{
		printf("%s\n", s);
		free(s);
	}
	close(file);
}
