#include "fk.h"
/**
 * fk_execute - runs
 * @fk_commands: commands to be inputed
 * @fk_env: environment
 * @fk_argv: arguments vector
 * @fk_count: argument count
 */
void fk_execute(char **fk_commands,
		char **fk_env, char **fk_argv, int fk_count)
{
	int opt;

	env_end(fk_env);
	/* Check if command is NULL or empty spaces */
	if (fk_commands == NULL)
		null_command(stdout, fk_count);

	/* Check if command is exit to exit from shell */
	if (strcmp("exit", fk_commands[0]) == 0)
	{
		while ((opt = getopt(fk_count, fk_argv, "a:b:")) != -1)
		{
			switch (opt)
			{
				case 'a':/* handle option 'a'*/
				break;
				case 'b':/* handle option 'b'*/
				break;
			}
		}
	}
	/* Check if the command is ENV to print environment variables */
	else if (strcmp("env", fk_commands[0]) == 0)
	{
		env_end(fk_env);
	}
	/* Check if the command is a full path to an executable file */
	else if (access(fk_commands[0], X_OK) == 0)
	{
		execve(fk_commands[0], fk_commands, NULL);
		perror("execve");
	}
	/* Check all $PATH directories for executable commands */
	else
	_path(fk_commands, fk_env);
}

