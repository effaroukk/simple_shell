#include "fk.h"

/**
 * null_command - a function that writes to the stream
 * @stream: the output
 * @count: argument count
 */
void null_command(FILE *stream, int count)
{
	fprintf(stream, "Error: Null or empty
			command in execution attempt #%d\n", count);
}


/**
 * env_end - end of env
 *@env: environmet
 */
void env_end(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}
/**
 * _path - the path
 * @commands: commands to input
 * @env: the environment
 */
void _path(char **commands, char **env);
void _path(char **commands, char **env)
{
	char *token;
	char *path_copy;
	char *path = getenv("PATH");

	if (path == NULL)
	{
		fprintf(stderr, "Error: PATH environment variable not set\n");
		return;
	}
	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("strdup");
		return;
	}
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		char *full_path = malloc(strlen
				(token) + 1 + strlen(commands[0]) + 1);

		if (full_path == NULL)
		{
			perror("malloc");
			free(path_copy);
			return;
		}

		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, commands[0]);
		/* Check if the executable exists in the current directory*/
		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, commands, env);
			perror("execve");
			free(full_path);
			free(path_copy);
			return;
		}
		free(full_path);
		/* Move to the next directory in $PATH*/
		token = strtok(NULL, ":");
	}
	/* If we reach here, the executable was not found in any $PATH directory*/
	fprintf(stderr, "Error: Command not found in $PATH\n");
	free(path_copy);
`}
