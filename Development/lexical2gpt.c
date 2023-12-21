#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Define token types
typedef enum {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    DELIMITER,
    COMMENT,
    WHITESPACE,
    UNKNOWN
} TokenType;

// Define a structure to store tokens
typedef struct {
    TokenType type;
    char value[100]; // Assuming maximum token length is 100 characters
} Token;

// Function to check if a character is an operator
int is_operator(char c) {
    char operators[] = "+-*/%=<>&|!";
    for (int i = 0; operators[i] != '\0'; i++) {
        if (c == operators[i]) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is a delimiter
int is_delimiter(char c) {
    char delimiters[] = "(){}[],;:";
    for (int i = 0; delimiters[i] != '\0'; i++) {
        if (c == delimiters[i]) {
            return 1;
        }
    }
    return 0;
}

// Function to tokenize the input C program
Token* tokenize(const char* input, int* num_tokens) {
    int input_length = strlen(input);
    Token* tokens = (Token*)malloc(input_length * sizeof(Token));
    if (tokens == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    int token_count = 0;
    int i = 0;
    while (i < input_length) {
        // Skip whitespace characters
        if (isspace(input[i])) {
            i++;
            continue;
        }

        // Check for comments
        if (input[i] == '/' && input[i + 1] == '/') {
            tokens[token_count].type = COMMENT;
            while (input[i] != '\n' && i < input_length) {
                i++;
            }
            continue;
        }

        // Check for operators
        if (is_operator(input[i])) {
            tokens[token_count].type = OPERATOR;
            tokens[token_count].value[0] = input[i];
            tokens[token_count].value[1] = '\0';
            token_count++;
            i++;
            continue;
        }

        // Check for delimiters
        if (is_delimiter(input[i])) {
            tokens[token_count].type = DELIMITER;
            tokens[token_count].value[0] = input[i];
            tokens[token_count].value[1] = '\0';
            token_count++;
            i++;
            continue;
        }

        // Check for numbers
        if (isdigit(input[i])) {
            tokens[token_count].type = NUMBER;
            int j = 0;
            while (isdigit(input[i]) && j < 99) {
                tokens[token_count].value[j++] = input[i++];
            }
            tokens[token_count].value[j] = '\0';
            token_count++;
            continue;
        }

        // Check for keywords or identifiers
        if (isalpha(input[i]) || input[i] == '_') {
            int j = 0;
            while ((isalnum(input[i]) || input[i] == '_') && j < 99) {
                tokens[token_count].value[j++] = input[i++];
            }
            tokens[token_count].value[j] = '\0';

            // Check if the token is a keyword
            if (strcmp(tokens[token_count].value, "while") == 0) {
                tokens[token_count].type = KEYWORD;
            } else {
                tokens[token_count].type = IDENTIFIER;
            }
            token_count++;
            continue;
        }

        // Unknown token
        tokens[token_count].type = UNKNOWN;
        tokens[token_count].value[0] = input[i];
        tokens[token_count].value[1] = '\0';
        token_count++;
        i++;
    }

    *num_tokens = token_count;
    return tokens;
}

// Function to print tokens
void print_tokens(Token* tokens, int num_tokens) {
    for (int i = 0; i < num_tokens; i++) {
        switch (tokens[i].type) {
            case KEYWORD:
                printf("Keyword: %s\n", tokens[i].value);
                break;
            case IDENTIFIER:
                printf("Identifier: %s\n", tokens[i].value);
                break;
            case NUMBER:
                printf("Number: %s\n", tokens[i].value);
                break;
            case OPERATOR:
                printf("Operator: %s\n", tokens[i].value);
                break;
            case DELIMITER:
                printf("Delimiter: %s\n", tokens[i].value);
                break;
            case COMMENT:
                printf("Comment\n");
                break;
            case UNKNOWN:
                printf("Unknown: %s\n", tokens[i].value);
                break;
            default:
                break;
        }
    }
}

int main() {
    const char* input = "#include<stdio.h>\n  int main() {\n    int x = 0;\n    while (x < 10) {\n        x = x + 1;\n    }\n    return 0;\n}";

    int num_tokens;
    Token* tokens = tokenize(input, &num_tokens);

    printf("Tokens:\n");
    print_tokens(tokens, num_tokens);

    free(tokens);

    return 0;
}
