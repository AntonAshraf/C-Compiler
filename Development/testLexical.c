#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/regex.h>

// Token types with mappings
typedef enum {
    WHILE,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    SEMICOLON,
    IDENTIFIER,
    GREATER_THAN,
    LESS_THAN,
    GREATER_THAN_EQUAL,
    LESS_THAN_EQUAL,
    EQUAL,
    NOT_EQUAL,
    AND,
    OR,
    NOT,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    ASSIGN,
    KEYWORD,
    NUMBER,
    STRING_LITERAL,
    CHARACTER_LITERAL,
    COMMENT,
    OPERATOR
} TokenType;

// Structure to hold a token
typedef struct {
    TokenType type;
    char value[100]; // Adjust the size as needed
} Token;

// Function to tokenize the C code
Token* tokenize_c_code(const char* code) {
    regex_t regex;
    Token* tokens = malloc(100 * sizeof(Token)); // Adjust the size as needed
    int token_count = 0;

    // Token regular expressions
    char* patterns[] = {
        "while",
        "\\(",
        "\\)",
        "\\{",
        "\\}",
        ";",
        "[a-zA-Z_][a-zA-Z0-9_]*",
        ">",
        "<",
        ">=",
        "<=",
        "==",
        "!=",
        "&&",
        "\\|\\|",
        "!",
        "\\+",
        "-",
        "\\*",
        "/",
        "=",
        "(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)\\b",
        "\\d+(\\.\\d+)?",
        "\".*?\"",
        "\'(\\\\.|[^\\\\\'])\'",
        "//.*|/\\*[^*]*\\*+(?:[^/*][^*]*\\*+)*/",
        "(\\+\\+|--|\\+=|-=|\\*=|/=|%==|!=|>=|<=|==|&&|\\|\\||\\+=|-=|\\*=|/=|%=|&=|\\|=|\\^=|<<=|>>=|\\+\\+|--|->|\\+|-|\\*|/|%|<|>|=|!|~|\\?|:|\\||\\^|&|<<|>>|,|;|\\.\\.\\.|\\.|->|\\(|\\)|\\[|\\]|\\{|\\})"
    };

    int i;
    for (i = 0; i < sizeof(patterns) / sizeof(patterns[0]); ++i) {
        if (regcomp(&regex, patterns[i], REG_EXTENDED) != 0) {
            fprintf(stderr, "Could not compile regex pattern %d\n", i);
            exit(EXIT_FAILURE);
        }

        regmatch_t match;
        while (regexec(&regex, code, 1, &match, 0) == 0) {
            if (match.rm_so == -1) {
                break;
            }

            Token token;
            token.type = i;
            strncpy(token.value, code + match.rm_so, match.rm_eo - match.rm_so);
            token.value[match.rm_eo - match.rm_so] = '\0';
            tokens[token_count++] = token;

            code += match.rm_eo;
        }
        regfree(&regex);
    }

    Token end_token;
    end_token.type = -1;
    strcpy(end_token.value, "");
    tokens[token_count++] = end_token;

    return tokens;
}

int main() {
    const char* c_code = "while (auto_increment > 5) { auto_increment = auto_increment - 1; if (auto_increment <= 0) { break; } }";
    // const char* c_code = "while (x > 5) { x = x - 1;}";
    
    Token* tokens = tokenize_c_code(c_code);

    printf("Tokenization Result:\n");
    for (int i = 0; tokens[i].type != -1; ++i) {
        printf("Type: %d, Value: %s\n", tokens[i].type, tokens[i].value);
    }

    free(tokens);

    return 0;
}
