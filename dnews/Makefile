
CC=gcc
CFLAGS=-I/usr/local/mysql/include/mysql -Wall
LDFLAGS= -L/usr/local/mysql/lib/mysql -lmysqlclient

dnews : main.o child.o help.o dnewsconfig.o
	${CC} -o dnews main.o child.o help.o dnewsconfig.o ${LDFLAGS}

main.o : main.c
	${CC} -c main.c ${CFLAGS}

child.o : child.c
	${CC} -c child.c ${CFLAGS}

help.o : help.c
	${CC} -c help.c ${CFLAGS}

dnewsconfig.o : dnewsconfig.c
	${CC} -c dnewsconfig.c ${CFLAGS}

clean : 
	rm *.o

