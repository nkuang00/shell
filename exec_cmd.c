#include "exec_cmd.h"

// int run_cmd(char ** args)
// Inputs:
//   char ** args
// Returns:
//   0 if cmd is exit, 1 otherwise
//
// If the cmd is exit, 0 is returned
// If the cmd is cd, chdir(args[1]) is called and 1 is returned
// Otherwise, run_forkcmd(args) is called and 1 is returned
int run_cmd(char ** args){
  if(strcmp(args[0], "exit") == 0){
    return 0;
  }

  if (strcmp(args[0], "cd") == 0){
    chdir(args[1]);
  }

  else{
      run_forkcmd(args);
  }
  return 1;
}

// int run_redir(char ** args_run, char ** args_in, char ** args_out)
// Inputs:
//   char ** args_run
//   char ** args_in
//   char ** args_out
// Returns:
//   1
//
// Reads args_in[0] as input, runs runs_forkcmd(args_run), and writes output to args_out[0]
int run_redir(char ** args_run, char ** args_in, char ** args_out){
  int in, out, stdin_temp, stdout_temp;
  in = open(args_in[0], O_RDONLY);
  out = open(args_out[0], O_WRONLY | O_CREAT, 0644);
  stdin_temp = dup(STDIN_FILENO);
  stdout_temp = dup(STDOUT_FILENO);
  dup2(in, STDIN_FILENO);
  dup2(out, STDOUT_FILENO);
  close(in);
  close(out);
  run_forkcmd(args_run);
  dup2(stdin_temp, STDIN_FILENO);
  dup2(stdout_temp, STDOUT_FILENO);
  close(stdin_temp);
  close(stdout_temp);

  return 1;
}

// int run_redirout(char ** args_in, char ** args_out)
// Inputs:
//   char ** args_in
//   char ** args_out
// Returns:
//   1
//
// Runs runs_forkcmd(args_in) and writes output to args_out[0]
int run_redirout(char ** args_in, char ** args_out){
  int out;
  out = open(args_out[0], O_WRONLY | O_CREAT, 0644);
  int stdout_temp = dup(STDOUT_FILENO);
  dup2(out, STDOUT_FILENO);
  run_forkcmd(args_in);
  close(out);
  dup2(stdout_temp, STDOUT_FILENO);
  close(stdout_temp);
  return 1;
}

// int run_redirin(char ** args_in, char ** args_out)
// Inputs:
//   char ** args_in
//   char ** args_out
// Returns:
//   1
//
// Reads args_in[0] as input and runs runs_forkcmd(args_out)
int run_redirin(char ** args_in, char ** args_out){
  int in;
  in = open(args_in[0], O_RDONLY);
  int stdin_temp = dup(STDIN_FILENO);
  dup2(in, STDIN_FILENO);
  close(in);
  run_forkcmd(args_out);
  dup2(stdin_temp, STDIN_FILENO);
  close(stdin_temp);
  return 1;
}

// int run_pipe(char * str_rd, char * str_wr)
// Inputs:
//   char * str_rd
//   char * str_wr
// Returns:
//   1
//
// Uses output from str_rd as input for str_wr
int run_pipe(char * str_rd, char * str_wr){
  FILE * fp_r;
  FILE * fp_w;
  fp_r = popen(str_rd, "r");
  fp_w = popen(str_wr, "w");
  char str[200];
  while (fgets(str, 200, fp_r)){
    fputs(str,fp_w);
  }
  pclose(fp_r);
  pclose(fp_w);
  return 1;
}

// void run_forkcmd(char ** args)
// Inputs:
//   char ** args
//
// Forks and executes cmd
void run_forkcmd(char ** args){
  int f = fork();
  int status;
  if (f == 0){
    execvp(args[0], args);
  }
  else{
    wait(&status);
  }
}
