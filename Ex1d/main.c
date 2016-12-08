//
//  main.c
//  Ex1d
//
//  Created by Thomas Kosiewski on 07.12.16.
//  Copyright © 2016 Thomas Kosiewski. All rights reserved.
//

#include <stdio.h>

#include "file_reader.h"
#include "parser.h"
#include "dictionary.h"

int main(int argc, const char * argv[]) {
    
    if (argc < 2)
    {
        printf("Please pass the whole path of the file to be read as command line argument\n");
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
    Dictionary_delete(dict);
    
    return 0;
}
