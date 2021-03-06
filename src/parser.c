//
//  parser.c
//  SPP Praktikum 1
//
//  Created by Thomas Kosiewski on 29.11.16.
//  Copyright © 2016 Thomas Kosiewski. All rights reserved.
//

#include "parser.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Parser {
    unsigned long int currentPosition;
    const char* text;
};

Parser* Parser_create( const char* text )
{
    Parser* p = (Parser*) malloc(sizeof(Parser));
    
    p->currentPosition = 0;
    p->text = text;
    
    return p;
}

void convertToUpperCase(char *sPtr)
{
    while(*sPtr != '\0')
    {
        *sPtr = toupper(*sPtr);
        sPtr++;
    }
}

int Parser_getNextWord( Parser* parser, char* nextWord, unsigned int bufferLength )
{
    if (parser == NULL || parser->text == NULL)
        return -1;
    
    char buff[bufferLength];
    
    int i = sscanf(parser->text + parser->currentPosition, "%s", buff);
    parser->currentPosition += strlen(buff) + 1;
    
    if (strlen(buff) < bufferLength)
    {
        bzero(nextWord, bufferLength);
        convertToUpperCase(buff);
        strncpy(nextWord, buff, strlen(buff));
    }
    else
    {
        return 0;
    }
    
    return i;
}

void Parser_delete( Parser* parser )
{
    free(parser);
}
