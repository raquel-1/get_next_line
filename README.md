*Este proyecto ha sido creado como parte del currículo de 42 por raqroca-.*

# get_next_line

## Descripción

**get_next_line** es un proyecto en C cuyo objetivo es implementar una función capaz de leer un archivo (o la entrada estándar) línea a línea a partir de un descriptor de archivo (`fd`).

La función `get_next_line` devuelve una línea completa en cada llamada, incluyendo el carácter de salto de línea (`\n`) si está presente. El proyecto refuerza conceptos fundamentales como:

- Uso de variables estáticas.
- Gestión de memoria dinámica.
- Lectura incremental mediante la función `read()`.
- Control de memoria sin provocar leaks ni comportamientos indefinidos.

El objetivo principal es aprender a manejar correctamente la lectura parcial de un archivo sin cargarlo completamente en memoria.

---

## Prototipo

```c
char *get_next_line(int fd);
```

---

## Archivos del proyecto

### Parte obligatoria

* `get_next_line.c`
* `get_next_line_utils.c`
* `get_next_line.h`

### Parte bonus (no implementada en este repositorio)

* `get_next_line_bonus.c`
* `get_next_line_utils_bonus.c`
* `get_next_line_bonus.h`

---

## Descripción detallada de la biblioteca creada

Para este proyecto se ha desarrollado una pequeña biblioteca auxiliar que contiene funciones necesarias para manipular cadenas y gestionar memoria correctamente.

Las funciones implementadas son:

- `ft_strlen`: calcula la longitud de una cadena.
- `ft_strchr`: busca la primera aparición de un carácter en una cadena.
- `ft_strdup`: duplica completamente una cadena reservando nueva memoria.
- `ft_strjoin`: concatena dos cadenas en una nueva reserva de memoria, liberando la primera.

Estas funciones permiten:

- Construir progresivamente el contenido leído desde el descriptor.
- Detectar la presencia del salto de línea (`\n`).
- Duplicar la parte restante tras extraer una línea.
- Gestionar correctamente la memoria dinámica durante todo el proceso.

Toda la biblioteca ha sido implementada respetando las restricciones del proyecto y sin utilizar funciones prohibidas.

---

## Explicación y justificación del algoritmo

La implementación se basa en una **variable estática (`storage`)** que conserva entre llamadas el contenido leído del descriptor de archivo que aún no ha sido devuelto como línea.

El flujo del algoritmo se divide en tres funciones principales:

### 1. `read_to_storage`

Esta función se encarga de leer desde el descriptor de archivo usando `read()` en bloques de tamaño `BUFFER_SIZE`.

- Se reserva memoria para un `buffer`.
- Se lee repetidamente mientras:
  - No exista un `\n` en `storage`.
  - No se haya alcanzado el final del archivo.
- Cada bloque leído se concatena a `storage` mediante `ft_strjoin`.
- Si ocurre un error (`read` devuelve `-1`), se libera la memoria y se devuelve `NULL`.

Esto permite realizar una lectura incremental eficiente sin cargar el archivo completo en memoria.

---

### 2. `extract_line`

Una vez que `storage` contiene al menos una línea completa (o se ha llegado al final del archivo), esta función:

- Recorre `storage` hasta encontrar `\n` o el final.
- Reserva memoria exacta para la línea.
- Copia los caracteres correspondientes.
- Incluye el salto de línea si existe.

Devuelve la línea lista para el usuario.

---

### 3. `update_storage`

Después de extraer la línea, es necesario conservar únicamente el contenido restante.

Esta función:

- Busca el primer `\n` en `storage`.
- Duplica el contenido posterior a ese salto de línea.
- Libera la memoria anterior.
- Devuelve el nuevo `storage` actualizado.

Si no queda contenido tras la línea extraída, libera la memoria y devuelve `NULL`.

---

## Justificación del diseño

Este diseño modular permite:

- Separar claramente responsabilidades (lectura, extracción y actualización).
- Mantener el estado entre llamadas mediante una variable estática.
- Garantizar que solo se lee lo necesario hasta encontrar una línea completa.
- Evitar fugas de memoria mediante liberaciones controladas en cada caso de error.
- Funcionar correctamente con cualquier valor válido de `BUFFER_SIZE`.

La complejidad del algoritmo depende del número de lecturas necesarias y de las concatenaciones realizadas, pero cumple los requisitos de eficiencia y gestión de memoria exigidos por el proyecto.


---

## Instrucciones

### Compilación

Es necesario definir el tamaño del buffer mediante la macro `BUFFER_SIZE`:

```bash
cc -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

El programa debe funcionar correctamente con cualquier valor positivo de `BUFFER_SIZE` (por ejemplo: 1, 42, 2048).

### Uso

Cada llamada a:

```c
get_next_line(fd);
```

devuelve la siguiente línea del archivo asociado al descriptor `fd`.

La función devuelve:

* Una cadena con la línea leída.
* `NULL` cuando se alcanza el final del archivo o ocurre un error.

Funciona tanto con archivos como con la entrada estándar (`stdin`).

---

## Recursos

* Manual de la función `read` → `man 2 read`
* Manual de `malloc` y `free` → `man 3 malloc`
* Manuales oficiales de C (man pages):
  [https://man7.org/linux/man-pages/](https://man7.org/linux/man-pages/)

### Uso de Inteligencia Artificial

La inteligencia artificial se ha utilizado únicamente como herramienta de apoyo teórico para:

* Aclarar conceptos como variables estáticas.
* Comprender mejor la gestión de memoria dinámica.
* Revisar explicaciones y documentación.

No se ha utilizado para generar directamente el código del proyecto.

---

```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int		fd;
	int 	i;
	char	*str;

	fd = open("tuta.txt", O_RDONLY);
	i = 1;
	while (i)
	{
		str = get_next_line(fd);
		if (str)
		{
			printf("%s", str);
			free(str);
		}
		else
			i = 0;
	}
	close(fd);
}
```

---

**Escuela:** 42 Madrid
