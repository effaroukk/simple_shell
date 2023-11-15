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
	info_t fk_info[] = {FK_INFO_INIT};
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
		fk_eputs(fk_av[0]);
		fk_eputs(": 0: Can't open ");
		fk_eputs(fk_av[1]);
		fk_eputchar('\n');
		fk_eputchar(BUF_FLUSH);
		exit(127);
		}
		return (EXIT_FAILURE);
	}
	fk_info->readfd = fd;
	}
	fk_populate_env_list(fk_info);
	fk_myhistory(fk_info);
	fk_hsh(fk_info, fk_av);
	return (EXIT_SUCCESS);
}

