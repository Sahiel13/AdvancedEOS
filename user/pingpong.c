#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) 
{
           int parent_fd[2], child_fd[2],pid;
           char *Dataping="Ping",*Datapong="Pong";

           if (argc > 2) {
               printf("Invalid number of arguments\n");
               exit();
           }

           if (pipe(parent_fd) == -1) {
               printf("Pipe error \n");
               exit();
           }

           if (pipe(child_fd) == -1) {
               printf("Pipe error \n");
               exit();
           }

           pid = fork();
           if (pid == -1) {
               printf("Fork Error");
               exit();
           }

           if (pid == 0) {    /* Child reads from pipe */
	       read(parent_fd[0],Dataping,strlen(Dataping));/*Reading from parent pipe end*/
	       printf("%d: received ping %s \n",getpid(),Dataping);
               write(child_fd[1],Datapong,strlen(Datapong));/*Writing to child pipe end*/
               exit();

           } else {            /* Parent writes argv[1] to pipe */
               write(parent_fd[1],Dataping, strlen(Dataping));/*Writing to parent pipe end*/
	       read(child_fd[0],Datapong,strlen(Datapong));/*Reading from chile pipe end*/
	       printf("%d: received pong %s \n",getpid(),Datapong);
               exit();
           }
       }
