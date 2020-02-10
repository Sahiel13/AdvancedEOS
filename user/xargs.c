#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc < 2){
    fprintf(2, "Usage: xargs command\n");
    exit();
  }

  char* _argv[MAXARG];
  for (int i = 1; i < argc; i++) {
   _argv[i - 1] = argv[i];
  }

  char argument[300];
  int value = 1;

  while (value) {
    int cnt = 0, lst_arg = 0, argv_cnt = argc - 1;
    char ch = 0;

    while (1) {
      value = read(0, &ch, 1);

      if (value == 0) 
          exit();

      if (ch == ' ' || ch == '\n') {
        argument[cnt++] = 0;
        _argv[argv_cnt++] = &argument[lst_arg];
        lst_arg = cnt;

        if (ch == '\n')
           break;
      } 
	else 
	   argument[cnt++] = ch;
    }
    _argv[argv_cnt] = 0;

    if (fork() == 0) {
      exec(_argv[0], _argv);
    }
    else {
      wait();  
    }
  }

  exit();
}
