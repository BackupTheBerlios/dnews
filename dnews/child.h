#ifndef CHILD_H
#define CHILD_H

#include <string.h>
#include <stdio.h>
#include <mysql.h>

#include "dnewsconfig.h"

// #include "rfc977.h"

MYSQL mysql;
MYSQL_RES *res;
MYSQL_ROW row;
MYSQL_RES *res2;
MYSQL_ROW row2;

int connfd, working;

unsigned int articenumber;
char groupname[256];
unsigned int groupnumber;

void dochild(int);

char puffer[513];
char* readline();
void parseline(char*);

void sendline(char*);

void makelower(char*);


void doquit();
void dolist();

#endif

