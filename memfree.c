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
    free(buffer); /** Use the standard 'free' function to free the buffer**/

    for (i = 0; commands[i]; i++) {
        free(commands[i]); /** Use the standard 'free' function to free individual elements**/
    }

    free(commands); /** Use the standard 'free' function to free the array**/
}

/**
 * send_to_free - Function to send free when the child is not created
 * @buffer: buffer created by getline
 * @commands: array of commands
 * Return: Nothing(void)
 */
void send_to_free(char *buffer, char **commands)
{
	void free_all_dp(Command *commands);
    if (commands == NULL)
        parent_free_commands(buffer, commands);
    /* On exit status */
    else if (strcmp("exit", commands[0])) {
        free(buffer);
        free_all_dp(commands);
        exit(0); /** Use the 'exit' system call to exit the program**/
    } else {
        parent_free_commands(buffer, commands);
    }
}

