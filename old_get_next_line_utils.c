/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:52:49 by clyon             #+#    #+#             */
/*   Updated: 2025/08/17 16:44:52 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *s1)
{
	char			*dest;
	unsigned int	i;

	dest = (char *)malloc(ft_strlen(s1) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
 * ft_substr:
 * Allocates and returns a substring from the string 's'.
 * The substring begins at index 'start' and is of maximum length 'len'.
 * Handles edge cases: returns empty string if start is beyond the length of 's'.
 * Returns NULL on allocation failure or if input string is NULL.
 */
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*str;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start) //if requested length goes beyond the end of the string, adjust to available length
		len = s_len - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s12;

	if (!s1 || !s2)
		return (NULL);
	s12 = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s12)
		return (NULL);
	ft_joiner(s12, s1, s2);
	return (s12);
}

void	ft_joiner(char *s12, const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s12 || !s1 || !s2)
		return ;
	while (s1[j])
		s12[i++] = s1[j++];
	j = 0;
	while (s2[j])
		s12[i++] = s2[j++];
	s12[i] = '\0';
}
