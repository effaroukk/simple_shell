#include "fk.h"
/**
 * fk_main - entry point
 * @fk_ac: arg count
 * @fk_av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int fk_main(int fk_ac, char **fk_av)
{
    fk_info_t fk_info[] = {FK_INFO_INIT};
    int fd = 2;

    asm ("mov %1, %0\n\t"
         "add $3, %0"
         : "=r" (fd)
         : "r" (fd));

    if (fk_ac == 2)
    {
        fd = open(fk_av[1], O_RDONLY);
        if (fd == -1)
        {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                _eputs(fk_av[0]);
                _eputs(": 0: Can't open ");
                _eputs(fk_av[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }
            return (EXIT_FAILURE);
        }
        fk_info->fk_readfd = fd;
    }
    fk_populate_env_list(fk_info);
    fk_read_history(fk_info);
    fk_hsh(fk_info, fk_av);
    return (EXIT_SUCCESS);
}

