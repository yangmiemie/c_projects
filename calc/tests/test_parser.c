#include "../src/parser.h"
#include "../src/lex.h"

#include <assert.h>
#include <stdio.h>

void test_parser()
{
    char *line;
    double value;

    line = "1 + 2";
    value = parseLine(line);
    assert(value == 3);

    line = "3 * 4";
    value = parseLine(line);
    assert(value == 12);

    line = "3 * 4 * 2 / 4";
    value = parseLine(line);
    assert(value == 6);

    line = "3 * 4 + 2 / 4";
    value = parseLine(line);
    assert(value == 12.5);

    line = "3 + 4 + 2 / 4";
    value = parseLine(line);
    assert(value == 7.5);

    line = "3 - 4 + 2 / 4";
    value = parseLine(line);
    assert(value == -0.5);    

    line = "3 - 4 + 2 * 4 + 9 + 3";
    value = parseLine(line);
    assert(value == 19); 

    line = "3 / 4 * 2 + 4 * 9 / 3";
    value = parseLine(line);
    assert(value == 13.5);      
}