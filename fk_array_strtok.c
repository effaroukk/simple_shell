#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * fk_array_strtok - Tokenizes a string into an array of strings
 * @str: The input string to tokenize
 * Return: An array of strings
 */
char **fk_array_strtok(char *str)
{
    const char *delimiters = " \t\n\r";  /*You can customize delimiters as needed*/
    char **tokens = NULL;
    size_t token_count = 0;

    char *token = strtok(str, delimiters);
    while (token != NULL)
    {
        tokens = realloc(tokens, sizeof(char *) * (token_count + 1));
        if (tokens == NULL)
        {
            perror("realloc");
            exit(EXIT_FAILURE);
        }

        tokens[token_count] = strdup(token);
        if (tokens[token_count] == NULL)
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }

        token_count++;
        token = strtok(NULL, delimiters);
    }

    tokens = realloc(tokens, sizeof(char *) * (token_count + 1));
    if (tokens == NULL)
    {
        perror("realloc");
        exit(EXIT_FAILURE);
    }

    tokens[token_count] = NULL;  /*Null-terminate the array*/

    return tokens;
}

