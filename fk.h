#ifndef _FK_H
#define _FK_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH '\0'
#define CONVERT_UNSIGNED 1
#define CONVERT_LOWERCASE 1


extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

struct fk_info
{
	int fk_readfd;
};

typedef struct
{
	int readfd;
	char *cmd_buf;
	char *fk_fname;
	int fk_line_count;
	char **fk_argv;
	int linecount_flag;
	int histcount;
	char *arg;
} info_t;
int fk_is_delim(char c, char *delim);
int fk_is_alpha(int c);
int fk_atoi(char *s);
void fk_eputs(char *fk_str);
int fk_eputchar(char fk_c);
int fk_putfd(char fk_c, int fk_fd);
int fk_putsfd(char *fk_str, int fk_fd);
char *fk_strncpy(char *fk_dest, char *fk_src, int fk_n);
char *fk_strncat(char *fk_dest, char *fk_src, int fk_n);
char *fk_strchr(char *fk_s, char fk_c);
int fk_myexit(siginfo_t *fk_info);
int fk_mycd(siginfo_t *fk_info);
int fk_myhelp(siginfo_t *fk_info);
int fk_main(int fk_ac, char **fk_av);
int fk_myhistory(siginfo_t *fk_info);
int fk_unset_alias(siginfo_t *fk_info, char *fk_str);
int fk_set_alias(siginfo_t *fk_info, char *fk_str);
int fk_print_alias(list_t *fk_node);
int fk_myalias(siginfo_t *fk_info);
int fk_myenv(siginfo_t *fk_info);
char *fk_getenv(siginfo_t *fk_info, const char *fk_name);
int fk_mysetenv(siginfo_t *fk_info);
int fk_myunsetenv(siginfo_t *fk_info);
int fk_populate_env_list(siginfo_t *fk_info);
int fk_erratoi(char *fk_s);
void fk_print_error(info_t *fk_info, char *fk_estr);
int fk_print_d(int fk_input, int fk_fd);
char *fk_convert_number(long int fk_num, int fk_base, int fk_flags);
void fk_remove_comments(char *fk_buf);
void fk_eputs(char *fk_str);
int fk_eputchar(char fk_c);
int fk_putfd(char fk_c, int fk_fd);
int fk_putsfd(char *fk_str, int fk_fd);
int fk_interactive(struct fk_info *fk_info);
ssize_t fk_input_buf(info_t *info, char **fk_buf, size_t *fk_len);
ssize_t fk_get_input(info_t *info);
ssize_t fk_read_buf(info_t *info, char *fk_buf, size_t *fk_i);
int fk_getline(info_t *info, char **ptr, size_t *length);
void fk_sigintHandler(__attribute__((unused)) int fk_sig_num);
void fk_build_history_list(info_t *info,
		const char *command, int histcount);
void fk_check_chain(info_t *info, char *fk_buf,
		size_t *fk_j, size_t fk_i, size_t fk_len);


























#endif
