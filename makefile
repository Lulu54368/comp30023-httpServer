CC=gcc
CFLAGS=-Wall
LDFLAGS=-lpthread


server:  server.o -lpthread utils.o multithreads.o 

server.o:  server.c 
	  gcc  -c server.c -Wall -g -lpthread -fno-stack-protector  
utils.o: utils.c utils.h
	gcc -c utils.c -Wall -g -fno-stack-protector  

multithreads.o: multithreads.c multithreads.h
	gcc -c multithreads.c -Wall -g -fno-stack-protector  
clean:
	rm -f *.o ./server

format:
	clang-format -i *.c *.h
