# shell
by Nancy Kuang

## Features
  + Parses multiple commands on one line by ';'
  + Forks and executes commands
  + Redirects using >, <, and < > (in that order)
  + Implements pipes (limited to one pipe per command)


## Attempted

## Bugs
  + Command line inputs are limited to 99 bytes
  + < breaks when file that is being read from does not exist

## Files and Function Headers:

### main.c
Handles while loop

```
int main()
```
Returns:\
&emsp; ```0``` upon exiting the shell

Initiates while loop that calls ```readcmdline()```\
If "exit" is called, then it breaks out of the while loop

### parse_args.c
Handles parsing command line arguments

```
int readcmdline()
```
Returns:\
&emsp; ```0``` if exit is called; ```1``` otherwise

Reads in up to 99 bytes from the command line\
Calls ```parse_cmds```

```
int parse_cmds(char * line)
```
Inputs:\
&emsp; ```char * line```\
Returns:\
&emsp; ```0``` if exit is called; ```1``` otherwise

Parses ```line``` by semicolons\
Calls ```parse_args``` on each command

```
int parse_args(char * line)
```
Inputs:\
&emsp; ```char * line```\
Returns:\
&emsp; ```0``` if exit is called; ```1``` otherwise

Calls and returns ```parse_pipe(line)``` if ```line``` contains a pipe\
Calls and returns ```parse_redir(line)``` if ```line``` contains both ```'<'``` and ```'>'```\
Calls and returns ```parse_redirin(line)``` if ```line``` contains ```'<'```\
Calls and returns ```parse_redirout(line)``` if ```line``` contains ```'>'```\
Otherwise, calls ```parse_args2(line)``` and ```run_cmd```


```
int parse_redir(char * line)
```
Inputs:\
&emsp; ```char * line```\
Returns:\
&emsp; ```1```

Calls ```parse_args2``` three times to parse run cmd, in cmd, and out cmd\
Calls and returns ```run_redir```, passing parsed run, in, and out cmds as inputs

```
int parse_redirin(char * line)
```
Inputs:\
&emsp; ```char * line```\
Returns:\
&emsp; ```1```

Calls ```parse_args2``` twice to parse left and right of ```'<'```\
Calls and returns ```run_redirin```, passing parsed cmds from above as inputs

```
int parse_redirout(char * line)
```
Inputs:\
&emsp; ```char * line```\
Returns:\
&emsp; ```1```

Calls ```parse_args2``` twice to parse left and right of ```'>'```\
Calls and returns ```run_redirout```, passing parsed cmds from above as inputs

```
int parse_pipe(char * line)
```
Inputs:\
&emsp; ```char * line```\
Returns:\
&emsp; ```1```

Calls and returns ```run_pipe```


```
char ** parse_args2(char * line)
```
Inputs:\
&emsp; ```char * line```\
Returns:\
&emsp; ```char ** tokens```, where ```tokens``` is an array of strings, with each string being an arg 

Parses ```line``` by space

```
char ** free_tokens(char ** tokens)
```
Inputs:\
&emsp; ```char ** tokens```\
Returns:\
&emsp; ```NULL```

Frees each string in ```tokens``` and sets pointers to ```NULL```


### exec_cmd.c
Executes commands

```
int run_cmd(char ** args)
```
Inputs:\
&emsp; ```char ** args```\
Returns:\
&emsp; ```0``` if cmd is exit, ```1``` otherwise

If the cmd is exit, ```0``` is returned\
If the cmd is cd, ```chdir(args[1])``` is called and ```1``` is returned\
Otherwise, ```run_forkcmd(args)``` is called and ```1``` is returned


```
int run_redir(char ** args_run, char ** args_in, char ** args_out)
```
Inputs:\
&emsp; ```char ** args_run```\
&emsp; ```char ** args_in```\
&emsp; ```char ** args_out```\
Returns:\
&emsp; ```1```

Reads ```args_in[0]``` as input, runs ```runs_forkcmd(args_run)```, and writes output to ```args_out[0]```

```
int run_redirin(char ** args_in, char ** args_out)
```
Inputs:\
&emsp; ```char ** args_in```\
&emsp; ```char ** args_out```\
Returns:\
&emsp; ```1```

Reads ```args_in[0]``` as input and runs ```runs_forkcmd(args_out)```

```
int run_redirout(char ** args_in, char ** args_out)
```
Inputs:\
&emsp; ```char ** args_in```\
&emsp; ```char ** args_out```\
Returns:\
&emsp; ```1```

Runs ```runs_forkcmd(args_in)``` and writes output to ```args_out[0]```

```
int run_pipe(char * str_rd, char * str_wr)
```
Inputs:\
&emsp; ```char * str_rd```\
&emsp; ```char * str_wr```\
Returns:\
&emsp; ```1```

Uses output from ```str_rd``` as input for ```str_wr```

```
void run_forkcmd(char ** args)
```
Inputs:\
&emsp; ```char ** args```

Forks and executes cmd
