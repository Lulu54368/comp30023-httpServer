
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>
char* getFileName(char *buffer);
int getOKMessage(char *Mimetype, char *dest);

int getFailureMessage(char *dest);
int checkEscape(char * filename);
char *getFileType(char *filename);
char* getMimeType(char* type);
FILE* openFile(char*folder, char*buffer);