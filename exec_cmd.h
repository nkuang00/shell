#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int run_cmd(char ** args);
void run_forkcmd(char ** args);
int run_redir(char ** args_run, char ** args_in, char ** args_out);
int run_redirin(char ** args_in, char ** args_out);
int run_redirout(char ** args_in, char ** args_out);
int run_pipe(char * str_rd, char * str_wr, char ** arr_wr);
