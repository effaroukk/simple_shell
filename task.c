#include "fk.h"
/**
 * fk_erratoi - converts a string to an integer
 * @fk_s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int fk_erratoi(char *fk_s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*fk_s == '+')
		fk_s++;

	for (i = 0; fk_s[i] != '\0'; i++)
	{
		if (fk_s[i] >= '0' && fk_s[i] <= '9')
		{
			result *= 10;
			result += (fk_s[i] - '0');
		if (result > INT_MAX)
			return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * fk_print_error - prints an error message
 * @fk_info: the parameter & return info struct
 * @fk_estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void fk_print_error(info_t *fk_info, char *fk_estr)
{
	fk_eputs(fk_info->fk_fname);
	fk_eputs(": ");
	printf("%d", fk_info->fk_line_count);
	fk_eputs(": ");
	fk_eputs(fk_info->fk_argv[0]);
	fk_eputs(": ");
	fk_eputs(fk_estr);
}

/**
 * fk_print_d - function prints a decimal (integer) number (base 10)
 * @fk_input: the input
 * @fk_fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int fk_print_d(int fk_input, int fk_fd)
{
	int (*__putchar)(char) = __putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fk_fd == STDERR_FILENO)
		__putchar = __putchar;

	if (fk_input < 0)
	{
		_abs_ = -fk_input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = fk_input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
	if (_abs_ / i)
	{
		__putchar('0' + current / i);
		count++;
	}
	current %= i;
	}
		__putchar('0' + current);
		count++;

	return (count);
}

/**
 * fk_convert_number - converter function, a clone of itoa
 * @fk_num: number
 * @fk_base: base
 * @fk_flags: argument flags
 *
 * Return: string
 */
char *fk_convert_number(long int fk_num, int fk_base, int fk_flags)
{
	static char *fk_array;
	static char fk_buffer[50];
	char sign = 0;
	char *fk_ptr;
	unsigned long fk_n = fk_num;

	if (!(fk_flags & CONVERT_UNSIGNED) && fk_num < 0)
	{
		fk_n = -fk_num;
		sign = '-';
	}

	fk_array = fk_flags & CONVERT_LOWERCASE ?
		"0123456789abcdef" : "0123456789ABCDEF";
	fk_ptr = &fk_buffer[49];
	*fk_ptr = '\0';

	do {
		*--fk_ptr = fk_array[fk_n % fk_base];
		fk_n /= fk_base;
	} while (fk_n != 0);

	if (sign)
		*--fk_ptr = sign;
	return (fk_ptr);
}

/**
 * fk_remove_comments - function replaces the first instance of '#' with '\0'
 * @fk_buf: address of the string to modify
 *
 * Return: Always 0;
 */
void fk_remove_comments(char *fk_buf)
{
	int i;

	for (i = 0; fk_buf[i] != '\0'; i++)
		if (fk_buf[i] == '#' && (!i || fk_buf[i - 1] == ' '))
		{
			fk_buf[i] = '\0';
			break;
		}
}

