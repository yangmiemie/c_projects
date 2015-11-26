#define MAX_TOKEN_LENGTH 128

#define SUCCESS 0
#define BAD_CHAR 1
#define SYNTAX_ERROR 2
#define OVER_MAX_TOKEN_LEN 3

typedef enum {
  BAD_TOKEN,
  NUMBER_TOKEN,
  ADD_OPERATOR_TOKEN,
  SUB_OPERATOR_TOKEN,
  MUL_OPERATOR_TOKEN,
  DIV_OPERATOR_TOKEN,
  END_OF_LINE_TOKEN
} TokenType;

typedef struct {
  TokenType type;
  double value;
  char content[MAX_TOKEN_LENGTH];
} Token;
