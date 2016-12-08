//
//  main.c
//  Ex3a
//
//  Created by Thomas Kosiewski on 07.12.16.
//  Copyright © 2016 Thomas Kosiewski. All rights reserved.
//

#include <stdio.h>
#include <libiomp/omp.h>

#include "file_reader.h"
#include "parser.h"
#include "dictionary.h"

int main(int argc, const char * argv[]) {
    
    if (argc < 3)
    {
        printf("Please pass both absolute file paths as command line argument\n");
        return 0;
    }
    
    Dictionary* dict = Dictionary_create();
    LinkedList* list = read_text_file(*(argv + 1), 16000);
    
    int i, size = LinkedList_getSize(list);
    
    double startTime = omp_get_wtime();
    
    #pragma omp parallel for private(i)
    for (i = 0; i < size; i++)
    {
        char* data = LinkedList_getDataAt(list, i);
        char buf[1024];
        Parser* p = Parser_create(data);
        
        int j = 0;
        
        while (Parser_getNextWord(p, buf, 1024) > 0)
        {
            #pragma omp critical
            Dictionary_insert(dict, buf);
            
            j += 1;
        }
        
        Parser_delete(p);
        
        printf("%i - %i\n", omp_get_thread_num(), j);
    }
    double endTime = omp_get_wtime();
    double totalTime = endTime - startTime;
//    double totalTime = 0;
    
    LinkedList_delete(list);
    int j = 0;
    printf("%i - %f\n", j, totalTime);
    
    /* TIMES: Total words inserted - Total time
     -  1 Thread:   100609 - 1.041746
     -  2 Threads:  100609 - 0.569139
     -  4 Threads:  100609 - 0.511422
     -  8 Threads:  100609 - 0.662391
     -  16 Threads: 100609 - 1.323677
     */
    
    i = 0;
    list = read_text_file(*(argv + 2), 16000);
    LinkedListNode* node = LinkedList_getFirst(list);
    
    do
    {
        char* data = LinkedList_getData(node);
        char buf[1024];
        Parser* p = Parser_create(data);
        
        while (Parser_getNextWord(p, buf, 1024) > 0)
        {
            if (!Dictionary_isIn(dict, buf))
                i += 1;
        }
        
        Parser_delete(p);
    }
    while ((node = LinkedList_getNext(node)) != NULL);
    LinkedList_delete(list);
    
    printf("Amount of different words: %i\n", i);
    
    Dictionary_delete(dict);
    
    return 0;
}
