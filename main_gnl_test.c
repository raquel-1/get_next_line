/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gnl_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raqroca- <raqroca-@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:46:44 by raqroca-          #+#    #+#             */
/*   Updated: 2026/02/17 15:46:49 by raqroca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*           //2048     4     1                                                                 */
/*   main_gnl_test.c                                                          */
/*   Tester completo para la evaluación de get_next_line (42)                 */
/*                                                                            */
/*   Compilar (obligatoria):                                                  */
/*     cc -Wall -Wextra -Werror -D BUFFER_SIZE=42                             */
/*        get_next_line.c get_next_line_utils.c main_gnl_test.c -o gnl_test  */
/*                                                                            */
/*   Compilar (bonus, cambia los includes abajo):                             */
/*     cc -Wall -Wextra -Werror -D BUFFER_SIZE=42                             */
/*        get_next_line_bonus.c get_next_line_utils_bonus.c                   */
/*        main_gnl_test.c -o gnl_test                                         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line.h"
/* Si evalúas el BONUS comenta la línea de arriba y descomenta esta: */
/* #include "get_next_line_bonus.h"                                  */

/* ── Colores ── */
#define RED    "\033[1;31m"
#define GREEN  "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN   "\033[1;36m"
#define RESET  "\033[0m"

static void	print_separator(const char *title)
{
	printf(CYAN "\n══════════════════════════════════════════\n" RESET);
	printf(CYAN "  %s\n" RESET, title);
	printf(CYAN "══════════════════════════════════════════\n" RESET);
}

static void	print_line(int n, char *line)
{
	if (!line)
		printf(YELLOW "  Línea %d: " RESET RED "NULL\n" RESET, n);
	else
		printf(YELLOW "  Línea %d: " RESET GREEN "\"%s\"\n" RESET, n, line);
}

static void	read_all_lines(int fd)
{
	char	*line;
	int		i;

	i = 1;
	while (1)
	{
		line = get_next_line(fd);
		print_line(i++, line);
		if (!line)
			break ;
		free(line);
	}
}

/* ── TEST 1: fd inválido ── */
static void	test_invalid_fd(void)
{
	char	*line;

	print_separator("TEST 1 - fd inválido (fd=42, sin abrir)");
	line = get_next_line(42);
	if (!line)
		printf(GREEN "  PASS: devolvió NULL correctamente.\n" RESET);
	else
	{
		printf(RED "  FAIL: devolvió \"%s\" en lugar de NULL.\n" RESET, line);
		free(line);
	}
}

/* ── TEST 2: fd negativo ── */
static void	test_negative_fd(void)
{
	char	*line;

	print_separator("TEST 2 - fd negativo (fd=-1)");
	line = get_next_line(-1);
	if (!line)
		printf(GREEN "  PASS: devolvió NULL correctamente.\n" RESET);
	else
	{
		printf(RED "  FAIL: devolvió \"%s\" en lugar de NULL.\n" RESET, line);
		free(line);
	}
}

/* ── TEST 3: múltiples líneas normales ── */
static void	test_file_multiline(void)
{
	int		fd;

	print_separator("TEST 3 - Archivo con múltiples líneas normales");
	fd = open("test_files/multiline.txt", O_RDONLY);
	if (fd < 0)
	{
		printf(RED "  ERROR: No se pudo abrir multiline.txt\n" RESET);
		return ;
	}
	read_all_lines(fd);
	close(fd);
}

/* ── TEST 4: líneas largas (> 2000 chars) ── */
static void	test_long_lines(void)
{
	int		fd;

	print_separator("TEST 4 - Líneas largas (> 2000 chars)");
	fd = open("test_files/longlines.txt", O_RDONLY);
	if (fd < 0)
	{
		printf(RED "  ERROR: No se pudo abrir longlines.txt\n" RESET);
		return ;
	}
	read_all_lines(fd);
	close(fd);
}

