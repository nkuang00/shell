#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse_args.h"
#include "exec_cmd.h"


int readcmdline(){
  //reads in line of cmd
  printf("$ ");
  fflush(stdout);
  char cmd_line[101];
  fgets(cmd_line, 100, stdin);
  cmd_line[strlen(cmd_line) - 1] = 0;
  return parse_cmds(cmd_line);
}

int parse_cmds(char * line){
  //char *** tokens = malloc(100);
  int i = 0;
  while (line != NULL){
    char * cmd = strsep(&line, ";");

    //deleting leading and trailing spaces
    int j;
    int len = strlen(cmd);
    if (cmd[len - 1] == ' '){
      cmd[len - 1] = 0;
    }

    len = strlen(cmd);
    if (i != 0){
      for (j = 0; j < len; j++){
        cmd[j] = cmd[j + 1];
      }
    }

    // if exit:
    if (parse_args(cmd) == 0){
      return 0;
    }
    i++;
  }
  return 1;
}


// RUN < IN > OUT
int parse_redir(char * line){
  char * in_start = strchr(line, '<') + 2;
  char * out_start = strchr(line, '>') + 2;
  *(in_start - 3) = 0;
  *(out_start - 3) = 0;
  char ** run_tokens = parse_args2(line);
  char ** in_tokens = parse_args2(in_start);
  char ** out_tokens = parse_args2(out_start);


  int ret = run_redir(run_tokens, in_tokens, out_tokens);
  run_tokens = free_tokens(run_tokens);
  in_tokens = free_tokens(in_tokens);
  out_tokens = free_tokens(out_tokens);

  return ret;
}

int parse_redirout(char * line){
  char * out_start = strchr(line,'>') + 2;
  *(out_start - 2) = 0;
  *(out_start - 3) = 0;
  char ** in_tokens = parse_args2(line);
  char ** out_tokens = parse_args2(out_start);

  int ret = run_redirout(in_tokens, out_tokens);
  in_tokens = free_tokens(in_tokens);
  out_tokens = free_tokens(out_tokens);

  return ret;
}

int parse_redirin(char * line){
  char * in_start = strchr(line,'<') + 2;
  *(in_start - 2) = 0;
  *(in_start - 3) = 0;
  char ** in_tokens = parse_args2(in_start);
  char ** out_tokens = parse_args2(line);

  int ret = run_redirin(in_tokens, out_tokens);
  in_tokens = free_tokens(in_tokens);
  out_tokens = free_tokens(out_tokens);

  return ret;
}

int parse_pipe(char * line){
  char * str_rd, * str_wr;
  int ret;
  str_rd = line;
  str_wr = strchr(line, '|') + 2;
  *(str_wr - 3) = 0;
  ret = run_pipe(str_rd, str_wr);
  return ret;
}


//parsing args in a cmd
int parse_args(char * line){
  if (strchr(line, '|') != NULL){
    return parse_pipe(line);
  }
  if (strchr(line, '>') != NULL && strchr(line, '<') != NULL){
    return parse_redir(line);
  }
  if (strchr(line, '>') != NULL){
    return parse_redirout(line);
  }
  if (strchr(line, '<') != NULL){
    return parse_redirin(line);
  }
  char ** tokens = parse_args2(line);
  // for(j = 0; j < i; j++){
  //   printf("token %d: %s\n", j, tokens[j]);
  // }
  int ret = run_cmd(tokens);
  tokens = free_tokens(tokens);
  return ret;
}

char ** free_tokens(char ** tokens){
  int j = 0;
  while (tokens[j] != NULL){
    tokens[j] = NULL;
    j++;
  }
  free(tokens);
  return NULL;
}

char ** parse_args2(char * line){
  char ** tokens = malloc(100);
  int i, j;
  i = 0;
  while (line != NULL){
    tokens[i] = strsep(&line, " ");
    i++;
  }
  return tokens;
}
