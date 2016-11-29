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

int main(int argc, const char * argv[]) {
	LinkedList* list = read_text_file("/Users/thomas/Uni/SPP Praktikum 1/82-0.txt", 16000);
	return 0;
}
