#include "help.h"

void sigchld(int sig) {
  int status;
  wait(&status);
}

void openport(int portn) {
  int i;

  if( (sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    printf("socket\n");
    exit(1);
  }
  i = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
  address.sin_family = AF_INET;
  address.sin_port = htons(portn);
  memset(&address.sin_addr, 0, sizeof(address.sin_addr));

  if(bind(sockfd, (struct sockaddr*) &address, sizeof(address))) {
    printf("bind\n");
    exit(1);
  }

  if(listen(sockfd, 5)) {
    printf("listen\n");
    exit(1);
  }

}

void ng2dir(char *ng) {
	while(*ng != NULL) {
		if(*ng == '.') *ng = '/';
		++ng;
	}
}


