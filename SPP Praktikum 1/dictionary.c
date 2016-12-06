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
    size_t successorCount;
};

Dictionary* Dictionary_create()
{
    Dictionary* dict = (Dictionary*) malloc(sizeof(Dictionary));
    
    dict->prefix = NULL;
    dict->word = false;
    dict->successors = (Dictionary **) malloc(0 * sizeof(Dictionary *));;
    dict->successorCount = 0;
    
    return dict;
}

void Dictionary_delete( Dictionary* dict )
{
    if (dict->successorCount > 0)
    {
        for (int i = 0; i < dict->successorCount + 1; i++)
        {
            Dictionary_delete(dict->successors[i]);
        }
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
    dict->successorCount = count;
    
    return dict;
}

Dictionary* cloneDictionary(const Dictionary* dict)
{
    Dictionary* d = (Dictionary*) malloc(sizeof(Dictionary));
    
    d->prefix = strdup(dict->prefix);
    d->successors = dict->successors;
    d->successorCount = dict->successorCount;
    d->word = dict->word;
    
    return d;
}

void addSuccessor (Dictionary* dict, Dictionary* node)
{
    if (strcmp(dict->prefix, node->prefix) == 0 && dict->word && node->word)
    {
        Dictionary_delete(node);
    }
    else
    {
        dict->successors = (Dictionary**) realloc(dict->successors, (dict->successorCount + 1) * sizeof(Dictionary*));
        
        dict->successors[dict->successorCount] = node;
        
        dict->successorCount += 1;
    }
}

Dictionary* getLoc(Dictionary* dict, const char* word)
{
    if (dict == NULL)
        return NULL;
    
    static Dictionary* loc;
    static const char* lastWord = "";
    static char* aprefix = "";
    
    if (strcmp(lastWord, "") == 0 || strcmp(lastWord, word) != 0)
    {
        aprefix = "";
        loc = NULL;
        lastWord = word;
    }
    
    for (int i = 0; i < dict->successorCount; i++)
    {
        if (strcmp(dict->successors[i]->prefix, word) == 0)
        {
            loc = dict->successors[i];
            break;
        }
        else
        {
            char* bprefix = commonPrefix(dict->successors[i]->prefix, word);
            
            if (strlen(bprefix) > strlen(aprefix))
            {
                aprefix = bprefix;
                loc = dict->successors[i];
            }
        }
    }
    
    for (int i = 0; i < dict->successorCount; i++) {
        Dictionary* temp = getLoc(dict->successors[i], word);
        
        char* bprefix = commonPrefix(temp->prefix, word);
        
        if (strlen(bprefix) > strlen(aprefix))
        {
            aprefix = bprefix;
            loc = temp;
        }
    }
    
    return loc;
}

void sortSucc(Dictionary* dict)
{
    if (dict == NULL)
        return;
    
    if (dict->successorCount == 0)
        return;
    
    for (unsigned long int j = dict->successorCount; j > 1; j--)
    {
        for (int i = 0; i < j - 1; i++)
        {
            const char* str1 = dict->successors[i]->prefix;
            const char* str2 = dict->successors[i+1]->prefix;
            if (strcmp(str1, str2) > 0)
            {
                Dictionary* temp = dict->successors[i];
                dict->successors[i] = dict->successors[i+1];
                dict->successors[i+1] = temp;
            }
        }
    }
    
    for (int i = 0; i < dict->successorCount; i++)
    {
        sortSucc(dict->successors[i]);
    }
}

void Dictionary_insert( Dictionary* dict, const char* word )
{
//    printf("%s - %s\n", word, dict->prefix);
    
    if (dict->prefix == NULL && dict->successorCount == 0)
    {
        dict->prefix = strdup(word);
        dict->word = true;
    }
    else if (strcmp(dict->prefix, word) == 0)
    {
        dict->word = true;
    }
    else
    {
        char* prefix = commonPrefix(dict->prefix, word);
        
        if (strcmp(dict->prefix, "") == 0)
        {
            Dictionary* new = createNode(word, true, NULL, 0);
            
            dict->prefix = prefix;
            dict->word = false;
            
            bool found = false;
            
            for (int i = 0; i < dict->successorCount; i++)
            {
                char* aprefix = commonPrefix(dict->successors[i]->prefix, word);
                
                if (strcmp(aprefix, "") != 0)
                {
                    Dictionary_insert(dict->successors[i], word);
                    found = true;
                }
            }
            
            if (!found)
                addSuccessor(dict, new);
        }
        else if (strcmp(prefix, "") == 0)
        {
            Dictionary* clone = cloneDictionary(dict);
            Dictionary* new = createNode(word, true, NULL, 0);
            
            dict->prefix = prefix;
            dict->word = false;
            dict->successors = NULL;
            dict->successorCount = 0;
            
            addSuccessor(dict, clone);
            addSuccessor(dict, new);
        }
        else
        {
            if (strcmp(dict->prefix, word) == 0)
            {
                Dictionary* new = createNode(word, true, NULL, 0);
                addSuccessor(dict, new);
            }
            else
            {
                Dictionary* loc = getLoc(dict, word);
                
                if (loc != NULL && strcmp(loc->prefix, word) == 0)
                {
                    addSuccessor(loc, createNode(word, true, NULL, 0));
                }
                
                if (loc != NULL && loc != dict && strlen(commonPrefix(loc->prefix, word)) > strlen(commonPrefix(dict->prefix, word)))
                {
                    Dictionary_insert(loc, word);
                }
                else
                {                    
                    if (strcmp(dict->prefix, prefix) != 0)
                    {
                        Dictionary* clone = cloneDictionary(dict);
//                        printf("dict->prefix: %s - prefix: %s\n", dict->prefix, prefix);
//                        if (loc != NULL)
//                            printf("Loc: %s\n", loc->prefix);
                        dict->prefix = prefix;
                        dict->word = false;
                        dict->successors = NULL;
                        dict->successorCount = 0;
                        
                        addSuccessor(dict, clone);
                    }
                    
                    Dictionary* new = createNode(word, true, NULL, 0);
                    addSuccessor(dict, new);
                }
            }
        }
        sortSucc(dict);
    }
}

int Dictionary_isIn( const Dictionary* dict, const char* word )
{
    if (dict == NULL)
        return 0;
    
    if (dict->word && strcmp(dict->prefix, word) == 0)
        return 1;
    
    if (dict->successorCount == 0)
    {
        return 0;
    }
    
    int found = 0;
    
    for (int i = 0; i < dict->successorCount; i++)
    {
        if (!found && Dictionary_isIn(dict->successors[i], word))
        {
            found = 1;
            break;
        }
    }
    
    return found;
}

void Dictionary_print( const Dictionary* dict )
{
    if (dict == NULL)
        return;
    
    if (dict->word)
        printf("%s\n", dict->prefix);
    
    for (int i = 0; i < dict->successorCount; i++) {
        Dictionary_print(dict->successors[i]);
    }
}

void Dictionary_merge( Dictionary* destination, const Dictionary* source )
{
    if (source == NULL)
        return;
    
    if (source->word)
        Dictionary_insert(destination, source->prefix);
    
    for (int i = 0; i < source->successorCount; i++)
    {
        Dictionary_merge(destination, source->successors[i]);
    }
}
