#include "fk.h"

/**
 * fk_prompt - prints the prompt
 * @cmd: command to be handled
 * Return: void
 */
void fk_prompt(int cmd)
{
	(void)cmd;
	write(STDOUT_FILENO, "\nfkshell$ ", 10);
}
/**
 * fk_display_prompt - displas a prompt to the user
 *
 * Return: nothing
 */
void fk_display_prompt(void)
{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "fkshell$ ", 9);
}
/**
 * free_array - frees memory allocated for an array of strings
 * @arr: the array of strings to be freed
 */
void free_array(char **arr)
{
	int i;

	if (arr == NULL)
		return;
	for (i = 0; arr[i] != NULL; i++)
	{
		free(arr[i]);
	}
	free(arr);
}

/**
 * main - principal function to run the shell
 * @fk_argc: argument count
 * @fk_argv: argument vector
 * @fk_env: environment variables
 * Return: 0 on exit, 1 if any failures happen
 */
int main(int fk_argc, char **fk_argv, char **fk_env);
int main(int fk_argc, char **fk_argv, char **fk_env)
{
	char *fk_buffer, **fk_commands;
	size_t fk_length;
	ssize_t fk_characters;
	pid_t pid;
	int fk_status, fk_count;
	(void)fk_argc;
	fk_buffer = NULL;
	fk_length = 0;
	fk_count = 0;



	while ((fk_characters = getline(&fk_buffer, &fk_length, stdin)))
	{/* Signal kill for Ctrl+C */
		signal(SIGINT, fk_prompt);

		if (fk_characters == -1)/* Check the end of file */
		{
			free(fk_buffer);
			continue;
		}
		fk_count++;
		/* Collect commands from the prompt and store in double pointer */
		fk_commands = fk_array_strtok(fk_buffer);

		pid = fork(); /* Create a new process */

		if (pid == -1)
		{
			perror("Fork failed");
			return (EXIT_FAILURE);
		}
		if (pid == 0)
		{
			fk_execute(fk_commands, fk_buffer,
					fk_env, fk_argv, fk_count);
		}
		else
		{
			wait(&fk_status);
			free_array(fk_commands);
			free(fk_buffer);
		}
		fk_length = 0;
		fk_buffer = NULL;
	}
	if (fk_characters == -1)
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
/**
 * fk_strncpcommand - Function that copies the path and appends a / and command
 * @dest: destination to save
 * @src: source
 * @command: command to append
 * @n: length of destination
 * @c: length of command
 * Return: address of dest
 */
char *fk_strncpcommand(char *dest, char *src, char *command, int n, int c)
{
	int fk_i, fk_j;

	for (fk_i = 0; fk_i < n && src[fk_i] != '\0'; fk_i++)
		dest[fk_i] = src[fk_i];
	/*append "/" and "command" to the src*/
	dest[fk_i] = '/';
	fk_i++;
	for (fk_j = 0; fk_j < c && command[fk_j] != '\0'; fk_j++, fk_i++)
		dest[fk_i] = command[fk_j];
	dest[fk_i] = '\0';
	return (dest);
}
