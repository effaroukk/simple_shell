#include "fk.h"


extern char** environ; // Include the external environment variable array

void fkPutPrompt() {
    char *prompt = "Enter a command: ";
    write(STDOUT_FILENO, prompt, strlen(prompt));
}

int fkExecuteCommand(const char *command, char *envp[]) {
    if (fork() == 0) {
        // Child process
        char *path = "/usr/bin/"; // You can adjust this to your needs
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s%s", path, command);

        char *argv[] = {command, NULL};
        execve(full_path, argv, envp); // Pass the envp argument

        // If execve fails, print an error message and exit
        if (access(full_path, F_OK) == -1) {
            write(STDOUT_FILENO, "Command not found\n", 18);
        } else {
            write(STDOUT_FILENO, "Command execution failed\n", 26);
        }

        _exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        wait(&status);
        return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }
}


