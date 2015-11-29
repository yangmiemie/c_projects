#include "parser.h"
#include "lex.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char line[MAX_EXPRESSION_LENGTH];
    double value;
    int n;

    while (fgets(line, MAX_EXPRESSION_LENGTH, stdin) != NULL)
    {
        line[strlen(line) - 1] = '\0';
        initLine(line);
        value = parseLine(line);
        printf(">> %lf\n", value);
    }

    return 0;
}