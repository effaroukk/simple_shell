#include "fk.h"
/**
 * fk_myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @fk_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int fk_myhistory(fk_info_t *fk_info)
{
    print_list(fk_info->fk_history);
    return (0);
}

/**
 * fk_unset_alias - sets alias to string
 * @fk_info: parameter struct
 * @fk_str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int fk_unset_alias(fk_info_t *fk_info, char *fk_str)
{
    char *p, c;
    int ret;

    p = _strchr(fk_str, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = delete_node_at_index(&(fk_info->fk_alias),
                               get_node_index(fk_info->fk_alias, node_starts_with(fk_info->fk_alias, fk_str, -1)));
    *p = c;
    return (ret);
}

/**
 * fk_set_alias - sets alias to string
 * @fk_info: parameter struct
 * @fk_str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int fk_set_alias(fk_info_t *fk_info, char *fk_str)
{
    char *p;

    p = _strchr(fk_str, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (fk_unset_alias(fk_info, fk_str));

    fk_unset_alias(fk_info, fk_str);
    return (add_node_end(&(fk_info->fk_alias), fk_str, 0) == NULL);
}

/**
 * fk_print_alias - prints an alias string
 * @fk_node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int fk_print_alias(list_t *fk_node)
{
    char *p = NULL, *a = NULL;

    if (fk_node)
    {
        p = _strchr(fk_node->str, '=');
        for (a = fk_node->str; a <= p; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * fk_myalias - mimics the alias builtin (man alias)
 * @fk_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int fk_myalias(fk_info_t *fk_info)
{
    int i = 0;
    char *p = NULL;
    list_t *fk_node = NULL;

    if (fk_info->fk_argc == 1)
    {
        fk_node = fk_info->fk_alias;
        while (fk_node)
        {
            fk_print_alias(fk_node);
            fk_node = fk_node->next;
        }
        return (0);
    }
    for (i = 1; fk_info->fk_argv[i]; i++)
    {
        p = _strchr(fk_info->fk_argv[i], '=');
        if (p)
            fk_set_alias(fk_info, fk_info->fk_argv[i]);
        else
            fk_print_alias(node_starts_with(fk_info->fk_alias, fk_info->fk_argv[i], '='));
    }

    return (0);
}

