#ifndef MAIN_H
#define MAIN_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#include "help.h"
#include "dnewsconfig.h"
#include "child.h"

#include "rfc977.h"

int connfd;
size_t addressl = sizeof(struct sockaddr_in);




#endif

