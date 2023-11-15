#include "fk.h"
/**
 * fk_myenv - prints the current environment
 * @fk_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int fk_myenv(fk_info_t *fk_info)
{
    print_list_str(fk_info->fk_env);
    return (0);
}

/**
 * fk_getenv - gets the value of an environ variable
 * @fk_info: Structure containing potential arguments. Used to maintain
 * @fk_name: env var name
 *
 * Return: the value
 */
char *fk_getenv(fk_info_t *fk_info, const char *fk_name)
{
    list_t *fk_node = fk_info->fk_env;
    char *p;

    while (fk_node)
    {
        p = starts_with(fk_node->str, fk_name);
        if (p && *p)
            return (p);
        fk_node = fk_node->next;
    }
    return (NULL);
}

/**
 * fk_mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @fk_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int fk_mysetenv(fk_info_t *fk_info)
{
    if (fk_info->fk_argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (_setenv(fk_info, fk_info->fk_argv[1], fk_info->fk_argv[2]))
        return (0);
    return (1);
}

/**
 * fk_myunsetenv - Remove an environment variable
 * @fk_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int fk_myunsetenv(fk_info_t *fk_info)
{
    int i;

    if (fk_info->fk_argc == 1)
    {
        _eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= fk_info->fk_argc; i++)
        _unsetenv(fk_info, fk_info->fk_argv[i]);

    return (0);
}

/**
 * fk_populate_env_list - populates env linked list
 * @fk_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int fk_populate_env_list(fk_info_t *fk_info)
{
    list_t *fk_node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&fk_node, environ[i], 0);
    fk_info->fk_env = fk_node;
    return (0);
}

