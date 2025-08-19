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

char	*_01_stash_builder(char *stash, int fd)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (free(stash), NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(stash), NULL);
		buffer[bytes_read] = '\0';
		stash = append_buffer(stash, buffer);
		if (!stash)
			return (free(buffer), NULL);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (free(buffer), stash);
}

char	*extract_line(char *stash)
{
	size_t	len;
	char	*workline;

	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	workline = ft_calloc(len + 1, sizeof(char));
	if (!workline)
		return (NULL);
	ft_strlcpy(workline, stash, len + 1);
	return (workline);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*workline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_calloc(1, 1);
	if (!stash)
		return (NULL);
	if (!ft_strchr(stash, '\n'))
	{
		stash = _01_stash_builder(stash, fd);
		if (!stash)
			return (NULL);
	}
	workline = extract_line(stash);
	if (!workline || workline[0] == '\0')
	{
		free(stash);
		stash = NULL;
		free(workline);
		return (NULL);
	}
	stash = obtain_remaining(stash);
	return (workline);
}

char	*obtain_remaining(char *stash)
{
	size_t	start;
	size_t	len;
	char	*remaining;

	start = 0;
	while (stash[start] && stash[start] != '\n')
		start++;
	if (stash[start] == '\n')
		start++;
	len = ft_strlen(stash + start);
	remaining = ft_calloc(len + 1, sizeof(char));
	if (!remaining)
		return (free(stash), NULL);
	ft_strlcpy(remaining, stash + start, len + 1);
	return (free(stash), remaining);
}

char	*append_buffer(char *stash, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(stash, buffer);
	return (free(stash), temp);
}
