#include "fk.h"

/**
 * fk_find_num_dir - Function to find the total number of directories
 * @fk_path: path string
 * Return: number of directories in the path
 */
unsigned int fk_find_num_dir(char *fk_path)
{
    unsigned int fk_i = 0, fk_flag = 0, fk_num_dir = 0;

    while (fk_path[fk_i])
    {
        if (fk_path[fk_i] != ':')
            fk_flag = 1;

        if ((fk_flag && fk_path[fk_i + 1] == ':') || (fk_flag && fk_path[fk_i + 1] == '\0'))
        {
            fk_num_dir++;
            fk_flag = 0;
        }
        fk_i++;
    }

    return fk_num_dir;
}

/**
 * fk_store_e_variables - Function that creates a double pointer array, where stores
 * each path directory as a pointer
 * @fk_fir_com: first command inserted in the prompt
 * @environ: environment variables
 * Return: environment
 */
char **fk_store_e_variables(char *fk_fir_com)
{
    char **fk_directories, *fk_path_env, *fk_directory;
    unsigned int fk_length, fk_i = 0;
    int fk_dir_length, fk_command_length;

    fk_path_env = getenv("PATH");
    fk_length = fk_find_num_dir(fk_path_env);
    fk_directories = malloc(sizeof(char *) * (fk_length + 1));
    if (fk_directories == NULL)
        return (NULL);

    fk_directory = strtok(fk_path_env, ":");

    while (fk_directory != NULL)
    {
        fk_dir_length = strlen(fk_directory);
        fk_command_length = strlen(fk_fir_com);
        fk_directories[fk_i] = malloc(sizeof(char *) * (fk_dir_length + fk_command_length + 2));
        if (fk_directories[fk_i] == NULL)
        {
            free_all_dp(fk_directories);
            return (NULL);
        }
        _strncpcommand(fk_directories[fk_i], fk_directory, fk_fir_com, fk_dir_length, fk_command_length);
        fk_i++;
        fk_directory = strtok(NULL, ":");
    }

    fk_directories[fk_i] = NULL;

    return (fk_directories);
}

/**
 * fk_getenv - Function to get the environment variable
 * @name: name of the environment variable
 * @environ: environment variables
 * Return: the value associated with the variable
 */
char *fk_getenv(const char *name, char **environ)
{
    char *fk_env_value, *fk_cp_name;
    unsigned int fk_i = 0, fk_length;


    fk_cp_name = malloc(sizeof(char) * fk_length + 1);
    if (fk_cp_name == NULL)
        return (NULL);

    /*copy the contents of the name argument to cp_name*/
    strcpy(fk_cp_name, name);

    /*finding the environment variable*/
    fk_env_value = strtok(environ[fk_i], "=");
    while (environ[fk_i])
    {
        if (strcmp(fk_env_value, fk_cp_name))
        {
            fk_env_value = strtok(NULL, "\n");
            free(fk_cp_name);
            return fk_env_value;
        }
        fk_i++;
        fk_env_value = strtok(environ[fk_i], "=");
    }
    free(fk_cp_name);
    return NULL;
}

/**
 * fk_print_env - Function to print all environment variables
 * @environ: environment variables for the user
 * Return: Nothing(void)
 */
void fk_print_env(char **environ)
{
    unsigned int fk_i = 0, fk_length;

    while (environ[fk_i])
    {
        fk_length = strlen(environ[fk_i]);
        write(STDOUT_FILENO, environ[fk_i], fk_length);
        write(STDOUT_FILENO, "\n", 1);
        fk_i++;
    }
}

