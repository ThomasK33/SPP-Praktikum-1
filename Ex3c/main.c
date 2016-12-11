//
//  main.c
//  Ex3a
//
//  Created by Thomas Kosiewski on 07.12.16.
//  Copyright © 2016 Thomas Kosiewski. All rights reserved.
//

#include <stdio.h>
#include <libiomp/omp.h>
// #include <omp.h>

#include "file_reader.h"
#include "parser.h"
#include "dictionary.h"

Dictionary* dict_merge(Dictionary** dicts, int size)
{
    if (size < 2)
    {
        return *dicts;
    }
    else if (size == 2)
    {
        Dictionary_merge(dicts[0], dicts[1]);
        return dicts[0];
    }
    else
    {
        Dictionary *dict1, *dict2;
        
        #pragma omp task shared(dict1)
        dict1 = dict_merge(dicts, size/2);
        #pragma omp task shared(dict2)
        dict2 = dict_merge(dicts + size/2, size - (size/2));
        #pragma omp taskwait
        Dictionary_merge(dict1, dict2);
        
        return dict1;
    }
}

int main(int argc, const char * argv[]) {
    
    if (argc < 3)
    {
        printf("Please pass both absolute file paths as command line argument\n");
        return 0;
    }
    
    LinkedList* list = read_text_file(*(argv + 1), 16000);
    
    int i, size = LinkedList_getSize(list), j = 0;
    double startTime = omp_get_wtime();
    Dictionary* d[size];
    
    #pragma omp parallel for private(i) reduction(+:j)
    for (i = 0; i < size; i++)
    {
        char* data = LinkedList_getDataAt(list, i);
        char buf[1024];
        Parser* p = Parser_create(data);
        Dictionary* pDict = Dictionary_create();
        
        while (Parser_getNextWord(p, buf, 1024) > 0)
        {
            Dictionary_insert(pDict, buf);
            
            j += 1;
        }
        
        d[i] = pDict;
        
        Parser_delete(p);
    }
    
    Dictionary* dict;
    
    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            dict = dict_merge(d, size);
        }
    }
    double endTime = omp_get_wtime();
    double totalTime = endTime - startTime;
    
    LinkedList_delete(list);
    printf("%i - %f\n", j, totalTime);
    
    /* TIMES: Total words inserted - Total time
     -  1 Thread:   792972 - 0.708331
     -  2 Threads:  792972 - 0.371586
     -  4 Threads:  792972 - 0.209174
     -  8 Threads:  792972 - 0.192068
     -  16 Threads: 792972 - 0.226489
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
