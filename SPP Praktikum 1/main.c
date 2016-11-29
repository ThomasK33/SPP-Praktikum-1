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
	LinkedList* list = read_text_file("/export/files/disc04/users1/tk83vydi/SPP-Praktikum-1/smaller testing.txt", 16000);

	if (list == NULL)
		printf("List is NULL\n");

	LinkedListNode* n = LinkedList_getFirst(list);

	if (n == NULL)
		printf("Node is NULL\n");

	if (LinkedList_getData(n) == NULL)
		printf("Get data is NULL\n");

	printf("Data: %s\n", LinkedList_getData(n));
	return 0;
}
