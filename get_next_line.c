/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 20:48:52 by clyon             #+#    #+#             */
/*   Updated: 2025/08/18 20:48:52 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*read_from_file(char *buffer2, int fd)
{
	char	*buffer1;
	ssize_t	bytes_read;
	size_t	chunk;

	if (BUFFER_SIZE > 1048576)
		chunk = 1048576;
	else
		chunk = BUFFER_SIZE;
	buffer1 = malloc(chunk + 1);
	if (buffer1 == NULL)
		return (free(buffer2), NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer1, chunk);
		if (bytes_read == -1)
			return (free(buffer1), free(buffer2), NULL);
		buffer1[bytes_read] = '\0';
		buffer2 = append_buffer(buffer2, buffer1);
		if (!buffer2)
			return (free(buffer1), NULL);
		if (ft_strchr(buffer2, '\n'))
			break ;
	}
	return (free(buffer1), buffer2);
}

char	*extract_line(char *buffer2)
{
	size_t	len;
	char	*line;

	len = 0;
	while (buffer2[len] && buffer2[len] != '\n')
		len++;
	if (buffer2[len] == '\n')
		len++;
	line = ft_calloc(len + 1, sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, buffer2, len + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer2 = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer2)
		buffer2 = ft_calloc(1, 1);
	if (!buffer2)
		return (NULL);
	if (!ft_strchr(buffer2, '\n'))
	{
		buffer2 = read_from_file(buffer2, fd);
		if (!buffer2)
			return (NULL);
	}
	line = extract_line(buffer2);
	if (!line || line[0] == '\0')
	{
		free(buffer2);
		buffer2 = NULL;
		free(line);
		return (NULL);
	}
	buffer2 = obtain_remaining(buffer2);
	return (line);
}

char	*obtain_remaining(char *buffer2)
{
	size_t	start;
	size_t	len;
	char	*remaining;

	start = 0;
	while (buffer2[start] && buffer2[start] != '\n')
		start++;
	if (buffer2[start] == '\n')
		start++;
	len = ft_strlen(buffer2 + start);
	remaining = ft_calloc(len + 1, sizeof(char));
	if (!remaining)
		return (free(buffer2), NULL);
	ft_strlcpy(remaining, buffer2 + start, len + 1);
	return (free(buffer2), remaining);
}

char	*append_buffer(char *buffer2, char *read_buffer)
{
	char	*temp;

	temp = ft_strjoin(buffer2, read_buffer);
	return (free(buffer2), temp);
}
