#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int err(){
  printf("errno %d\n", errno);
  strerror(errno);
  printf("%s\n", strerror(errno));
  exit(1);
}

int randint(){
  int rand_file = open("/dev/urandom", O_RDONLY, 0);
  if (rand_file == -1) {
    printf("error time\n");
    err();
  }

  int buff;
  int bytes = read(rand_file, &buff, sizeof(buff));
  if (bytes == -1) {
    printf("error time2\n");
    err();
  }

  close(rand_file);

  return abs(buff%5)+1;
}

int minor(int pid){
  int rand = randint();
  printf("%d %dsec\n", pid, rand);
  sleep(rand);
  printf("%d finished after %d seconds\n", pid, rand);
  return rand;
}

int main(){
  pid_t firstborn, secondborn;
  printf("%d about to create 2 child processes\n", getpid());

  firstborn = fork();
  if(firstborn<0){
    perror("fork fail");
    exit(1);
  } else if (firstborn==0){
    return minor(getpid());
  } else {
      secondborn = fork();
      if(secondborn<0){
        perror("fork fail");
        exit(1);
      } else if (secondborn == 0){
        return minor(getpid());
      } else {
        int status;
        pid_t dead = wait(&status);
        if (WIFEXITED(status)){
          printf("main, %d, is done. rip %d who lived for %d seconds.\n", getpid(), dead, WEXITSTATUS(status));
        }
        return 0;
      }
  }
}
