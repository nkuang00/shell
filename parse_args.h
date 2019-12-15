#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "exec_cmd.h"


int readcmdline();
int parse_cmds(char * line);
int parse_args(char * line);
int parse_redir(char * line);
int parse_redirout(char * line);
int parse_redirin(char * line);
char ** free_tokens(char ** tokens);
char ** parse_args2(char * line);
int parse_pipe(char * line);
