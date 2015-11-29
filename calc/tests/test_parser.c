#include "../src/parser.h"
#include "../src/lex.h"

#include <assert.h>
#include <stdio.h>

void test_parser()
{
    char *line;
    double value;

    line = "1 + 2";
    initLine(line);
    value = parseLine(line);
    assert(value == 3);

    line = "3 * 4";
    initLine(line);
    value = parseLine(line);
    assert(value == 12);

    line = "3 * 4 * 2 / 4";
    initLine(line);
    value = parseLine(line);
    assert(value == 6);

    line = "3 * 4 + 2 / 4";
    initLine(line);
    value = parseLine(line);
    assert(value == 12.5);

    line = "3 + 4 + 2 / 4";
    initLine(line);
    value = parseLine(line);
    assert(value == 7.5);

    line = "3 - 4 + 2 / 4";
    initLine(line);
    value = parseLine(line);
    assert(value == -0.5);    

    line = "3 - 4 + 2 * 4 + 9 + 3";
    initLine(line);
    value = parseLine(line);
    assert(value == 19); 

    line = "3 / 4 * 2 + 4 * 9 / 3";
    initLine(line);
    value = parseLine(line);
    assert(value == 13.5);    

    line = "-1 + 2";
    initLine(line);
    value = parseLine(line);
    assert(value == 1);  

    line = "-3 * 4";
    initLine(line);
    value = parseLine(line);
    assert(value == -12);

    line = "-3 * 4 * 2 / 4";
    initLine(line);
    value = parseLine(line);
    assert(value == -6);

    line = "-3 * 4 + 2 / 4";
    initLine(line);
    value = parseLine(line);
    assert(value == -11.5);

    line = "-3 + 4 + 2 / 4";
    initLine(line);
    value = parseLine(line);
    assert(value == 1.5);

    line = "-3 - 4 + 2 / 4";
    initLine(line);
    value = parseLine(line);
    assert(value == -6.5);    

    line = "(1 + 2)";
    initLine(line);
    value = parseLine(line);
    assert(value == 3);

    line = "(1 + 2) * 3";
    initLine(line);
    value = parseLine(line);
    assert(value == 9);

    line = "(1 + 2) / 3";
    initLine(line);
    value = parseLine(line);
    assert(value == 1);

    line = "3 * (1 + 2)";
    initLine(line);
    value = parseLine(line);
    assert(value == 9);

    line = "2 + 3 * (1 + 2)";
    initLine(line);
    value = parseLine(line);
    assert(value == 11);

    line = "2 + 3 - (1 + 2) + 3";
    initLine(line);
    value = parseLine(line);
    assert(value == 5);

    line = "-2 * (1 + 2) + 3";
    initLine(line);
    value = parseLine(line);
    assert(value == -3);

    line = "(-2 + 4) * (1 - 2) * 3";
    initLine(line);
    value = parseLine(line);
    assert(value == -6);

}