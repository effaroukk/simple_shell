#include "fk.h"

/**
 * fk_fork_fail - function that handles a fork fail
 * Return: Nothing
 */
void fk_fork_fail(void)
{
	perror("Error: ");
	exit(EXIT_FAILURE);
}
/**
 * fk_build_message - Function to write an error message
 * @av: argument vector
 * @fk_fir_com: first command to print if not found
 * @count: number of times executed
 * Return: Nothing(void)
 */
void fk_build_message(char **av, char *fk_fir_com, int count)
{
	int num_length = 1, cp, mult = 1;

	write(STDERR_FILENO, av[0], strlen(av[0]));
	write(STDERR_FILENO, ": ", 2);
	cp = count;

	while (cp >= 10)
	{
		cp /= 10;
		mult *= 10;
		num_length++;
	}
	while (num_length > 1)
	{
		if ((count / mult) < 10)
			_fk_puterror((count / mult + '0'));
		else
			_fk_puterror((count / mult) % 10 + '0');
		--num_length;
		mult /= 10;
	}
	_fk_puterror(count % 10 + '0');
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, fk_fir_com, strlen(fk_fir_com));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * _fk_puterror - Prints a char
 * @c: character to write
 * Return: int to print
 */
int _fk_puterror(char c)
{
	write(STDERR_FILENO, &c, 1);
	return (0);
}
/**
 * fk_end_file - function to control the interrupt signal
 * @buffer: buffer array created by new line
 * Return: Nothing(void)
 */
void fk_end_file(char *buffer)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(buffer);
	exit(0);
}
