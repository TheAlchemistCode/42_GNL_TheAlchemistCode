/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:52:57 by clyon             #+#    #+#             */
/*   Updated: 2025/08/14 17:52:57 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*_01_stash_builder(int fd, char *stash, char *buffer);
static char	*_02_stash_trunc(char *work_line);
static char	*_03_ft_strchr(char *s, int c);


/* 
 * _01_stash_builder:
 * Reads from the file descriptor into the buffer until either a newline
 * is found or there is no more data to read. Appends each chunk to the stash.
 * Returns the updated stash or NULL on error.
 */
static char	*_01_stash_builder(int fd, char *stash, char *buffer)
{
	ssize_t	b_read;
	char	*tmp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read <= 0)
		{
			if (b_read == -1)
				return (free(stash), NULL);
			break ;
		}
		buffer[b_read] = 0;
		if (!stash)
			stash = ft_strdup("");
		tmp = stash;
		stash = ft_strjoin(tmp, buffer);
		free(tmp);
		if (!stash)
			return (NULL);
		if (_03_ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

/*
 * _02_stash_trunc:
 * Extracts the leftover part of the line *after* the newline character
 * to prepare for the next get_next_line call.
 * If no leftover exists, returns NULL.
 * Also truncates the current work_line at the newline.
 */
static char	*_02_stash_trunc(char *work_line)
{
	ssize_t	i;
	char	*stash;

	i = 0;
	while (work_line[i] != '\n' && work_line[i] != '\0')
		i++;
	if (work_line[i] == '\0' || work_line[i + 1] == '\0')
		return (NULL);
	stash = ft_substr(work_line, i + 1, ft_strlen(work_line) - (i + 1)); //Copy everything after the '\n' into stash
	if (!stash || *stash == '\0') // If allocation failed OR the result is an empty strin
	{
		free(stash);
		return (NULL);
	}
	work_line[i + 1] = '\0';
	return (stash);
}

/* 
 * _03_ft_strchr:
 * Searches for the first occurrence of the character 'c' in the string 's'.
 * Returns a pointer to the matching character, or NULL if not found.
 * Special case: if 'c' is '\0', returns a pointer to the null terminator.
 */
static char	*_03_ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if (cc == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

/*
 * get_next_line:
 * Reads and returns the next line from the file descriptor 'fd'.
 * Maintains leftover data between calls using a static 'stash'.
 * Uses a buffer to read chunks and builds up the line until a newline or EOF.
 * Returns a malloc'd string containing the next line, or NULL on error or EOF.
 */
char	*get_next_line(int fd)
{
	char		*work_line; // The line being assembled to return
	char		*buffer; // Temporary buffer used for each read() call
	static char	*stash; // Persistent stash of leftover data between calls
	char		*temp; // Holds leftover after '\n' to update stash

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(0, 0, 0) < 0) // this check is inefficient, it creates a lot of overhead just to see if the file exists, and then 01stashbuilder continues to read from it anyway.
	{
		free(buffer);
		stash = NULL;
		return (NULL);
	}
	work_line = _01_stash_builder(fd, stash, buffer); // 
	free(buffer);
	if (!work_line) //if nothing read, get out
		return (NULL);
	temp = _02_stash_trunc(work_line); /// Extract leftover after '\n' to save for the next call
	stash = temp; // Update stash with leftover after '\n' to continue reading from the correct spot next time
	return (work_line); //only returns up to '\n' or eof.
}

/*#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1); //(return '0' for success usually)
	}
	while ((line = get_next_line(fd)) != NULL) //returns NULL when EOF is reached 
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/
