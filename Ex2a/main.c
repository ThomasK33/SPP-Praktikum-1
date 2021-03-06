//
//  main.c
//  Ex2a
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
    int i, size = LinkedList_getSize(list), j = 0;
//    double startTime = omp_get_wtime();
    
    #pragma omp parallel for private(i) reduction(+:j)
    for (i = 0; i < size; i++)
    {
        char* data = LinkedList_getDataAt(list, i);
        char buf[1024];
        Parser* p = Parser_create(data);
        
        while (Parser_getNextWord(p, buf, 1024) > 0)
        {
            if (!Dictionary_isIn(dict, buf))
                j += 1;
        }
        
        Parser_delete(p);
    }
    
//    double endTime = omp_get_wtime();
//    double totalTime = endTime - startTime;
    
    LinkedList_delete(list);
    Dictionary_delete(dict);
    
    printf("Amount of different words: %i\n", j);
//    printf("Total time: %f\n", totalTime);
    
    return 0;
}
