#ifndef HELP_H
#define HELP_H

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

void sigchld(int);

int sockfd;
struct sockaddr_in address;

void openport(int);

void ng2dir(char *);



#endif

