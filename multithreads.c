#include "multithreads.h"
//This function to to assign task for each thread
void* thread_task(void *i){
    input_t* input = (input_t *) i;
    int n;
    int newsockfd = input->newsockfd;
	//record accumulated information read
    char last_buffer[2048];
   // strcpy(last_buffer ,input->last_buffer);
    char *folder = input->folder;
    char* buffer = malloc(2048 *sizeof(char));
		//read buffer
		while((n = read(newsockfd, buffer, 2048)) >0){
            buffer[n] = '\0';
            strcat(last_buffer, buffer);
       
			if(checkRequestFinished(buffer, n) == 0){
				// remove ctrl+D
                last_buffer[n-7] = '\0';
			
				
				
            }
            else{
                
                FILE* fp = openFile(folder, last_buffer);
              
                char *message = (char*)malloc(256 * sizeof(char));
                char *fileName = (char*)malloc(256 * sizeof(char));
                fileName = getFileName(last_buffer);
				printf("file name %s", fileName);
                // check whether the file is legal
		        if(fp == NULL || checkEscape(getFileName(buffer))){  
             
			        int n = getFailureMessage(message);
			        write(newsockfd, message, n);
			        close(newsockfd);

			    }
               
                else
		        {
			        int currWrite = 0;
			        char* text = malloc(1024 * sizeof(char));
			        char *type = malloc(256);
			        type = getFileType(fileName);
			        int ind = 0;
			        int currNum = 0;
			        int tot = 0;
					// send ok message
			        currWrite = getOKMessage(getMimeType(type), message);
			        write(newsockfd, message, currWrite);
					// send the content of the file
		            while((currNum = fread(text+ind,1,  1024, fp)) >0){
			            write(newsockfd, text+ind, currNum);
				        ind = currNum + ind;
				        tot += currNum;
				        text = realloc(text, tot+1024);
				
			        }
			        free(text);
                    fclose(fp);
			        
		        }
                free(message);
			    
			    close(newsockfd);

            }
		    
            
		    } // n is number of characters read
		    // Null-terminate string
            return 0;
        
       
}