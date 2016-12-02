//
//  dictionary.c
//  SPP Praktikum 1
//
//  Created by Thomas Kosiewski on 01.12.16.
//  Copyright © 2016 Thomas Kosiewski. All rights reserved.
//

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Dictionary {
    char* prefix;
    bool word;
    Dictionary** successors;
    size_t sucessorCount;
};

Dictionary* Dictionary_create()
{
    Dictionary* dict = (Dictionary*) malloc(sizeof(Dictionary));
    
    dict->prefix = NULL;
    dict->word = false;
    dict->successors = (Dictionary **) malloc(0 * sizeof(Dictionary *));;
    dict->sucessorCount = 0;
    
    return dict;
}

void Dictionary_delete( Dictionary* dict )
{
    for (int i = 0; i < (sizeof(dict->successors) / sizeof(dict->successors[0])); i++)
    {
        Dictionary_delete(dict->successors[i]);
    }
    
    if (dict->prefix != NULL)
        free(dict->prefix);
    
    free(dict);
}

char* commonPrefix(const char* word, const char* prefix)
{
    unsigned long int maxSize;
    
    if (strlen(word) > strlen(prefix))
    {
        maxSize = strlen(prefix);
    }
    else
    {
        maxSize = strlen(word);
    }
    
    int i;
    for (i = 0; i < maxSize && prefix[i] == word[i]; i++);
    
    char* subbuff = (char*) malloc(i * sizeof(char) + 1);
    bzero(subbuff, sizeof(subbuff));
    memcpy(subbuff, word, i);
    
    return subbuff;
}

Dictionary* createNode(const char* prefix, bool word, Dictionary** suc, size_t count)
{
    Dictionary* dict = (Dictionary*) malloc(sizeof(Dictionary));
    
    char* pf = strdup(prefix);
    
    dict->prefix = pf;
    dict->word = word;
    dict->successors = suc;
    dict->sucessorCount = count;
    
    return dict;
}

Dictionary* cloneDictionary(const Dictionary* dict)
{
    Dictionary* d = (Dictionary*) malloc(sizeof(Dictionary));
    
    d->prefix = strdup(dict->prefix);
    d->successors = dict->successors;
    d->sucessorCount = dict->sucessorCount;
    d->word = dict->word;
    
    return d;
}

void addSuccessor (Dictionary* dict, Dictionary* node)
{
    dict->successors = (Dictionary**) realloc(dict->successors, (dict->sucessorCount + 1) * sizeof(Dictionary*));
    
    dict->successors[dict->sucessorCount] = node;
    
    dict->sucessorCount += 1;
}

void mergeByPrefix(const char* word, Dictionary* dict)
{
    char* prefix = commonPrefix(word, dict->prefix);
    
    if (strcmp(prefix, dict->prefix) == 0)
    {
        addSuccessor(dict, createNode(word, true, NULL, 0));
    }
    else
    {
        Dictionary* d = cloneDictionary(dict);
        
        dict->prefix = prefix;
        dict->successors = NULL;
        dict->sucessorCount = 0;
        dict->word = false;
        
        if (d->prefix[strlen(prefix)] < word[strlen(prefix)])
        {
            addSuccessor(dict, d);
            addSuccessor(dict, createNode(word, true, NULL, 0));
        }
        else
        {
            addSuccessor(dict, createNode(word, true, NULL, 0));
            addSuccessor(dict, d);
        }
    }
}

void Dictionary_insert( Dictionary* dict, const char* word )
{
    printf("%s\n", word);
    
    if (dict->prefix == NULL && dict->sucessorCount == 0)
    {
        dict->prefix = strdup(word);
        dict->word = true;
    }
    else if (strcmp(dict->prefix, word) == 0)
    {
        dict->word = true;
    }
    else if (strcmp(dict->prefix, "") == 0)
    {
        int i;
        for (i = 0; dict->successors[i] != NULL && word[0] > dict->successors[i]->prefix[0]; i++);
        
        if (dict->successors[i] != NULL && word[0] == dict->successors[i]->prefix[0])
        {
            mergeByPrefix(word, dict->successors[i]);
        }
        else
        {
            printf("To insert after index: %i\n", i);
        }
    }
    else
    {
        if (dict->prefix != NULL && word[0] != dict->prefix[0])
        {
            Dictionary* temp = createNode(dict->prefix, dict->word, dict->successors, dict->sucessorCount);
            
            dict->prefix = "";
            dict->word = false;
            dict->sucessorCount = 0;
            dict->successors = NULL;
            
            if (temp->prefix[0] < word[0])
            {
                addSuccessor(dict, temp);
                addSuccessor(dict, createNode(word, true, NULL, 0));
            }
            else
            {
                addSuccessor(dict, createNode(word, true, NULL, 0));
                addSuccessor(dict, temp);
            }
        }
        else
            mergeByPrefix(word, dict);
    }
}

int Dictionary_isIn( const Dictionary* dict, const char* word );

void Dictionary_print( const Dictionary* dict );

void Dictionary_merge( Dictionary* destination, const Dictionary* source );
