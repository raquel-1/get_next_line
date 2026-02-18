/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raromar <raromar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:34:15 by raqroca-          #+#    #+#             */
/*   Updated: 2026/02/13 19:38:43 by raromar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char *storage)
{
	char	*line;
	int		i;

	i = 0;
	if (!storage || !storage[0])
		return (NULL);
	while (storage[i] && storage[i] != DELIMITER)
		i++;
	if (storage[i] == DELIMITER)
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != DELIMITER)
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] == DELIMITER)
	{
		line[i] = DELIMITER;
		i++;
	}
	return (line[i] = '\0', line);
}

char	*update_storage(char *storage)
{
	char	*new_storage;
	char	*ptr;

	if (!storage)
		return (NULL);
	ptr = ft_strchr(storage, DELIMITER);
	if (!ptr)
	{
		free(storage);
		return (NULL);
	}
	ptr++;
	if (*ptr == '\0')
	{
		free(storage);
		return (NULL);
	}
	new_storage = ft_strdup(ptr);
	free(storage);
	return (new_storage);
}

static char	*read_to_storage(int fd, char *storage)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(storage, DELIMITER) && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		storage = ft_strjoin(storage, buffer);
		if (!storage)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = read_to_storage(fd, storage);
	if (!temp)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	storage = temp;
	line = extract_line(storage);
	if (!line)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	storage = update_storage(storage);
	return (line);
}
