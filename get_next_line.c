/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raromar <raromar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:34:15 by raqroca-          #+#    #+#             */
/*   Updated: 2026/02/10 23:41:16 by raromar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*storage;
	char		buffer[BUFFER_SIZE + 1];
	size_t		bytes_read;
	char		*line;

	while (!ft_strchr(storage, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = '\0';
		storage = ft_strjoin(storage, buffer);
	}
	if (storage != NULL && ft_strlen(storage) == 0)
		return (NULL);
	line = extract_line(storage);
	storage = update_storage(storage);
	return (line);	
/*
SI hay '\n' en storage:
    → Extraer desde inicio hasta '\n' (incluido)
    → Guardar en 'line'
    → Actualizar storage con lo que queda después de '\n'
    → Retornar line

SI NO hay '\n' (EOF):
    → Extraer todo storage
    → Guardar en 'line'
    → Limpiar storage (ponerlo a NULL)
    → Retornar line
///////////////////////////////////////
	char *extract_line(char *storage)
	{
		// 1. ¿Cómo encuentras dónde está el '\n'?
		// 2. ¿Cuántos bytes necesitas copiar?
		// 3. ¿Necesitas malloc? ¿De qué tamaño?
		// 4. ¿Qué pasa si no hay '\n'?
		
		// Tu código aquí
	}
	Pistas:
		Usa ft_strchr() para encontrar \n
		Calcula la longitud hasta \n (o hasta el final)
		Haz malloc() de esa longitud + 1
		Copia caracteres
		No olvides el \0
	char *update_storage(char *storage)*/
}
