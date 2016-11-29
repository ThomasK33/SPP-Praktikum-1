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

int main(int argc, const char * argv[]) {
	LinkedList* list = read_text_file("/Users/thomas/Uni/SPP Praktikum 1/smaller testing.txt", 16000);
    
    char* firstData = LinkedList_getData(LinkedList_getFirst(list));
    
    char buf[1024];
    
    Parser* p = Parser_create(firstData);
    
    for (int i = 0; i < 10; i++)
    {
        Parser_getNextWord(p, buf, 1024);
        printf("%s\n", buf);
    }
    
	return 0;
}
