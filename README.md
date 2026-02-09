*Este proyecto ha sido creado como parte del currículo de 42 por raqroca-.*

# Get Next Line

## Descripción

**get_next_line** es un proyecto en C cuyo objetivo es implementar una función capaz de leer un archivo (o entrada estándar) línea a línea a partir de un descriptor de archivo (`fd`).

La función principal, `get_next_line`, devuelve una línea completa en cada llamada, incluyendo el salto de línea (`\n`) si existe. El proyecto introduce y refuerza conceptos clave como el uso de **variables estáticas**, la gestión de memoria dinámica y la lectura eficiente con `read()`.

## Objetivo

* Aprender a manejar lectura incremental de archivos.
* Comprender y usar correctamente variables estáticas en C.
* Gestionar memoria sin provocar leaks ni errores.

## Archivos del proyecto

* `get_next_line.c`
* `get_next_line_utils.c`
* `get_next_line.h`


## Prototipo

```c
char *get_next_line(int fd);
```

## Archivos del proyecto

* `get_next_line.c`
* `get_next_line_utils.c`
* `get_next_line.h`

### Bonus

* `get_next_line_bonus.c`
* `get_next_line_utils_bonus.c`
* `get_next_line_bonus.h`

## Instrucciones de compilación

El proyecto se compila definiendo el tamaño del buffer mediante la macro `BUFFER_SIZE`:

```bash
cc -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

El valor de `BUFFER_SIZE` puede variar y el programa debe funcionar correctamente con cualquier valor válido (por ejemplo: 1, 42, 9999).

## Funcionamiento

* Cada llamada a `get_next_line(fd)` devuelve la siguiente línea del archivo.
* Si se alcanza el final del archivo o ocurre un error, la función devuelve `NULL`.
* La función funciona tanto con archivos como con `stdin`.
* No se lee el archivo completo de golpe, solo lo necesario hasta encontrar un `\n`.

## Bonus

La parte bonus añade:

* Soporte para múltiples descriptores de archivo simultáneamente.
* Uso de una sola variable estática.

Esto permite alternar llamadas a `get_next_line` entre distintos `fd` sin perder el estado de lectura de cada uno.

## Recursos

* `man 2 read`
* `man 3 malloc`
* Documentación oficial de C
* Apuntes y debates con otros estudiantes de 42

### Uso de IA

La IA se utilizó únicamente como apoyo teórico y de comprensión (por ejemplo, aclarar conceptos como variables estáticas o gestión de memoria). No se utilizó para generar directamente el código del proyecto.

---

**Escuela**: 42 MADRID