//
//  main.c
//  Ex2c
//
//  Created by Thomas Kosiewski on 07.12.16.
//  Copyright © 2016 Thomas Kosiewski. All rights reserved.
//

#include <stdio.h>

// #include <libiomp/omp.h>
#include <omp.h>

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
    
    LinkedListNode* node = LinkedList_getFirst(list);
    
    do
    {
        char* data = LinkedList_getData(node);
        char buf[1024];
        Parser* p = Parser_create(data);
        
        while (Parser_getNextWord(p, buf, 1024) > 0)
        {
            Dictionary_insert(dict, buf);
        }
        
        Parser_delete(p);
    }
    while ((node = LinkedList_getNext(node)) != NULL);
    LinkedList_delete(list);
    
    list = read_text_file(*(argv + 2), 16000);
    int j = 0;
    double startTime = omp_get_wtime();
    
    #pragma omp parallel private(node)
    #pragma omp single nowait
    for (node = LinkedList_getFirst(list); node; node = LinkedList_getNext(node)) {
        #pragma omp task shared(j)
        {
            char* data = LinkedList_getData(node);
            char buf[1024];
            Parser* p = Parser_create(data);
            
            while (Parser_getNextWord(p, buf, 1024) > 0)
            {
                if (!Dictionary_isIn(dict, buf))
                    #pragma omp atomic
                    j += 1;
            }
            
            Parser_delete(p);
            
//            printf("%i\n", omp_get_thread_num());
        }
    }
    double endTime = omp_get_wtime();
    double totalTime = endTime - startTime;
    
    LinkedList_delete(list);
    Dictionary_delete(dict);
    
        printf("Amount of different words: %i - Total time: %f\n", j, totalTime);
    //    printf("Total time: %f\n", totalTime);
//    printf("%i - %f\n", j, totalTime);
    
    /* TIMES: Amount of different words - Total time
     -  1 Thread:   41034 - 0.380956
     -  2 Threads:  41034 - 0.191767
     -  4 Threads:  41034 - 0.099774
     -  8 Threads:  41034 - 0.091707
     -  16 Threads: 41034 - 0.102149
     */
    
    return 0;
}
