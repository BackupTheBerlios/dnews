#include "main.h"


int main(int argc, char* argv[]) {
  
  int connfd;
  pid_t pid;

  getconfig();

  signal(SIGCHLD, &sigchld);

  openport(portnumber);

  while( (connfd = accept(sockfd, (struct sockaddr *) &address, &addressl)) >= 0 ) {
    pid = fork();

    if(pid == 0) {
      close(sockfd);
      dochild(connfd);
    }
    else if(pid < 0) {
      printf("fork\n");
      exit(1);
    }
    else {
      close(connfd);
    }
  }

  exit(0);
}