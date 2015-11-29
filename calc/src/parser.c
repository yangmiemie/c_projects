#include "lex.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// #define DEBUG 0

void logInfo(char* fmt, ...);

char* errorMsg[] = {"", "bad character", "syntax error", "over max token length"};

static int isTokenBuffered;
static int isInParenthesis;
static Token* tokenBuffered;
static Token token;

double parseToken()
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
        logInfo("parseGetToken isTokenBuffered, tokenBuffered = %d, type = %d, value = %lf\n", tokenBuffered, tokenBuffered -> type, tokenBuffered -> value);
        isTokenBuffered = 0;
        memcpy(token, tokenBuffered, sizeof(Token));
    }
    else 
    {
        if ((n = getToken(token)) != SUCCESS)
        {
            logInfo("%s\n", errorMsg[n]);
            exit(1);
        }
    }
    
    logInfo("in parseGetToken, token.type = %d, token.value = %d\n", token -> type, token -> value);
    return SUCCESS;
}

double ungetToken(Token *token)
{
    isTokenBuffered = 1;
    logInfo("ungetToken, token %d,token type = %d, token value = %d\n", token, token -> type, token -> value);
    tokenBuffered = token;
}

int parsePrimaryTerm(Token *token)
{
    double value;

    parseGetToken(token);

    logInfo("in parsePrimaryTerm, token type = %d, token value = %d\n", token -> type, token -> value);
    if (token -> type == LEFT_PARENTHESIS_TOKEN)
    {
        isInParenthesis = 1;
        value = parseLine();
        token -> type = NUMBER_TOKEN;
        token -> value = value;
    }

    return SUCCESS;
}

double parseTerm()
{
    double value1, value2;
    int n, operator, positive;

    positive = 1;
    parsePrimaryTerm(&token);

    logInfo("in parseTerm\n");
    logInfo("token type = %d, token value = %d\n", token.type, token.value);

    if (token.type == ADD_OPERATOR_TOKEN || token.type == SUB_OPERATOR_TOKEN)
    {
        positive = token.type == SUB_OPERATOR_TOKEN ? -1 : 1;
        parseGetToken(&token);
    }

    if (token.type != NUMBER_TOKEN)
    {
        logInfo("%s\n", errorMsg[SYNTAX_ERROR]);
        exit(1);        
    }

    logInfo("token type = %d, token value = %d\n", token.type, token.value);
    logInfo("positive = %d\n", positive);
    value1 = token.value * positive;

    logInfo("in parseTerm, value1 = %lf\n", value1);

    for ( ; ; )
    {
        parseGetToken(&token);

        switch(token.type)
        {
            case ADD_OPERATOR_TOKEN:
            case SUB_OPERATOR_TOKEN:
                logInfo("ungetToken, token.type = %d, token.value = %d\n", token.type, token.value);
                ungetToken(&token);
                return value1;
                break;
            case MUL_OPERATOR_TOKEN:
            case DIV_OPERATOR_TOKEN:
                operator = token.type;
                break;
            case END_OF_LINE_TOKEN:
            case LEFT_PARENTHESIS_TOKEN:
            case RIGHT_PARENTHESIS_TOKEN:
                ungetToken(&token);
                return value1;
                break;
            default:
                logInfo("%s\n", errorMsg[SYNTAX_ERROR]);
                exit(1);              
                break;
        }

        logInfo("in parseTerm, operator = %d\n", token.type);

        parsePrimaryTerm(&token);
        if (token.type != NUMBER_TOKEN)
        {
            logInfo("%s\n", errorMsg[SYNTAX_ERROR]);
            exit(1);             
        }

        value2 = token.value;

        logInfo("in parseTerm, value2 = %lf\n", value2);

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

double parseLine()
{
    double value1, value2;
    Token token;
    int operator;

    logInfo("in parseLine\n");

    value1 = parseTerm();

    logInfo("in parseLine, value1 = %lf\n", value1);
    for ( ; ; )
    {
        parseGetToken(&token);

        logInfo("in parseLine, toke type = %d, token value = %d\n", token.type, token.value);
        switch(token.type)
        {
            case ADD_OPERATOR_TOKEN:
            case SUB_OPERATOR_TOKEN:
                operator = token.type;
                break;
            case END_OF_LINE_TOKEN:
                // missing right parenthesis
                if (isInParenthesis)
                {
                    logInfo("%s\n", errorMsg[SYNTAX_ERROR]);
                    exit(1);                    
                }
                return value1;
            case RIGHT_PARENTHESIS_TOKEN:
                if (!isInParenthesis)
                {
                    logInfo("%s\n", errorMsg[SYNTAX_ERROR]);
                    exit(1);                  
                }

                isInParenthesis = 0;
                return value1;
            case NUMBER_TOKEN:
                logInfo("%s\n", errorMsg[SYNTAX_ERROR]);
                exit(1);            
                break;
        }

        value2 = parseTerm();

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

void logInfo(char* fmt, ...)
{
#if defined DEBUG
    va_list ap;
    char *p, *sval;
    double dval;
    int ival;

    va_start(ap, fmt);

    for (p = fmt; *p; p++)
    {
    if (*p != '%')
    {
      putchar(*p);
      continue;
    }

    switch(*++p)
    {
      case 's':
        sval = va_arg(ap, char*);
        printf("%s", sval);
      break;
      case 'd':
        ival = va_arg(ap, int);
        printf("%d", ival);
      break;
      case 'f':
        dval = va_arg(ap, double);
        printf("%f", dval);
      break;
      default:
        putchar(*p);
        break;
    }
    }

    va_end(ap); 

#endif
}