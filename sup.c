#include "fk.h"
/**
 * fk_myenv - prints the current environment
 * @fk_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int fk_myenv(info_t *fk_info)
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
char *fk_getenv(info_t *fk_info, const char *fk_name)
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
int fk_mysetenv(info_t *fk_info)
{
	if (fk_info != NULL && fk_info->fk_argv != NULL)
	{
		if (fk_info->fk_argv[1] != NULL && fk_info->fk_argv[2] != NULL)
		{
			const char *env_var_name = fk_info->fk_argv[1];
			const char *env_var_value = fk_info->fk_argv[2];

		if (setenv(env_var_name, env_var_value, 1) != 0)
			return (1);
		}
}

/**
 * fk_myunsetenv - Remove an environment variable
 * @fk_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int fk_myunsetenv(info_t *fk_info)
{
	int i;

	if (fk_info->fk_argc == 1)
	{
		fk_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 0; fk_info->fk_argv[i] != NULL; i++)
	{
		const char *env_var_name = fk_info->fk_argv[i];
		unsetenv(env_var_name);

	return (0);
	}
}
/**
 * fk_populate_env_list - populates env linked list
 * @fk_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int fk_populate_env_list(info_t *fk_info)
{
	list_t *fk_node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	{
	add_node_end(&fk_node, environ[i], 0);
	fk_info->fk_env = fk_node;
	}
	return (0);
}

