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










#endif
