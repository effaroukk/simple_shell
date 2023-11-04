#ifndef _fk_h
#define _fk_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

void fkPutPrompt(void);
int fkExecCmd(const char *command);
void fk_diplay_prompt(void);
char **fk_array_strtok(char *str);
void fk_execute(char **fk_commands, char *fk_buffer,
		char **fk_env, char **fk_argv, int fk_count);









#endif
