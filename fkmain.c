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
	char *path = getenv("PATH");
	char *fk_buffer, **fk_commands;
	size_t fk_length;
	ssize_t fk_characters;
	pid_t pid;
	int fk_status, fk_count;
	(void)fk_argc;
	fk_buffer = NULL;
	fk_length = 0;
	fk_count = 0;

	if (path != NULL)
	{
		char *token = strtok(path, ":");

		while (token != NULL)
		{
			printf("Directory: %s\n", token);
			token = strtok(NULL, ":");
		}
	}
	else
	{
		printf("PATH environment variable not found.\n");
	}
	while ((fk_characters = getline(&fk_buffer, &fk_length, stdin)))
	{
		signal(SIGINT, fk_prompt);

		if (fk_characters == -1)
		{
			free(fk_buffer);
			continue;
		}
		fk_count++;

		fk_commands = fk_array_strtok(fk_buffer);

		pid = fork();

		if (pid == -1)
		{
			perror("Fork failed");
			return (EXIT_FAILURE);
		}
		if (pid == 0)
		{
			fk_execute(fk_commands, fk_env, fk_argv, fk_count);
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
