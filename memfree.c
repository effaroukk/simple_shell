#include "fk.h"

/**
 * parent_free_commands - free the buffer and the commands
 * @buffer: buffer in getline
 * @commands: double pointer that store all the commands inserted
 * Return: Nothing(void)
 */
void parent_free_commands(char *buffer, char **commands)
{
	unsigned int i;

	free(buffer);

	for (i = 0; commands[i]; i++)
	{
		free(commands[i]);
	}

	free(commands);
}

/**
 * send_to_free - Function to send free when the child is not created
 * @buffer: buffer created by getline
 * @commands: array of commands
 * Return: Nothing(void)
 */
void send_to_free(char *buffer, char **commands)
{
	char **fk_directories = NULL;

	free_all_dp(fk_directories);

	if (commands == NULL)
	parent_free_commands(buffer, commands);

	else if (strcmp("exit", commands[0]))
	{
		free(buffer);
		free_all_dp(commands);
		exit(0);
	}
	else
	{
		parent_free_commands(buffer, commands);
	}
}

