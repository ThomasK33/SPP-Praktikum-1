#include "file_reader.h"

#include "list.h"

#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>

#include <string.h>

void cleanString(char* line)
{
    int i;
    for(i = 0; i < strlen(line) && line[i] != '\0'; i++)
    {
        if (!isalpha(line[i]))
        {
            for (int j = i; j < strlen(line) && line[j] != 0; j++)
            {
                line[j] = line[j+1];
            }
            i -= 1;
        }
    }
    
    line[i] = '\0';
}

LinkedList* read_text_file( const char* filename, int blockSize )
{
    LinkedList* l = LinkedList_create();
    
    FILE *fp;
   	char* buff = (char*) malloc(blockSize * sizeof(char));
//    char sbuff[blockSize];
    char* sbuff = (char*) malloc(blockSize * sizeof(char));
    int used = 0;
    
   	fp = fopen(filename, "r");
    
    if (fp == NULL)
        return l;
    
    int i = 0;
    
    while((i = fscanf(fp, "%s", buff)) > 0)
    {
        cleanString(buff);
        if (strlen(buff) == 0)
            continue;
        
//        printf("%s\n", buff);
        
        if (used + strlen(buff) + 1 >= blockSize)
        {
            //            printf("\n---\nBUFF full: %lu \n", strlen(buff));
            
            char* b = (char*)malloc(blockSize);
            
            strncpy(b, sbuff, blockSize);
            
            LinkedList_append(l, b);
            
            bzero(sbuff, sizeof(sbuff));
            used = 0;
            
        }

        strcat(buff, " ");
        memmove(sbuff + used, buff, strlen(buff));
        
//        strcat(sbuff, buff);
//        strcat(sbuff, " ");
        
//        char dest[] = "oldstring          ";
//        const char src[]  = "newstring";
//        
//        printf("Before memmove dest = %s, src = %s\n", dest, src);
//        memmove(dest, src, 9);
//        printf("After memmove dest = %s, src = %s\n", dest, src);
        
        used += strlen(buff);
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
    
    free(sbuff);
    free(buff);
    
    return l;
}
