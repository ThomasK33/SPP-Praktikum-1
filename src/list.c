//
//  list.c
//  SPP Praktikum 1
//
//  Created by Thomas Kosiewski on 28.11.16.
//  Copyright © 2016 Thomas Kosiewski. All rights reserved.
//

#include "list.h"

#include <stdlib.h>

struct LinkedList {
    LinkedListNode* first;
    LinkedListNode* last;
};

struct LinkedListNode {
    LinkedListNode* previous;
    LinkedListNode* next;
    char* data;
};

LinkedList* LinkedList_create()
{
    LinkedList* ll = (LinkedList*) malloc(sizeof(LinkedList));
    
    ll->first = NULL;
    ll->last = NULL;
    
    return ll;
}

void LinkedList_append( LinkedList* list, char* data )
{
    LinkedListNode* lln = (LinkedListNode*) malloc(sizeof(LinkedListNode));
    
    lln->data = data;
    lln->previous = list->last;
    lln->next = NULL;
    
    if (list->first == NULL)
    {
        list->first = lln;
        lln->previous = NULL;
        list->last = lln;
    }
    else
    {
        list->last->next = lln;
        list->last = lln;
    }
}

void LinkedList_delete( LinkedList* list )
{
    if (list == NULL)
        return;
    
    LinkedListNode* n = list->last;
    while (n != NULL && n->previous != NULL)
    {
        LinkedListNode* tmp = n->previous;
        
        free(n->data);
        
        free(n);
        
        n = tmp;
    }
    
    if (n != NULL)
    {
        free(n->data);
        free(n);
    }
    
    free(list);
}

LinkedListNode* LinkedList_getFirst( LinkedList* list )
{
//    return list->first != NULL ? list->first : NULL;
    if (list != NULL && list->first != NULL) return list->first;
    else return NULL;
}

LinkedListNode* LinkedList_getLast( LinkedList* list )
{
//    return list->last != NULL ? list->last : NULL;
    if (list != NULL && list->last != NULL) return list->last;
    else return NULL;
}

LinkedListNode* LinkedList_getNext( LinkedListNode* node )
{
//    return node != NULL ? (node->next != NULL ? node->previous : NULL) : NULL;
    if (node != NULL && node->next != NULL) return node->next;
    else return NULL;
}

LinkedListNode* LinkedList_getPrevious( LinkedListNode* node )
{
//    return node->previous != NULL ? node->previous : NULL;
    if (node != NULL && node->previous != NULL) return node->previous;
    else return NULL;
}

char* LinkedList_getData( LinkedListNode* node )
{
//    return node != NULL ? (node->data != NULL ? node->data : NULL) : NULL;
    if (node != NULL && node->data != NULL) return node->data;
    else return NULL;
}

unsigned int LinkedList_getSize( LinkedList* list )
{
    int i = 0;
    LinkedListNode* n;    

    if (list->first != NULL)
    {
        i += 1;
        for (n = list->first; n->next != NULL; n = n->next)
            i += 1;
    }
    
    return i;
}

char* LinkedList_getDataAt( LinkedList* list, unsigned int index )
{
    LinkedListNode* n = list->first;
    int i;    

    for (i = 0; i < index; i++)
        if (n != NULL)
            n = n->next;
    
    if (n != NULL)
        return n->data;
    else
        return "";
}
