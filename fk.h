#ifndef FK_H
#define FK_H

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
#define MAX_SIZE 340

void fkPutPrompt(void);
int fkExecCmd(const char *command);
void fk_diplay_prompt(void);
char **fk_array_strtok(char *str);
void fk_execute(char **fk_commands,
		char **fk_env, char **fk_argv, int fk_count);
void null_command(FILE *stream, int fk_count);
void _path(char **fk_commands, char **fk_env);
char **fk_store_e_variables(char *fk_fir_com);
int _fk_puterror(char c);
void fkPutPrompt(void);
void _strncpcommand(char *arg1, char *arg2,
		char *arg3, int arg4, int arg5);
void free_all_dp(char **fk_directories);
size_t _strlen_const(const char *str);

#endif
