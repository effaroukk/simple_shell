#include "fk.h"

/**
 * fk_input_buf - buffers chained commands
 * @info: parameter struct
 * @fk_buf: address of buffer
 * @fk_len: address of len var
 *
 * Return: bytes read
 */
ssize_t fk_input_buf(info_t *info, char **fk_buf, size_t *fk_len)
{
	ssize_t r = 0;
	size_t fk_len_p = 0;

	if (!*fk_len) /* if nothing left in the buffer, fill it */
	{
	/*bfree((void **)info->cmd_buf);*/
	free(*fk_buf);
	*fk_buf = NULL;
	signal(SIGINT, fk_sigintHandler);
	#if USE_GETLINE
	r = getline(fk_buf, &fk_len_p, stdin);
	#else
	r = fk_getline(info, fk_buf, &fk_len_p);
	#endif
	if (r > 0)
	{
		if ((*fk_buf)[r - 1] == '\n')
		{
			(*fk_buf)[r - 1] = '\0'; /* remove trailing newline */
			r--;
		}
		info->linecount_flag = 1;
		fk_remove_comments(*fk_buf);
		fk_build_history_list(info, *fk_buf, info->histcount++);
		/* if (fk_strchr(*fk_buf, ';')) is this a command chain? */
		{
		*fk_len = r;
		info->cmd_buf = *fk_buf;
		}
	}
	}
	return (r);
}

/**
 * fk_get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t fk_get_input(info_t *info)
{
	static char *fk_buf; /* the ';' command chain buffer */
	static size_t fk_i, fk_j, fk_len;
	ssize_t r = 0;
	char **fk_buf_p = &(info->arg), *p;

	putchar(BUF_FLUSH);
	r = fk_input_buf(info, &fk_buf, &fk_len);
	if (r == -1) /* EOF */
	return (-1);
	if (fk_len) /* we have commands left in the chain buffer */
	{
		fk_j = fk_i; /* init new iterator to current buf position */
		p = fk_buf + fk_i; /* get pointer for return */

		fk_check_chain(info, fk_buf, &fk_j, fk_i, fk_len);
		while (fk_j < fk_len) /* iterate to semicolon or end */
		{
			if (fk_is_chain(info, fk_buf, &fk_j))
				break;
			fk_j++;
		}

	fk_i = fk_j + 1; /* increment past nulled ';'' */
	if (fk_i >= fk_len) /* reached end of buffer? */
	{
		fk_i = fk_len = 0; /* reset position and length */
		info->cmd_buf_type = CMD_NORM;
	}

	*fk_buf_p = p; /* pass back pointer to current command position */
	return (fk_strchr(p)); /* return length of current command */
	}

	*fk_buf_p = fk_buf; /* else not a chain, pass back buffer from fk_getline() */
	return (r); /* return length of buffer from fk_getline() */
}

/**
 * fk_read_buf - reads a buffer
 * @info: parameter struct
 * @fk_buf: buffer
 * @fk_i: size
 *
 * Return: r
 */
ssize_t fk_read_buf(info_t *info, char *fk_buf, size_t *fk_i)
{
	ssize_t r = 0;

	if (*fk_i)
	return (0);
	r = read(info->readfd, fk_buf, WRITE_BUF_SIZE);
	if (r >= 0)
	*fk_i = r;
	return (r);
}

/**
 * fk_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int fk_getline(info_t *info, char **ptr, size_t *length)
{
	static char fk_buf[WRITE_BUF_SIZE];
	static size_t fk_i, fk_len;
	size_t fk_k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (fk_i == fk_len)
		fk_i = fk_len = 0;

	r = fk_read_buf(info, fk_buf, &fk_len);
	if (r == -1 || (r == 0 && fk_len == 0))
	return (-1);

	c = fk_strchr(fk_buf + fk_i, '\n');
	fk_k = c ? 1 + (unsigned int)(c - fk_buf) : fk_len;
	new_p = realloc(p, s, s ? s + fk_k : fk_k + 1);
	if (!new_p) /* MALLOC FAILURE! */
	return (p ? free(p), -1 : -1);

	if (s)
		fk_strncat(new_p, fk_buf + fk_i, fk_k - fk_i);
	else
		fk_strncpy(new_p, fk_buf + fk_i, fk_k - fk_i + 1);

	s += fk_k - fk_i;
	fk_i = fk_k;
	p = new_p;

	if (length)
		*length = s;
		*ptr = p;
	return (s);
}

/**
 * fk_sigintHandler - blocks ctrl-C
 * @fk_sig_num: the signal number
 *
 * Return: void
 */
void fk_sigintHandler(__attribute__((unused))int fk_sig_num)
{
	fk_eputs("\n");
	fk_eputs("$ ");
	fk_eputchar(BUF_FLUSH);
}

