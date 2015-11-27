#include "token.h"

typedef enum {
    DOT_STATUS,
    INT_PART_STATUS,
    FRAC_PART_STATUS,
    INIT_STATUS
} TokenStatus;

void initLine(char* line);
int getToken(Token* token);

