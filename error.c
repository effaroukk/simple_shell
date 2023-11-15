#include "fk.h"

/**
 * fk_eputs - prints an input string
 * @fk_str: the string to be printed
 *
 * Return: Nothing
 */
void fk_eputs(char *fk_str);
{
	int fk_i = 0;

	if (!fk_str)
	return;
	while (fk_str[fk_i] != '\0')
	{
		fk_eputchar(fk_str[fk_i]);
		fk_i++;
	}
}

/**
 * fk_eputchar - writes the character c to stderr
 * @fk_c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int fk_eputchar(char fk_c)
{
	static int fk_i;
	static char fk_buf[WRITE_BUF_SIZE];

	if (fk_c == BUF_FLUSH || fk_i >= WRITE_BUF_SIZE)
	{
		write(2, fk_buf, fk_i);
		fk_i = 0;
	}
	if (fk_c != BUF_FLUSH)
	fk_buf[fk_i++] = fk_c;
	return (1);
}

/**
 * fk_putfd - writes the character c to given fd
 * @fk_c: The character to print
 * @fk_fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int fk_putfd(char fk_c, int fk_fd)
{
	static int fk_i;
	static char fk_buf[WRITE_BUF_SIZE];

	if (fk_c == BUF_FLUSH || fk_i >= WRITE_BUF_SIZE)
	{
		write(fk_fd, fk_buf, fk_i);
		fk_i = 0;
	}
	if (fk_c != BUF_FLUSH)
	fk_buf[fk_i++] = fk_c;
	return (1);
}

/**
 * fk_putsfd - prints an input string
 * @fk_str: the string to be printed
 * @fk_fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int fk_putsfd(char *fk_str, int fk_fd)
{
	int fk_i = 0;

	if (!fk_str)
	return (0);
	while (*fk_str)
	{
	fk_i += fk_putfd(*fk_str++, fk_fd);
	}
	return (fk_i);
}

