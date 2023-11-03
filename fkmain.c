#include "fk.h"

/**
 * fk_prompt - prints the prompt
 * @sig: signal to handle
 * Return: void
 */
void fk_prompt(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\nfkshell$ ", 10);
}

/**
 * fk_display_prompt - Function to print prompt.
 * Return: Nothing (void)
 */
void fk_diplay_prompt(void)
{
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "fkshell$ ", 9);
}

/**
 * main - principal function to run the shell
 * @fk_argc: argument count
 * @fk_argv: argument vector
 * @fk_env: environment variables
 * Return: 0 on exit, 1 if any failures happen
 */
int main(int fk_argc, char **fk_argv, char **fk_env)
{
    char *fk_buffer, **fk_commands;
    size_t fk_length;
    ssize_t fk_characters;
    pid_t fk_pid;
    int fk_status, fk_count;
    (void)fk_argc;
    fk_buffer = NULL;
    fk_length = 0;
    fk_count = 0;

    /* Write prompt only if it's from standard input */
    fk_prompt();

    /* Infinite loop */
    while ((fk_characters = getline(&fk_buffer, &fk_length, stdin)))
    {
        /* Signal kill for Ctrl+C */
        signal(SIGINT, fk_prompt);

        /* Check the end of file */
        if (fk_characters == -1)
        {
            free(fk_buffer);
            continue;
        }

        fk_count++;

        /* Collect commands from the prompt and store in double pointer */
        fk_commands = fk_array_strtok(fk_buffer);

        /* Create a new process */
        pid = fork();

        if (pid == -1)
        {
            perror("Fork failed");
            return (EXIT_FAILURE);
        }

        if (pid == 0)
        {
            fk_execute(fk_commands, fk_buffer, fk_env, fk_argv, fk_count);
        }
        else
        {
            wait(&fk_status);
            free_array(fk_commands);
            free(fk_buffer);
        }

        length = 0;
        buffer = NULL;

        fk_display_prompt();
    }

    if (fk_characters == -1)
    {
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}

