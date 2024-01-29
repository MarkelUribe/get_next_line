/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:09:19 by muribe-l          #+#    #+#             */
/*   Updated: 2024/01/29 16:30:15 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *str, char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 2);
	ft_memcpy(line, str, i);
	line[i] = '\0';
	line[i++] = '\n';
	ft_memcpy(buffer, &str[i], ft_strlen(&str[i]));
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	size_t		bytes_read;

	line = NULL;
	bytes_read = 1;
	while(fd >= 0 || BUFFER_SIZE > 0)
	{
		while (1)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if ((int)bytes_read == -1)
				return (free(line), NULL);
			buffer[bytes_read] = '\0';
			line = ft_strjoin(line, buffer);
			if (ft_strchr(line, '\n'))
				break;
		}
		return (get_line(line, buffer));
	}
	if (line[0] == '\0' && bytes_read == 0)
		return (free(line), NULL);
	return (NULL);
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*s;
	int		file;

	file = open("test.txt", O_RDONLY);
	while((s = get_next_line(file)) != NULL)
	{
		printf("%s\nSALTO", s);
		free(s);
	}
	close(file);
}
