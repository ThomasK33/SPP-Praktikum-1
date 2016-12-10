//
//  main.c
//  Ex1e
//
//  Created by Thomas Kosiewski on 07.12.16.
//  Copyright © 2016 Thomas Kosiewski. All rights reserved.
//

#include <stdio.h>

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
    
    int j = 0;
    
    do
    {
        char* data = LinkedList_getData(node);
        char buf[1024];
        Parser* p = Parser_create(data);
        
        while (Parser_getNextWord(p, buf, 1024) > 0)
        {
            Dictionary_insert(dict, buf);
            
            j += 1;
        }
        
        Parser_delete(p);
    }
    while ((node = LinkedList_getNext(node)) != NULL);
    LinkedList_delete(list);
    
    printf("Inserted: %i words\n", j);
    
    int i = 0;
    list = read_text_file(*(argv + 2), 16000);
    node = LinkedList_getFirst(list);
    
    do
    {
        char* data = LinkedList_getData(node);
        char buf[1024];
        Parser* p = Parser_create(data);
        
        while (Parser_getNextWord(p, buf, 1024) > 0)
        {
            if (!Dictionary_isIn(dict, buf))
            {
                i += 1;
                
//                printf("%s\n", buf);
            }
        }
        
        Parser_delete(p);
    }
    while ((node = LinkedList_getNext(node)) != NULL);
    LinkedList_delete(list);
    
    printf("Amount of different words: %i\n", i);
    
    Dictionary_delete(dict);
    
    return 0;
}
