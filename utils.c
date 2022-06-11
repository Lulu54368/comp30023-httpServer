# include "utils.h"
// extract the file name
char* getFileName(char *buffer){
    int len = 0;
    int i = 4;
    while(buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\0'){
        i++;
        len++;
    }
    

    char* fileName = (char *)malloc(256 * sizeof(char));
    strncpy(fileName, buffer+4, len);
    fileName[len] = '\0';
  
    return fileName;

}
// check whether it's escape path
int checkEscape(char * filename){
    return (filename[1] == '.' && filename[2] == '.');
}
// get the ok message
int getOKMessage(char* Mimetype, char * dest){
    char * template = malloc(256 * sizeof(char));
    template = 
     "HTTP/1.0 200 OK\r\n"
     "Content-type: %s\r\n"
     "charset=utf-8\r\n\r\n";
     
    char *message = malloc(256);
    sprintf(message, template, Mimetype);
    strcpy(dest, message);
    return (sizeof(char) * strlen(dest));
}
// Get the failure message
int getFailureMessage(char * dest){
    char * template = malloc(sizeof(char) * 265);
    template = 
    "HTTP/1.0 404 Not Found\r\n"
    "Content-type: text/html\r\n\r\n";
    strcpy(dest, template);
    

    return (sizeof(char) * strlen(dest));
}
// extract the file type
char *getFileType(char *filename){
    
    int i = 0;
    //a.. case
    int start = strlen(filename)-1;
    while( filename[i] != '\0'){
        if(filename[i] == '.')
            start = i+1;
        i++;
    }
 
    int len = strlen(filename)-start;
  
    char *type = malloc(sizeof(char) * len);
    strncpy(type, filename+start, len);
   
    return type;
}

// get the mime type
char* getMimeType(char* type){
    if(strcmp(type, "html") == 0)
        return "text/html";
    else if(strcmp(type, "jpg") == 0){
        return "image/jpeg";
    }
    else if(strcmp(type, "css") == 0){
        return "text/css";
    }
    else{
        return "application/octet-stream";
    }
}
// check whether the message is complete
int checkRequestFinished(char* request, int n){
    if((request[n-3] == '\n')&&(request[n-4] == '\r')&&
    request[n-1] == '\n' && request[n-2] == '\r'){
        printf("valid");
        return 1;
    }
    else{
        printf("not valid\n");
        return 0;
    }
}
// open the file
FILE* openFile(char*folder, char*buffer){
    FILE* fp;
	fp = malloc(sizeof(FILE));
    char fileName[256];
    strcpy(fileName, getFileName(buffer));
    
	char filePath[256] = "..";
	strcat(filePath, folder);
	strcat(filePath, fileName);
    
	fp = fopen(filePath, "r");
    return fp;
}