/* ── TEST 5: líneas cortas (< 4 chars, incluso 1) ── */
static void	test_short_lines(void)
{
	int		fd;

	print_separator("TEST 5 - Líneas cortas (< 4 chars, incluso 1 char)");
	fd = open("test_files/shortlines.txt", O_RDONLY);
	if (fd < 0)
	{
		printf(RED "  ERROR: No se pudo abrir shortlines.txt\n" RESET);
		return ;
	}
	read_all_lines(fd);
	close(fd);
}

/* ── TEST 6: líneas vacías ── */
static void	test_empty_lines(void)
{
	int		fd;

	print_separator("TEST 6 - Líneas vacías mezcladas con contenido");
	fd = open("test_files/emptylines.txt", O_RDONLY);
	if (fd < 0)
	{
		printf(RED "  ERROR: No se pudo abrir emptylines.txt\n" RESET);
		return ;
	}
	read_all_lines(fd);
	close(fd);
}

/* ── TEST 7: última línea SIN \n al final ── */
static void	test_no_newline_at_eof(void)
{
	int		fd;

	print_separator("TEST 7 - Última línea SIN \\n al final");
	fd = open("test_files/no_newline_eof.txt", O_RDONLY);
	if (fd < 0)
	{
		printf(RED "  ERROR: No se pudo abrir no_newline_eof.txt\n" RESET);
		return ;
	}
	read_all_lines(fd);
	close(fd);
	printf(YELLOW "  >>> La ÚLTIMA línea NO debe tener \\n\n" RESET);
}

/* ── TEST 8: archivo vacío ── */
static void	test_empty_file(void)
{
	int		fd;
	char	*line;

	print_separator("TEST 8 - Archivo vacío");
	fd = open("test_files/empty.txt", O_RDONLY);
	if (fd < 0)
	{
		printf(RED "  ERROR: No se pudo abrir empty.txt\n" RESET);
		return ;
	}
	line = get_next_line(fd);
	if (!line)
		printf(GREEN "  PASS: archivo vacío devolvió NULL correctamente.\n" RESET);
	else
	{
		printf(RED "  FAIL: devolvió \"%s\" en lugar de NULL.\n" RESET, line);
		free(line);
	}
	close(fd);
}

/* ── TEST 9: stdin ── */
static void	test_stdin(void)
{
	char	*line;

	print_separator("TEST 9 - Lectura desde stdin");
	printf("  Escribe una línea y pulsa Enter (Ctrl+D para EOF):\n  > ");
	fflush(stdout);
	line = get_next_line(STDIN_FILENO);
	print_line(1, line);
	if (line)
		free(line);
}

/* ════════════════════════════════════════════════════════
   BONUS - MÚLTIPLES FD SIMULTÁNEOS
   Descomenta test_multiple_fd() y su llamada en main()
   SOLO si evalúas a alguien que tiene el bonus
   ════════════════════════════════════════════════════════ */

/*
static void	test_multiple_fd(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line1;
	char	*line2;
	char	*line3;
	int		i;

	print_separator("BONUS - Múltiples fd simultáneos");
	fd1 = open("test_files/multiline.txt", O_RDONLY);
	fd2 = open("test_files/shortlines.txt", O_RDONLY);
	fd3 = open("test_files/longlines.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
	{
		printf(RED "  ERROR: No se pudieron abrir los archivos.\n" RESET);
		if (fd1 >= 0) close(fd1);
		if (fd2 >= 0) close(fd2);
		if (fd3 >= 0) close(fd3);
		return ;
	}
	i = 1;
	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);
		if (!line1 && !line2 && !line3)
			break ;
		printf(YELLOW "  Ronda %d:\n" RESET, i++);
		printf("    fd1: ");
		if (line1) { printf(GREEN "\"%s\"\n" RESET, line1); free(line1); }
		else        printf(RED "NULL\n" RESET);
		printf("    fd2: ");
		if (line2) { printf(GREEN "\"%s\"\n" RESET, line2); free(line2); }
		else        printf(RED "NULL\n" RESET);
		printf("    fd3: ");
		if (line3) { printf(GREEN "\"%s\"\n" RESET, line3); free(line3); }
		else        printf(RED "NULL\n" RESET);
	}
	close(fd1);
	close(fd2);
	close(fd3);
	printf(CYAN "\n  Mezclando con fd inexistente (fd=999):\n" RESET);
	fd1 = open("test_files/multiline.txt", O_RDONLY);
	line1 = get_next_line(fd1);
	line2 = get_next_line(999);
	printf("    fd1 válido:  ");
	if (line1) { printf(GREEN "\"%s\"\n" RESET, line1); free(line1); }
	else        printf(RED "NULL\n" RESET);
	printf("    fd=999 inv:  ");
	if (!line2) printf(GREEN "NULL (correcto)\n" RESET);
	else        { printf(RED "FAIL: \"%s\"\n" RESET, line2); free(line2); }
	close(fd1);
}
*/

