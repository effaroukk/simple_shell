#include "fk.h"
/**
 * fk_print_env - Function to print all environment variables
 * @environ: environment variables for the user
 * Return: Nothing(void)
 */
void fk_print_env(char **environ)
{
	unsigned int fk_i = 0, fk_length;

	while (environ[fk_i])
	{
		fk_length = strlen(environ[fk_i]);
		write(STDOUT_FILENO, environ[fk_i], fk_length);
		write(STDOUT_FILENO, "\n", 1);
		fk_i++;
	}
}

