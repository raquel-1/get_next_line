/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raromar <raromar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:34:15 by raqroca-          #+#    #+#             */
/*   Updated: 2026/02/09 13:37:47 by raromar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*storage;
	char		buffer[BUFFER_SIZE + 1];
	size_t		bytes_read;

	while (!ft_strchr(storage, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read ==0)
			break
		if (bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = '\n';
		storage = ft_strjoin(storage, buffer);
	}
	storage = NULL;
	return (line);
}
