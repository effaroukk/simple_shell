#include "fk.h"

/**
* fk_execute - Function to verify and execute every command
*@fk_commands: command get
*@fk_buffer: command in getline
*@fk_env: enviroment variable
*@fk_argv: argument counter
*@fk_count: number of times that executed
*Return: Nothing(void)
*/

void fk_execute(char **fk_commands, char *fk_buffer,
		char **fk_env, char **fk_argv, int fk_count)
{
    struct stat fk_fileStat;

    /* Check if command is NULL or empty spaces */
    if (fk_commands == NULL)
        null_command(stdout, fk_buffer, fk_count);
    /* Check if command is exit to exit from shell */
    else if (strcmp("exit", fk_commands[0]))
        getopt(fk_buffer, fk_commands);
    /* Check if the command is ENV to print environment variables */
    else if (strcmp("env", fk_commands[0]))
        env_end(fk_buffer, fk_commands, fk_env);
    /* Check if the command is a full path to an executable file */
    else if (access(fk_commands[0], X_OK) == 0)
    {
        execve(fk_commands[0], fk_commands, NULL);
        perror("execve");
    }
    /* Check all $PATH directories for executable commands */
    else
        _path(fk_commands, fk_buffer, fk_env, fk_argv, fk_count);
}

