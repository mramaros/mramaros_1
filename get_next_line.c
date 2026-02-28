/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mramaros <mramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 17:00:49 by mramaros          #+#    #+#             */
/*   Updated: 2026/02/27 17:25:55 by mramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_text(int fd, char *stash)
{
	char	*buffer;
	int		read_line;
	char	*tmp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_line = 1;
	while (!ft_strchr(stash, '\n') && read_line > 0)
	{
		read_line = read(fd, buffer, BUFFER_SIZE);
		if (read_line < 0)
		{
			free (buffer);
			free (stash);
			return (NULL);
		}
		buffer[read_line] = '\0';
		tmp = ft_strjoin(stash, buffer);
		stash = tmp;
	}
	free (buffer);
	return (stash);
}

static char	*get_stach(char *stash)
{
	int	i;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return ((char *)ft_substr(stash, 0, i));
}

static char	*clean_stash(char *stash)
{
	int		i;
	char	*new_stach;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free (stash);
		return (NULL);
	}
	new_stach = ft_substr(stash, (i + 1), ft_strlen(stash) -i - 1);
	free (stash);
	return (new_stach);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	stash = ft_get_text(fd, stash);
	if (!stash)
		return (NULL);
	line = get_stach(stash);
	stash = clean_stash(stash);
	return (line);
}
