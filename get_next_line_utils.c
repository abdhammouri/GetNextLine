/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhammo <aalhammo@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 03:23:15 by aalhammo          #+#    #+#             */
/*   Updated: 2026/11/03 03:23:23 by aalhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*gnl_join(char *stash, const char *buffer)
{
	char	*new;
	size_t	i;
	size_t	j;

	new = malloc(gnl_strlen(stash) + gnl_strlen(buffer) + 1);
	if (!new)
	{
		free(stash);
		return (NULL);
	}
	i = 0;
	while (stash && stash[i])
	{
		new[i] = stash[i];
		i++;
	}
	j = 0;
	while (buffer[j])
		new[i++] = buffer[j++];
	new[i] = '\0';
	free(stash);
	return (new);
}
