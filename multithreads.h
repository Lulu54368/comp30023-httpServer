#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>
#include "utils.h"


struct input{
    int newsockfd;
    char* folder;
} ;
typedef struct input input_t;

void* thread_task(void *i);
int checkRequestFinished(char* request, int n);