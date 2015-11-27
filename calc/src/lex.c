#include <stdio.h>

#include "lex.h"

static int indexOfLine;
static char* inputLine;

int getToken(Token* token)
{
    char currentChar;
    int indexOfToken;
    TokenStatus status;

    status = INIT_STATUS;
    indexOfToken = 0;

    for ( ; ; )
    {
    currentChar = inputLine[indexOfLine];

    if ((status == INT_PART_STATUS || status == FRAC_PART_STATUS) 
      && !isdigit(currentChar) && (currentChar != '.'))
    {
      token -> type = NUMBER_TOKEN;
      sscanf(token -> content, "%lf", &token -> value);
      return SUCCESS;
    }

    if (currentChar == ' ')
    {
      // such as 1. 2
      if (status == DOT_STATUS)
      {
        return SYNTAX_ERROR;
      }

      indexOfLine++;
      // status is INIT_STATUS and ignore space
      continue;
    }

    if (currentChar == '\0')
    {
      // such as 1.
      if (status == DOT_STATUS)
      {
        return SYNTAX_ERROR;
      }

      token -> type = END_OF_LINE_TOKEN;
      return SUCCESS;
    }

    token -> content[indexOfToken++] = currentChar;
    token -> content[indexOfToken] = '\0';
    indexOfLine++;

    if (indexOfToken >= MAX_TOKEN_LENGTH)
    {
      return OVER_MAX_TOKEN_LEN;
    }

    switch(currentChar) 
    {
      case '+':
        token -> type = ADD_OPERATOR_TOKEN;
        return SUCCESS;
      case '-':
        token -> type = SUB_OPERATOR_TOKEN;
        return SUCCESS;
      case '*':
        token -> type = MUL_OPERATOR_TOKEN;
        return SUCCESS;
      case '/':
        token -> type = DIV_OPERATOR_TOKEN;
        return SUCCESS;
      case '.':
        if (status == INT_PART_STATUS)
        {
          status = DOT_STATUS;
        }
        else
        {
          // such as .2, 2.2.2, 2..
          return SYNTAX_ERROR;
        }
        break;
      default:
        if (isdigit(currentChar))
        {
          if (status == DOT_STATUS)
            status = FRAC_PART_STATUS;

          if (status == INIT_STATUS)
            status = INT_PART_STATUS;
        }
        else
        {
          return BAD_CHAR;
        }
      }
    }
}

void initLine(char* line)
{
    inputLine = line;
    indexOfLine = 0;
}