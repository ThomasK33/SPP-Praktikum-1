//
//  dictionary.c
//  SPP Praktikum 1
//
//  Created by Thomas Kosiewski on 01.12.16.
//  Copyright © 2016 Thomas Kosiewski. All rights reserved.
//

#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct Dictionary {
    bool word;
    struct Dictionary** children;
};

void addSuffix(Dictionary* node, const char* suffix);
int checkSuffix(const Dictionary* node, const char* suffix);
void printNode(const Dictionary* node, char* prefix);
void mergeNode(const Dictionary* node, Dictionary* dict, char* prefix);
void deleteNode(Dictionary* node);
Dictionary* createNode(bool w);

Dictionary *Dictionary_create() {
    Dictionary* dict = createNode(false);
    return dict;
}

void Dictionary_delete(Dictionary *dict) {
    deleteNode(dict);
}

void Dictionary_insert(Dictionary *dict, const char *word) {
    addSuffix(dict, word);
}

int Dictionary_isIn(const Dictionary *dict, const char *word) {
    return checkSuffix(dict, word);
}

void Dictionary_print(const Dictionary *dict) {
    char prefix[128] = "";
    
    printNode(dict, prefix);
}

void Dictionary_merge(Dictionary *destination, const Dictionary *source) {
    char prefix[128] = "";
    
    mergeNode(source, destination, prefix);
}

void addSuffix(Dictionary* node, const char *suffix) {
    if (!strlen(suffix)) {
        node->word = true;
    } else if (!isalpha(*suffix)) {
//        printf("Adding a new suffix requires a symbol between A and Z, but got \"%c\".\n", *suffix);
//        perror("");
        
    } else if (node->children[(int)(*suffix - (int)'A')] != NULL) {
        addSuffix(node->children[(int)(*suffix - (int)'A')], suffix + 1);
    } else if (strlen(suffix) == 1) {
        Dictionary* newChild = createNode(true);
        
        node->children[(int)(*suffix - (int)'A')] = newChild;
        
    } else {
        Dictionary* newChild = createNode(false);
        
        node->children[(int)(*suffix - (int)'A')] = newChild;
        
        addSuffix(newChild, suffix + 1);
    }
}

int checkSuffix(const Dictionary* node, const char* suffix) {
    if (node == NULL)
    {
        return 0;
    }
    else if (!strlen(suffix)) {
        return 1;
    } else if (!isalpha(*suffix)) {
//        printf("Checking for a valid word requires a symbol between A and Z, but got %c.", suffix[0]);
//        perror("");
        return 0;
    } else if (node->children[(int)(*suffix - (int)'A')] == NULL) {
        return 0;
    } else if (strlen(suffix) == 1) {
        return 1;
    } else {
        return checkSuffix(node->children[(int)(*suffix) - (int)'A'], suffix + 1);
    }
}

void printNode(const Dictionary* node, char *prefix) {
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != NULL) {
            prefix[(int)strlen(prefix)] = 'A' + (char) (i);
            
            if (node->children[i]->word) {
                printf("%s\n", prefix);
            }
            printNode(node->children[i], prefix);
            prefix[(int)strlen(prefix) - 1] = '\0';
        }
    }
}

void mergeNode(const Dictionary* node, Dictionary* dict, char *prefix) {
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != NULL) {
            prefix[(int)strlen(prefix)] = 'A' + (char) (i);
            
            if (node->children[i]->word) {
                Dictionary_insert(dict, prefix);
            }
            
            mergeNode(node->children[i], dict, prefix);
            prefix[(int)strlen(prefix) - 1] = '\0';
        }
    }
}

Dictionary* createNode(bool w)
{
    Dictionary* dict = (Dictionary*) malloc(sizeof(Dictionary));
    dict->word = w;
//    dict->children = (Dictionary**) calloc(26, sizeof(Dictionary*));
    
    dict->children = (Dictionary**) malloc(26 * sizeof(Dictionary*));
    bzero(dict->children, 26 * sizeof(Dictionary*));
    
    return dict;
}

void deleteNode(Dictionary* node) {
    if (node != NULL)
    {
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != NULL) {
                deleteNode(node->children[i]);
            }
        }
        
        free(node);
    }
}
