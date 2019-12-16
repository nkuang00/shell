#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse_args.h"
#include "exec_cmd.h"

// int readcmdline()
// Returns:
//   0 if exit is called; 1 otherwise
//
// Reads in up to 99 bytes from the command line
// Calls parse_cmds
int readcmdline(){
  char d[200];
  getcwd(d, 200);
  printf("%s$ ", d);
  fflush(stdout);
  char cmd_line[101];
  fgets(cmd_line, 100, stdin);
  cmd_line[strlen(cmd_line) - 1] = 0;
  return parse_cmds(cmd_line);
}

// int parse_cmds(char * line)
// Inputs:
//   char * line
// Returns:
//   0 if exit is called; 1 otherwise
//
// Parses line by semicolons
// Calls parse_args on each command
int parse_cmds(char * line){
  int i = 0;
  while (line != NULL){
    char * cmd = strsep(&line, ";");

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

    if (parse_args(cmd) == 0){
      return 0;
    }
    i++;
  }
  return 1;
}

// int parse_redir(char * line)
// Inputs:
//   char * line
// Returns:
//   1
//
// Calls parse_args2 three times to parse run cmd, in cmd, and out cmd
// Calls and returns run_redir, passing parsed run, in, and out cmds as inputs
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

// int parse_redirout(char * line)
// Inputs:
//   char * line
// Returns:
//   1
//
// Calls parse_args2 twice to parse left and right of '>'
// Calls and returns run_redirout, passing parsed cmds from above as inputs
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


// int parse_redirin(char * line)
// Inputs:
//   char * line
// Returns:
//   1
//
// Calls parse_args2 twice to parse left and right of '<'
// Calls and returns run_redirin, passing parsed cmds from above as inputs
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

// int parse_pipe(char * line)
// Inputs:
//   char * line
// Returns:
//   1
//
// Calls and returns run_pipe
int parse_pipe(char * line){
  char * str_rd, * str_wr;
  int ret;
  str_rd = line;
  str_wr = strchr(line, '|') + 2;
  *(str_wr - 3) = 0;
  ret = run_pipe(str_rd, str_wr);
  return ret;
}

// int parse_args(char * line)
// Inputs:
//   char * line
// Returns:
//   0 if exit is called; 1 otherwise
//
// Calls and returns parse_pipe(line) if line contains a pipe
// Calls and returns parse_redir(line) if line contains both '<' and '>'
// Calls and returns parse_redirin(line) if line contains '<'
// Calls and returns parse_redirout(line) if line contains '>'
// Otherwise, calls parse_args2(line) and run_cmd
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
  int ret = run_cmd(tokens);
  tokens = free_tokens(tokens);
  return ret;
}

// char ** free_tokens(char ** tokens)
// Inputs:
//   char ** tokens
// Returns:
//   NULL
//
// Frees each string in tokens and sets pointers to NULL
char ** free_tokens(char ** tokens){
  int j = 0;
  while (tokens[j] != NULL){
    tokens[j] = NULL;
    j++;
  }
  free(tokens);
  return NULL;
}

// char ** parse_args2(char * line)
// Inputs:
//   char * line
// Returns:
//   char ** tokens, where tokens is an array of strings, with each string being an arg
//
// Parses line by space
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
