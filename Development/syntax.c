#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 100

// Token types
enum TokenType {
    WHILE,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    IDENTIFIER,
    SEMICOLON,
    EOF_TOKEN
};

// Function to tokenize the input string
void tokenize(char* input, int* tokens) {
    char* token = strtok(input, " ");
    int i = 0;
    while (token != NULL) {
        if (strcmp(token, "while") == 0) {
            tokens[i++] = WHILE;
        } else if (strcmp(token, "(") == 0) {
            tokens[i++] = LPAREN;
        } else if (strcmp(token, ")") == 0) {
            tokens[i++] = RPAREN;
        } else if (strcmp(token, "{") == 0) {
            tokens[i++] = LBRACE;
        } else if (strcmp(token, "}") == 0) {
            tokens[i++] = RBRACE;
        } else if (strcmp(token, ";") == 0) {
            tokens[i++] = SEMICOLON;
        } else if (isalpha(token[0])) {
            tokens[i++] = IDENTIFIER;
        }
        token = strtok(NULL, " ");
    }
    tokens[i++] = EOF_TOKEN;
}

// Function to parse the while loop
int parseWhileLoop(int* tokens) {
    int index = 0;

    if (tokens[index] == WHILE) {
        index++;
        if (tokens[index] != LPAREN) {
            printf("Syntax Error: Expected '(' after 'while'\n");
            return 0;
        }
        index++;
        if (tokens[index] != IDENTIFIER) {
            printf("Syntax Error: Expected condition after '('\n");
            return 0;
        }
        index++;
        if (tokens[index] != RPAREN) {
            printf("Syntax Error: Expected ')' after condition\n");
            return 0;
        }
        index++;
        if (tokens[index] != LBRACE) {
            printf("Syntax Error: Expected '{' after while condition\n");
            return 0;
        }
        index++;
        if (tokens[index] != IDENTIFIER) {
            printf("Syntax Error: Expected statement after '{'\n");
            return 0;
        }
        index++;
        if (tokens[index] != SEMICOLON) {
            printf("Syntax Error: Expected ';' after statement\n");
            return 0;
        }
        index++;
        if (tokens[index] != RBRACE) {
            printf("Syntax Error: Expected '}' after statement\n");
            return 0;
        }
        index++;
        if (tokens[index] != EOF_TOKEN) {
            printf("Syntax Error: Expected end of input\n");
            return 0;
        }
    } else {
        printf("Syntax Error: Expected 'while'\n");
        return 0;
    }

    return 1;
}

int main() {
    char input[MAX_LENGTH];
    printf("Enter input containing a while loop: ");
    fgets(input, MAX_LENGTH, stdin);

    int tokens[MAX_LENGTH];
    memset(tokens, -1, sizeof(tokens));

    tokenize(input, tokens);

    if (parseWhileLoop(tokens)) {
        printf("Valid while loop\n");
    } else {
        printf("Invalid while loop\n");
    }

    return 0;
}