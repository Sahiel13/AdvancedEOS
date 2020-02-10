#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  
  int pipe_fd[2];
  int counter = 0, k, num[35] ;
  int pid;
	
    if (argc > 2) {
               printf("Invalid number of arguments\n");
               exit();
           }

  for (k = 2; k <= 35; k++) {
    num[counter++] = k;
  }

  while (counter > 0) {
   
     if (pipe(pipe_fd) == -1) {
               printf("Pipe error \n");
               exit();
        }

     pid = fork();
     if (pid == -1) {
               printf("Fork Error");
               exit();
        }
 	

    if (pid != 0) {  /* Parent reads from the pipe */

      close(pipe_fd[0]);/* closing the unused read end of the pipe*/
      for (k = 0; k < counter; k++) {
        write(pipe_fd[1], &num[k], sizeof(num[0])); /* writing to the pipe*/
      }
      close(pipe_fd[1]);/* closing the unused write end of the pipe*/
      wait();/* waiting for the child to change state */
      break;


    } else {

      int prime_number,first_prime = 0;

      close(pipe_fd[1]);/* closing the unused write end of the pipe*/
      counter = -1;
      while (read(pipe_fd[0], &prime_number, sizeof(prime_number)) != 0) { /* reading from the pipe until empty*/
        if (counter == -1) {
          first_prime = prime_number;/* stores the first number of every new array set */
          counter = 0;
        } else {
          if (prime_number % first_prime != 0) /* dropping of all the non prime numbers */
          num[counter++] = prime_number;
        }
      }
      printf("Prime Number %d\n", first_prime);
      close(pipe_fd[0]);/* closing the unused read end of the pipe*/

    }
  }
  exit();
}
