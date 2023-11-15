#include "fk.h"
/**
 * fk_myexit - exits the shell
 * @fk_info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if fk_info->fk_argv[0] != "exit"
 */
int fk_myexit(fk_info_t *fk_info)
{
    int exitcheck;

    if (fk_info->fk_argv[1]) /* If there is an exit argument */
    {
        exitcheck = fk_erratoi(fk_info->fk_argv[1]);
        if (exitcheck == -1)
        {
            fk_info->fk_status = 2;
            fk_print_error(fk_info, "Illegal number: ");
            _eputs(fk_info->fk_argv[1]);
            _eputchar('\n');
            return (1);
        }
        fk_info->fk_err_num = fk_erratoi(fk_info->fk_argv[1]);
        return (-2);
    }
    fk_info->fk_err_num = -1;
    return (-2);
}

/**
 * fk_mycd - changes the current directory of the process
 * @fk_info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int fk_mycd(fk_info_t *fk_info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        _puts("TODO: >>getcwd failure emsg here<<\n");
    if (!fk_info->fk_argv[1])
    {
        dir = fk_getenv(fk_info, "HOME=");
        if (!dir)
            chdir_ret = /* TODO: what should this be? */
                chdir((dir = fk_getenv(fk_info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (_strcmp(fk_info->fk_argv[1], "-") == 0)
    {
        if (!fk_getenv(fk_info, "OLDPWD="))
        {
            _puts(s);
            _putchar('\n');
            return (1);
        }
        _puts(fk_getenv(fk_info, "OLDPWD=")), _putchar('\n');
        chdir_ret = /* TODO: what should this be? */
            chdir((dir = fk_getenv(fk_info, "OLDPWD=")) ? dir : "/");
    }
    else
        chdir_ret = chdir(fk_info->fk_argv[1]);
    if (chdir_ret == -1)
    {
        fk_print_error(fk_info, "can't cd to ");
        _eputs(fk_info->fk_argv[1]), _eputchar('\n');
    }
    else
    {
        fk_setenv(fk_info, "OLDPWD", fk_getenv(fk_info, "PWD="));
        fk_setenv(fk_info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * fk_myhelp - changes the current directory of the process
 * @fk_info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int fk_myhelp(fk_info_t *fk_info)
{
    char **arg_array;

    arg_array = fk_info->fk_argv;
    _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*arg_array); /* temp att_unused workaround */
    return (0);
}

