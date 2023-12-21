#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Token types
typedef enum {
    INT,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    IDENTIFIER,
    ASSIGN,
    SEMICOLON,
    END_OF_FILE
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value[100];  // For simplicity, assuming identifiers and numbers have a maximum length of 100 characters
} Token;

// Lexical analyzer
Token getNextToken() {
    Token token;
    char c = getchar();

    while (isspace(c)) {
        c = getchar();
    }

    if (c == EOF) {
        token.type = END_OF_FILE;
        strcpy(token.value, "EOF");
        return token;
    }

    if (isdigit(c)) {
        token.type = INT;
        int i = 0;
        while (isdigit(c)) {
            token.value[i++] = c;
            c = getchar();
        }
        token.value[i] = '\0';
        ungetc(c, stdin);
    } else if (isalpha(c)) {
        token.type = IDENTIFIER;
        int i = 0;
        while (isalnum(c)) {
            token.value[i++] = c;
            c = getchar();
        }
        token.value[i] = '\0';
        ungetc(c, stdin);
    } else {
        switch (c) {
            case '+':
                token.type = PLUS;
                break;
            case '-':
                token.type = MINUS;
                break;
            case '*':
                token.type = MULTIPLY;
                break;
            case '/':
                token.type = DIVIDE;
                break;
            case '(':
                token.type = LPAREN;
                break;
            case ')':
                token.type = RPAREN;
                break;
            case '=':
                token.type = ASSIGN;
                break;
            case ';':
                token.type = SEMICOLON;
                break;
            default:
                // Handle unknown characters or errors
                fprintf(stderr, "Unknown character: %c\n", c);
                exit(EXIT_FAILURE);
        }
        sprintf(token.value, "%c", c);
    }

    return token;
}

// Syntax analyzer
void parseExpression();

void parseFactor() {
    Token token = getNextToken();
    if (token.type == INT || token.type == IDENTIFIER) {
        // Valid factor
    } else if (token.type == LPAREN) {
        parseExpression();
        token = getNextToken();
        if (token.type != RPAREN) {
            fprintf(stderr, "Expected ')'\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Invalid factor\n");
        exit(EXIT_FAILURE);
    }
}

void parseTerm() {
    parseFactor();
    Token token = getNextToken();
    while (token.type == MULTIPLY || token.type == DIVIDE) {
        parseFactor();
        token = getNextToken();
    }
    ungetc(token.value[0], stdin);
}

void parseExpression() {
    parseTerm();
    Token token = getNextToken();
    while (token.type == PLUS || token.type == MINUS) {
        parseTerm();
        token = getNextToken();
    }
    ungetc(token.value[0], stdin);
}

// Semantic analyzer (dummy function for illustration)
void performSemanticAnalysis() {
    // Dummy function - actual semantic analysis would involve checking the validity of the parsed structure
    printf("Semantic analysis performed successfully\n");
}

int main() {
    printf("Enter an expression: ");
    parseExpression();

    Token token = getNextToken();
    if (token.type != SEMICOLON && token.type != END_OF_FILE) {
        fprintf(stderr, "Expected end of expression or statement\n");
        return EXIT_FAILURE;
    }

    performSemanticAnalysis();

    printf("Compilation successful\n");

    return EXIT_SUCCESS;
}