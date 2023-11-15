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

int fk_interactive(fk_info_t *fk_info);
int fk_is_delim(char c, char *delim);
int fk_is_alpha(int c);
int fk_atoi(char *s);
































#endif
