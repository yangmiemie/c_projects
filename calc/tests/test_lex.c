#include "test.h"
#include "../src/lex.h"

#include <assert.h>
#include <stdio.h>
// typedef enum {
//   BAD_TOKEN,
//   NUMBER_TOKEN,
//   ADD_OPERATOR_TOKEN,
//   SUB_OPERATOR_TOKEN,
//   MUL_OPERATOR_TOKEN,
//   DIV_OPERATOR_TOKEN,
//   END_OF_LINE_TOKEN
// } TokenType;

// typedef struct {
//   TokenType type;
//   double value;
//   char content[MAX_TOKEN_LENGTH];
// } Token;

// #define SUCCESS 0
// #define BAD_CHAR 1
// #define SYNTAX_ERROR 2
// #define OVER_MAX_TOKEN_LEN 3

void test_lex()
{
  char *line;
  Token token;
  int n;

  line = "1 + 2";

  initLine(line);
  n = getToken(&token);

  assert(n == SUCCESS);
  assert(token.type == NUMBER_TOKEN);
  assert(token.value == 1);

  n = getToken(&token);
  assert(n == SUCCESS);
  assert(token.type == ADD_OPERATOR_TOKEN);

  n = getToken(&token);
  assert(n == SUCCESS);
  assert(token.type == NUMBER_TOKEN);
  assert(token.value == 2);

  line = "  1   +   2   ";
  initLine(line);
  n = getToken(&token);

  assert(n == SUCCESS);
  assert(token.type == NUMBER_TOKEN);
  assert(token.value == 1);

  n = getToken(&token);
  assert(n == SUCCESS);
  assert(token.type == ADD_OPERATOR_TOKEN);

  n = getToken(&token);
  assert(n == SUCCESS);
  assert(token.type == NUMBER_TOKEN);
  assert(token.value == 2);

  line = "  1 + 1. 2 ";
  initLine(line);
  n = getToken(&token);

  assert(n == SUCCESS);
  assert(token.type == NUMBER_TOKEN);
  assert(token.value == 1);

  n = getToken(&token);
  assert(n == SUCCESS);
  assert(token.type == ADD_OPERATOR_TOKEN);

  n = getToken(&token);
  assert(n == SYNTAX_ERROR);

  line = "  1 + 1.2.2 "; 
  initLine(line);
  n = getToken(&token);

  assert(n == SUCCESS);
  assert(token.type == NUMBER_TOKEN);
  assert(token.value == 1);

  n = getToken(&token);
  assert(n == SUCCESS);
  assert(token.type == ADD_OPERATOR_TOKEN);

  n = getToken(&token);
  assert(n == SYNTAX_ERROR);

  line = "  .1 + 1.2.2 "; 
  initLine(line);
  n = getToken(&token);

  assert(n == SYNTAX_ERROR);

  line = "  1 + .12 "; 
  initLine(line);
  n = getToken(&token);

  assert(n == SUCCESS);
  assert(token.type == NUMBER_TOKEN);
  assert(token.value == 1);

  n = getToken(&token);
  assert(n == SUCCESS);
  assert(token.type == ADD_OPERATOR_TOKEN);

  n = getToken(&token);
  assert(n == SYNTAX_ERROR);

  line = "  a1 + .12 "; 
  initLine(line);
  n = getToken(&token);

  assert(n == BAD_CHAR);

  line = "  1a + .12 "; 
  initLine(line);
  n = getToken(&token);

  assert(n == SUCCESS);
  assert(token.type == NUMBER_TOKEN);
  assert(token.value == 1);

  n = getToken(&token);
  assert(n == BAD_CHAR);

  line = "  1 1. + .12 "; 
  initLine(line);
  n = getToken(&token);

  assert(n == SUCCESS);
  assert(token.type == NUMBER_TOKEN);
  assert(token.value == 1);

  n = getToken(&token);
  assert(n == SYNTAX_ERROR);

}