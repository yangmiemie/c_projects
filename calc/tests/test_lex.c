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

    n = getToken(&token);
    assert(token.type == END_OF_LINE_TOKEN);

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

    n = getToken(&token);
    assert(token.type == END_OF_LINE_TOKEN);
    
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

    line = "( 1 + 2 ) * ( 2 / 3 )";
    initLine(line);

    n = getToken(&token);
    assert(n == SUCCESS);
    assert(token.type == LEFT_PARENTHESIS_TOKEN);

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

    n = getToken(&token);
    assert(n == SUCCESS);
    assert(token.type == RIGHT_PARENTHESIS_TOKEN);

    n = getToken(&token);
    assert(n == SUCCESS);
    assert(token.type == MUL_OPERATOR_TOKEN);

    n = getToken(&token);
    assert(n == SUCCESS);
    assert(token.type == LEFT_PARENTHESIS_TOKEN);

    n = getToken(&token);
    assert(n == SUCCESS);
    assert(token.type == NUMBER_TOKEN);
    assert(token.value == 2);  

    n = getToken(&token);
    assert(n == SUCCESS);
    assert(token.type == DIV_OPERATOR_TOKEN);

    n = getToken(&token);
    assert(n == SUCCESS);
    assert(token.type == NUMBER_TOKEN);
    assert(token.value == 3);  

    n = getToken(&token);
    assert(n == SUCCESS);
    assert(token.type == RIGHT_PARENTHESIS_TOKEN);

    n = getToken(&token);
    assert(n == SUCCESS);
    assert(token.type == END_OF_LINE_TOKEN);
}