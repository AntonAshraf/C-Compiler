#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 100
#define MAX_IDENTIFIER_COUNT 1000 // Maximum number of unique identifiers

// Token types enumeration
typedef enum {
    WHILE, LPAREN, RPAREN, LBRACE, RBRACE, SEMICOLON, IDENTIFIER,
    GREATER_THAN, LESS_THAN, GREATER_THAN_EQUAL, LESS_THAN_EQUAL, EQUAL, NOT_EQUAL,
    AND, OR, NOT, PLUS, MINUS, MULTIPLY, DIVIDE, ASSIGN, END_OF_FILE,
    DIGIT, HASH, INT, FLOAT, CHAR, MAIN, SINGLE_QUOTE, DOUBLE_QUOTE,
    NEWLINE, TAB
} TokenType;

// Structure to represent a token
typedef struct {
    TokenType type;
    char lexeme[MAX_TOKEN_LENGTH];
} Token;

// Structure to manage identifiers and their counts
typedef struct {
    char name[MAX_TOKEN_LENGTH];
    int count;
} IdentifierCount;

IdentifierCount identifiers[MAX_IDENTIFIER_COUNT];
int identifierIndex = 0;

// Function to get the next token from input
Token getNextToken(FILE *fp) {
    Token token;
    char ch = fgetc(fp);
    token.lexeme[0] = '\0';

    while (isspace(ch) || ch == '\n' || ch == '\t') {
        if (ch == '\n') {
            token.type = NEWLINE;
        } else if (ch == '\t') {
            token.type = TAB;
        }
        ch = fgetc(fp);
    }

    if (ch == EOF) {
        token.type = END_OF_FILE;
    } else if (isalpha(ch)) {
        // Identifier or reserved word
        int i = 0;
        while (isalnum(ch) || ch == '_') {
            token.lexeme[i++] = ch;
            ch = fgetc(fp);
        }
        token.lexeme[i] = '\0';

        // Check if it's a reserved word
        if (strcmp(token.lexeme, "while") == 0) {
            token.type = WHILE;
        } else if (strcmp(token.lexeme, "int") == 0) {
            token.type = INT;
        } else if (strcmp(token.lexeme, "float") == 0) {
            token.type = FLOAT;
        } else if (strcmp(token.lexeme, "char") == 0) {
            token.type = CHAR;
        } else if (strcmp(token.lexeme, "main") == 0) {
            token.type = MAIN;
        } else {
                  // Check if the identifier exists in the list
            int j, existing = -1;
            for (j = 0; j < identifierIndex; ++j) {
                if (strcmp(identifiers[j].name, token.lexeme) == 0) {
                    existing = j;
                    break;
                }
            }

            // If the identifier exists, assign its count
            if (existing != -1) {
                snprintf(token.lexeme, MAX_TOKEN_LENGTH, "%s%d", token.lexeme, identifiers[existing].count);
                identifiers[existing].count++;
            } else {
                // Add new identifier to the list
                snprintf(identifiers[identifierIndex].name, MAX_TOKEN_LENGTH, "%s", token.lexeme);
                identifiers[identifierIndex].count = 1;
                identifierIndex++;
            }

            token.type = IDENTIFIER;
        }

        ungetc(ch, fp); // Put back the non-alphanumeric character
    } else if (isdigit(ch)) {
        // Digits handling
        int i = 0;
        while (isdigit(ch)) {
            token.lexeme[i++] = ch;
            ch = fgetc(fp);
        }
        token.lexeme[i] = '\0';
        token.type = DIGIT;

        ungetc(ch, fp); // Put back the non-digit character
    } else {
        // Single character tokens or operators
        switch (ch) {
            case '(':
                token.type = LPAREN;
                break;
            case ')':
                token.type = RPAREN;
                break;
            case '{':
                token.type = LBRACE;
                break;
            case '}':
                token.type = RBRACE;
                break;
            case ';':
                token.type = SEMICOLON;
                break;
            case '>':
                ch = fgetc(fp);
                if (ch == '=') {
                    token.type = GREATER_THAN_EQUAL;
                } else {
                    token.type = GREATER_THAN;
                    ungetc(ch, fp);
                }
                break;
            case '<':
                ch = fgetc(fp);
                if (ch == '=') {
                    token.type = LESS_THAN_EQUAL;
                } else {
                    token.type = LESS_THAN;
                    ungetc(ch, fp);
                }
                break;
            case '=':
                ch = fgetc(fp);
                if (ch == '=') {
                    token.type = EQUAL;
                } else {
                    token.type = ASSIGN;
                    ungetc(ch, fp);
                }
                break;
            case '!':
                ch = fgetc(fp);
                if (ch == '=') {
                    token.type = NOT_EQUAL;
                } else {
                    token.type = NOT;
                    ungetc(ch, fp);
                }
                break;
            case '&':
                ch = fgetc(fp);
                if (ch == '&') {
                    token.type = AND;
                } else {
                    fprintf(stderr, "Error: Invalid character '&'\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case '|':
                ch = fgetc(fp);
                if (ch == '|') {
                    token.type = OR;
                } else {
                    fprintf(stderr, "Error: Invalid character '|'\n");
                    exit(EXIT_FAILURE);
                }
                break;
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
            case '#':
                token.type = HASH;
                break;
            case '\'':
                token.type = SINGLE_QUOTE;
                break;
            case '\"':
                token.type = DOUBLE_QUOTE;
                break;
            default:
                fprintf(stderr, "Error: Invalid character '%c'\n", ch);
                exit(EXIT_FAILURE);
        }
    }

    return token;
}

// Function to print token type
void printTokenType(TokenType type) {
    switch (type) {
        case WHILE:
            printf("While\n");
            break;
        case LPAREN:
            printf("LPAREN\n");
            break;
        case RPAREN:
            printf("RPAREN\n");
            break;
        case LBRACE:
            printf("LBRACE\n");
            break;
        case RBRACE:
            printf("RBRACE\n");
            break;
        case SEMICOLON:
            printf("SEMICOLON\n");
            break;
        case IDENTIFIER:
            printf("IDENTIFIER\n");
            break;
        case GREATER_THAN:
            printf("GREATER_THAN\n");
            break;
        case LESS_THAN:
            printf("LESS_THAN\n");
            break;
        case GREATER_THAN_EQUAL:
            printf("GREATER_THAN_EQUAL\n");
            break;
        case LESS_THAN_EQUAL:
            printf("LESS_THAN_EQUAL\n");
            break;
        case EQUAL:
            printf("EQUAL\n");
            break;
        case NOT_EQUAL:
            printf("NOT_EQUAL\n");
            break;
        case AND:
            printf("AND\n");
            break;
        case OR:
            printf("OR\n");
            break;
        case NOT:
            printf("NOT\n");
            break;
        case PLUS:
            printf("PLUS\n");
            break;
        case MINUS:
            printf("MINUS\n");
            break;
        case MULTIPLY:
            printf("MULTIPLY\n");
            break;
        case DIVIDE:
            printf("DIVIDE\n");
            break;
        case ASSIGN:
            printf("ASSIGN\n");
            break;
        case DIGIT:
            printf("DIGIT\n");
            break;
        case HASH:
            printf("HASH\n");
            break;
        case INT:
            printf("INT\n");
            break;
        case FLOAT:
            printf("FLOAT\n");
            break;
        case CHAR:
            printf("CHAR\n");
            break;
        case MAIN:
            printf("MAIN\n");
            break;
        case SINGLE_QUOTE:
            printf("SINGLE_QUOTE\n");
            break;
        case DOUBLE_QUOTE:
            printf("DOUBLE_QUOTE\n");
            break;
        case NEWLINE:
            printf("NEWLINE\n");
            break;
        case TAB:
            printf("TAB\n");
            break;
        case END_OF_FILE:
            printf("END_OF_FILE\n");
            break;
        default:
            printf("Unknown token\n");
    }
}

int main() {
    FILE *inputFile;
    Token token;

    // Open the input file
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Error: Could not open the file.\n");
        return EXIT_FAILURE;
    }

    // Get tokens and print their types
    do {
        token = getNextToken(inputFile);
        if (token.type != END_OF_FILE) {
            printf("%s -> ", token.lexeme);
            printTokenType(token.type);
        }
    } while (token.type != END_OF_FILE);

    // Close the file
    fclose(inputFile);

    return EXIT_SUCCESS;
}

// problem in identifier count
// problem in reserved word like printf
// problem in tab and newline
// problem in printing ()
// problem in strings