#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse_args.h"
#include "exec_cmd.h"


// int main()
// Returns:
//   0 upon exiting the shell
// Initiates while loop that calls readcmdline()
// If "exit" is called, then it breaks out of the while loop
int main(){
  printf("welcome to my shell!\n");
  printf("to start, enter a command with args separated by a single space\n");
  printf("when entering multiple cmds in the same line, leave a ';' between each command\n");
  printf("there should be a space on either side of the ';'\n");
  printf("to exit, enter \"exit\"\n");
  printf("******************************************************************************\n");

  while(1){
    if (! readcmdline()){
      break;
    }
  }
  return 0;
}
