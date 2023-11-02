#include "fk.h"
/*
 *main - the entry point of the program
 *
 *Return: zero (0) on success
 */

int main(void)
{
	struct stat fkshellStat;

	if (isatty(STDIN_FILENO) == 0 || fstat(STDIN_FILENO, &fkshellStat) == -1)
	{
		write(STDOUT_FILENO, "no such file/directory found\n", 31);
		return (1);
	}
	while (1)
	{
        char *cmd = NULL;
        size_t buf_size = 0;

        fkPutPrompt();
        fflush(stdout);

        if (getline(&cmd, &buf_size, stdin) == -1)
	{
            if (feof(stdin)) {
                write(STDOUT_FILENO, "\nCtrl+D pressed. Exiting.\n", 27);
                break;
            }
            perror("getline");
            _exit(EXIT_FAILURE);
        }

        // Remove the trailing newline character
        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }

        int result = fkExecuteCommand(command, environ); // Pass the environment variable array

        free(command);
    }

    return 0;
}
