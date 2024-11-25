#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
  pid_t firstborn, secondborn;
  printf("%d about to create 2 child processes. aaaand it's all over my screen\n", getpid());

  firstborn = fork();
  if(firstborn<0){
    perror("fork fail");
    exit(1);
  } else if (firstborn==0){
    //I AM A MINOR.
  } else {
    //SHE SAID SHE WAS TWELVE!!!!
      secondborn = fork();
      if(secondborn<0){
        perror("fork fail");
        exit(1);
      } else if (secondborn == 0){
        //child
      } else {
        //parent!!!
        int* status;
        WIFEXITED(*status);
      }

  }
}
