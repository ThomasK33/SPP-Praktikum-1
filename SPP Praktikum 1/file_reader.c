#include "file_reader.h"

#include "list.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

LinkedList* read_text_file( const char* filename, int blockSize )
{
    LinkedList* l = LinkedList_create();
    
    FILE *fp;
   	char buff[blockSize];
    char sbuff[blockSize];
    int used = 0;
    
   	fp = fopen(filename, "r");
    
    if (fp == NULL)
        return l;
    
    int i = 0;
    
    while((i = fscanf(fp, "%s", buff)) > 0)
    {
        // printf("%i - %s - %lu - %d\n", i, buff, strlen(buff), used);
        
        if (used + strlen(buff) + 1 >= blockSize)
        {
//            printf("\n---\nBUFF full: %lu \n", strlen(buff));
            
            char* b = (char*)malloc(blockSize);
            
            strncpy(b, sbuff, blockSize);
            
            LinkedList_append(l, b);
            
            bzero(sbuff, sizeof(sbuff));
            used = 0;
            
        }
        
        strcat(sbuff, buff);
        strcat(sbuff, " ");
        
        used += strlen(buff) + 1;
    }
    
    if (used > 0)
    {
//        printf("\n---\nBUFF: %lu \n---\n", strlen(sbuff));
        
//        printf("Content: %s\n\n", sbuff);
        
        char* b = (char*)malloc(blockSize);
        
        strncpy(b, sbuff, blockSize);
        
        LinkedList_append(l, b);
        
        bzero(sbuff, sizeof(sbuff));
        used = 0;
    }
    
    fclose(fp);
    
    return l;
}
