#include "test.h"
#include "../src/lex.h"

#include <assert.h>
#include <stdio.h>

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