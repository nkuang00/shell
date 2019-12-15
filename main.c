#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse_args.h"
#include "exec_cmd.h"


int main(){
  while(1){
    if (! readcmdline()){
      break;
    }
  }
  return 0;
}
