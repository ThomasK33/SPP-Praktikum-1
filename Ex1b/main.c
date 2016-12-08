//
//  main.c
//  Ex1b
//
//  Created by Thomas Kosiewski on 07.12.16.
//  Copyright © 2016 Thomas Kosiewski. All rights reserved.
//

#include <stdio.h>

#include "file_reader.h"

int main(int argc, const char * argv[])
{
    if (argc < 2)
    {
        printf("Please pass the whole path of the file to be read as command line argument\n");
    }
    else
    {
        LinkedList* list = read_text_file(*(argv + 1), 16000);
    }
    
    return 0;
}