/* ── Genera los archivos de test automáticamente ── */
static void	create_test_files(void)
{
	FILE	*f;
	char	longline[2100];

	system("mkdir -p test_files");

	f = fopen("test_files/multiline.txt", "w");
	if (f)
	{
		fprintf(f, "Primera línea del archivo\n");
		fprintf(f, "Segunda línea del archivo\n");
		fprintf(f, "Tercera línea del archivo\n");
		fprintf(f, "Cuarta línea del archivo\n");
		fclose(f);
	}
	f = fopen("test_files/longlines.txt", "w");
	if (f)
	{
		memset(longline, 'A', 2050);
		longline[2050] = '\n';
		longline[2051] = '\0';
		fputs(longline, f);
		memset(longline, 'B', 2050);
		longline[2050] = '\n';
		longline[2051] = '\0';
		fputs(longline, f);
		fclose(f);
	}
	f = fopen("test_files/shortlines.txt", "w");
	if (f)
	{
		fprintf(f, "a\n");
		fprintf(f, "bb\n");
		fprintf(f, "ccc\n");
		fprintf(f, "x\n");
		fclose(f);
	}
	f = fopen("test_files/emptylines.txt", "w");
	if (f)
	{
		fprintf(f, "\n");
		fprintf(f, "línea con contenido\n");
		fprintf(f, "\n");
		fprintf(f, "\n");
		fprintf(f, "otra línea\n");
		fclose(f);
	}
	f = fopen("test_files/no_newline_eof.txt", "w");
	if (f)
	{
		fprintf(f, "línea uno\n");
		fprintf(f, "línea dos\n");
		fprintf(f, "línea tres SIN newline");
		fclose(f);
	}
	f = fopen("test_files/empty.txt", "w");
	if (f)
		fclose(f);

	printf(GREEN "  Archivos de test creados en ./test_files/\n" RESET);
	printf(CYAN "  BUFFER_SIZE compilado = %d\n" RESET, BUFFER_SIZE);
}

int	main(void)
{
	printf(CYAN "\n╔══════════════════════════════════════════╗\n" RESET);
	printf(CYAN "║     TESTER COMPLETO - GET_NEXT_LINE      ║\n" RESET);
	printf(CYAN "╚══════════════════════════════════════════╝\n" RESET);

	print_separator("Generando archivos de test...");
	create_test_files();

	test_invalid_fd();
	test_negative_fd();
	test_file_multiline();
	test_long_lines();
	test_short_lines();
	test_empty_lines();
	test_no_newline_at_eof();
	test_empty_file();
	test_stdin();

	/* BONUS: descomenta esto si evalúas a alguien con el bonus */
	/* test_multiple_fd(); */

	printf(CYAN "\n══════════════════════════════════════════\n" RESET);
	printf(CYAN "  Tests finalizados. ¡Revisa los resultados!\n" RESET);
	printf(CYAN "══════════════════════════════════════════\n\n" RESET);
	return (0);
}
