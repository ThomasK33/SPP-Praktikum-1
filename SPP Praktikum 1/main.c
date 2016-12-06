//
//  main.c
//  SPP Praktikum 1
//
//  Created by Thomas Kosiewski on 28.11.16.
//  Copyright © 2016 Thomas Kosiewski. All rights reserved.
//

#include <stdio.h>

#include "list.h"
#include "file_reader.h"
#include "parser.h"
#include "dictionary.h"

int main(int argc, const char * argv[]) {
	LinkedList* list = read_text_file("/Users/thomas/Uni/SPP Praktikum 1/smaller testing.txt", 16000);
    LinkedList* list2 = read_text_file("/Users/thomas/Uni/SPP Praktikum 1/smaller testing 2.txt", 16000);
    
    char* firstData = LinkedList_getData(LinkedList_getFirst(list));
    char buf[1024];
//    char* buf[] = {"WHALE", "WAND", "WOODFIRE", "WOOD", "WOLF", "TEST", "WALL", "WHAT", "WANNA", "WHALE"};
    Parser* p = Parser_create(firstData);
    
    Dictionary* dict = Dictionary_create();
    
//    for (int i = 0; i < sizeof(buf)/sizeof(char*); i++)
//    for (int i = 0; i < 13; i++)
    while (Parser_getNextWord(p, buf, 1024) > 0)
    {
//
        Dictionary_insert(dict, buf);
        
//        Dictionary_insert(dict, buf[i]);
    }
    
    char* secondData = LinkedList_getData(LinkedList_getFirst(list2));
    Parser* p2 = Parser_create(secondData);
    
    char buf2[1024];
    
    int j = 0;
    
    while (Parser_getNextWord(p2, buf2, 1024) > 0)
    {
        if (!Dictionary_isIn(dict, buf2))
            j += 1;
    }
    
    printf("Amount of different words: %i\n", j);
    
	return 0;
}
