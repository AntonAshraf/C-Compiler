#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LEN 100

typedef enum {
    KEYWORD,
    IDENTIFIER,
    CONSTANT,
    OPERATOR,
    DELIMITER
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LEN];
} Token;

int isKeyword(const char* str) {
    // List of keywords in C
    const char* keywords[] = {"int", "char", "float", "double", "void", "if", "else", "while", "do", "for", "switch", "case", "return", "break", "continue"};
    const int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    
    for (int i = 0; i < numKeywords; ++i) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

TokenType getTokenType(const char* token) {
    if (isKeyword(token)) {
        return KEYWORD;
    } else if (isdigit(token[0])) {
        return CONSTANT;
    } else if (isalpha(token[0]) || token[0] == '_') {
        return IDENTIFIER;
    } else if (strchr("+-*/%=&|<>!()", token[0])) {
        return OPERATOR;
    } else if (strchr(",;{}[]", token[0])) {
        return DELIMITER;
    } else {
        return -1;
    }
}

void tokenize(const char* input) {
    char* token;
    char copyInput[MAX_TOKEN_LEN];
    strcpy(copyInput, input);

    token = strtok(copyInput, " \t\n\r");

    while (token != NULL) {
        TokenType type = getTokenType(token);
        printf("Token: %s, Type: ", token);

        switch (type) {
            case KEYWORD:
                printf("Keyword\n");
                break;
            case IDENTIFIER:
                printf("Identifier\n");
                break;
            case CONSTANT:
                printf("Constant\n");
                break;
            case OPERATOR:
                printf("Operator\n");
                break;
            case DELIMITER:
                printf("Delimiter\n");
                break;
            default:
                printf("Invalid\n");
                break;
        }
        token = strtok(NULL, " \t\n\r");
    }
}

int main() {
    const char* input = "int a = 10; float b = 5.5; if (a > b) { printf(\"a is greater than b\"); }";
    printf("Input String: %s\n", input);
    printf("Tokenizing...\n\n");
    tokenize(input);

    return 0;
}
