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

int fk_interactive(siginfo_t *fk_info);
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
ssize_t fk_input_buf(ino_t *info, char **fk_buf, size_t *fk_len);
ssize_t fk_get_input(ino_t *info);
ssize_t fk_read_buf(ino_t *info, char *fk_buf, size_t *fk_i);
int fk_getline(ino_t *info, char **ptr, size_t *length);
void fk_sigintHandler(__attribute__((unused))int fk_sig_num);
int fk_myhistory(siginfo_t *fk_info);
int fk_unset_alias(siginfo_t *fk_info, char *fk_str);
int fk_set_alias(siginfo_t *fk_info, char *fk_str);
int fk_print_alias(list_t *fk_node);
int fk_myalias(siginfo_t *fk_info);
int fk_myenv(siginfo_t *fk_info)
char *fk_getenv(siginfo_t *fk_info, const char *fk_name);
int fk_mysetenv(siginfo_t *fk_info);
int fk_myunsetenv(siginfo_t *fk_info);
int fk_populate_env_list(siginfo_t *fk_info);
int fk_erratoi(char *fk_s);
void fk_print_error(siginfo_t *fk_info, char *fk_estr);
int fk_print_d(int fk_input, int fk_fd);
char *fk_convert_number(long int fk_num, int fk_base, int fk_flags);
void fk_remove_comments(char *fk_buf);































#endif
