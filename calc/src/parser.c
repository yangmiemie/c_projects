#include "lex.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// typedef enum {
//     BAD_TOKEN,
//     NUMBER_TOKEN,
//     ADD_OPERATOR_TOKEN,
//     SUB_OPERATOR_TOKEN,
//     MUL_OPERATOR_TOKEN,
//     DIV_OPERATOR_TOKEN,
//     END_OF_LINE_TOKEN
// } TokenType;

// typedef struct {
//     TokenType type;
//     double value;
//     char content[MAX_TOKEN_LENGTH];
// } Token;

// #define SUCCESS 0
// #define BAD_CHAR 1
// #define SYNTAX_ERROR 2
// #define OVER_MAX_TOKEN_LEN 3

char* errorMsg[] = {"", "bad character", "syntax error", "over max token length"};

static int isTokenBuffered;
static Token* tokenBuffered;

double parseToken(char* line)
{
    Token token;

    if (getToken(&token) == SUCCESS)
    {
        return token.value;
    }
}

int parseGetToken(Token* token)
{
    int n;

    if (isTokenBuffered)
    {
        isTokenBuffered = 0;
        memcpy(token, tokenBuffered, sizeof(Token));
    }
    else 
    {
        if ((n = getToken(token)) != SUCCESS)
        {
            printf("%s\n", errorMsg[n]);
            exit(1);
        }        
    }

    return SUCCESS;
}

double ungetToken(Token *token)
{
    isTokenBuffered = 1;
    tokenBuffered = token;
}

double parseTerm(char* line)
{
    double value1, value2;
    Token token;
    int n, operator;

    parseGetToken(&token);

    if (token.type != NUMBER_TOKEN)
    {
        printf("%s\n", errorMsg[SYNTAX_ERROR]);
        exit(1);        
    }

    value1 = token.value;

    for ( ; ; )
    {
        parseGetToken(&token);

        switch(token.type)
        {
            case ADD_OPERATOR_TOKEN:
            case SUB_OPERATOR_TOKEN:
                ungetToken(&token);
                return value1;
                break;
            case MUL_OPERATOR_TOKEN:
            case DIV_OPERATOR_TOKEN:
                operator = token.type;
                break;
            case END_OF_LINE_TOKEN:
                ungetToken(&token);
                return value1;
                break;
            default:
                printf("%s\n", errorMsg[SYNTAX_ERROR]);
                exit(1);              
                break;
        }

        parseGetToken(&token);
        if (token.type != NUMBER_TOKEN)
        {
            printf("%s\n", errorMsg[SYNTAX_ERROR]);
            exit(1);             
        }

        value2 = token.value;

        if (operator == MUL_OPERATOR_TOKEN)
        {
            value1 = value1 * value2;
        }
        else if (operator == DIV_OPERATOR_TOKEN)
        {
            value1 = value1 / value2;
        }
    }

}

double parseLine(char *line)
{
    double value1, value2;
    Token token;
    int operator;

    initLine(line);
    value1 = parseTerm(line);

    for ( ; ; )
    {
        parseGetToken(&token);

        switch(token.type)
        {
            case ADD_OPERATOR_TOKEN:
            case SUB_OPERATOR_TOKEN:
                operator = token.type;
                break;
            case END_OF_LINE_TOKEN:
                return value1;
            case NUMBER_TOKEN:
                printf("%s\n", errorMsg[SYNTAX_ERROR]);
                exit(1);            
                break;
        }

        value2 = parseTerm(line);

        if (operator == ADD_OPERATOR_TOKEN)
        {
            value1 += value2;
        }
        else if (operator == SUB_OPERATOR_TOKEN)
        {
            value1 -= value2;
        }
    }
}