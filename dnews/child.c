#include "child.h"

void dochild(int fd) {

  char* lastline;
  char puffer[128];

  connfd = fd;

  working = checkclient();

  strcpy(puffer, "200 dnews server ");
  strcat(puffer, "posting ok...\n");

  sendline((char*)&puffer);

  if( !(mysql_connect(&mysql, "localhost", "dnewsserver", "dnewsserver")) ) {
    printf("mysql: %s\n", mysql_error(&mysql));
  }

  if( mysql_select_db(&mysql, "dnews") ) {
    printf("mysql: %s\n", mysql_error(&mysql));
  }

  while(working) {
    lastline = readline();
    if(strlen(lastline)>0) {
      parseline(lastline);
    }
  }
  close(connfd);

  mysql_close(&mysql);
}

char* readline() {

  int count, ch;
  count = 0;
  while( (ch = read(connfd, &puffer[count], 1)) > 0) {
    if( (puffer[count] == '\n') || (puffer[count] == '\r') ) {
      puffer[count] = 0;
      break;
    }
    ++count;
  }
  if( ch < 0) {
    printf("read\n");
    exit(1);
  }

  return (char *)&puffer;
}

void parseline (char* lastline) {

  char *tok, *arg;
  char puffer[2048];

  printf("got: %s\n", lastline);

  // get command

  tok = (char*)strtok(lastline, " \t\r");
  makelower(tok);
  arg = (char*)strtok(NULL, "\r");

  printf("command: '%s'\n", tok);
  printf("arg: '%s'\n", arg);

  if(strcmp(tok, "quit")==0) {
    doquit();
  }
  else if(strcmp(tok, "list")==0) {
    dolist();
  }
  else {
    sendline("501 command not recognized...\n");
  }

}

void sendline(char* line) {
  write(connfd, line, strlen(line));
}

void makelower(char* string) {
  int i;
  for(i=0; string[i]; ++i) {
    string[i] = tolower(string[i]);
    if(string[i] == '\r') string[i] = 0;
    if(string[i] == '\n') string[i] = 0;
  }
}

int checkclient() {

  return 1;
}

void doquit() {
  sendline("205 Bye bye...\n");
  working = 0;
}

void dolist() {

  int i;
  char puffer[64];
  char ch[64];

  sendline("215 list of newsgroups follows...\n");

  if( mysql_query(&mysql, "SELECT g.id, g.name, MIN(h.id), MAX(h.id) FROM newsgroups g, newsheader h WHERE g.id=h.gid GROUP BY g.id") ) {
    printf("mysql: %s\n", mysql_error(&mysql));
  }

  if( !(res = mysql_store_result(&mysql)) ) {
    printf("mysql: %s\n", mysql_error(&mysql));
  }

  while( (row = mysql_fetch_row(res)) ) {

    printf("result: %s %s %s %s\n", row[0],row[1],row[2],row[3]);

    sprintf(&ch, "%s ", row[1]);
    strcpy(puffer, ch);

    sprintf(&ch, "%010d ", atoi(row[2]));
    strcat(puffer, ch);
    sprintf(&ch, "%010d ", atoi(row[3]));
    strcat(puffer, ch);
    strcat(puffer, "y\n");

    sendline(puffer);

    mysql_free_result(res);
  }

  sendline(".\n\r");
}


