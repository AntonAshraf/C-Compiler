#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to check if a string is a reserved word
int isReservedWord(char* str) {
    char* reservedWords[] = {"while","auto", "break", "case", "char", "const", "continue", "default",
                             "do", "double", "else", "enum", "extern", "float", "for", "goto",
                             "if", "int", "long", "register", "return", "short", "signed",
                             "sizeof", "static", "struct", "switch", "typedef", "union",
                             "unsigned", "void", "volatile", "while", "#include", "main" };

    int numReservedWords = sizeof(reservedWords) / sizeof(reservedWords[0]);
    for (int i = 0; i < numReservedWords; i++) {
        if (strcmp(str, reservedWords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is a special symbol
int isSpecialSymbol(char c) {
    char specialSymbols[] = "+-*/=<>(){}[]";

    for (int i = 0; specialSymbols[i] != '\0'; i++) {
        if (c == specialSymbols[i]) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a string is a number
int isNumber(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

// Function to check if a string is an identifier
int isIdentifier(char* str) {
    int len = strlen(str);
    if (!isalpha(str[0]) && str[0] != '_') {
        return 0;
    }
    for (int i = 1; i < len; i++) {
        if (!isalnum(str[i]) && str[i] != '_') {
            return 0;
        }
    }
    return 1;
}

// Function to check if a string is a comment
int isComment(char* str) {
    int len = strlen(str);
    if (len >= 2 && strncmp(str, "//", 2) == 0) {
        return 1; // Single-line comment
    } else if (len >= 4 && strncmp(str, "/*", 2) == 0 && strncmp(str + len - 2, "*/", 2) == 0) {
        return 1; // Multi-line comment
    }
    return 0;
}

int main() {
    char input[1000]; // Assuming the maximum input size is 1000 characters
    printf("Enter the code: \n");
    fgets(input, sizeof(input), stdin);

    char* token = strtok(input, " \t\n"); // Tokenizing based on space, tab, newline

    while (token != NULL) {
        if (isReservedWord(token)) {
            printf("%s is a Reserved Word.\n", token);
        } else if (isSpecialSymbol(token[0])) {
            printf("%s is a Special Symbol.\n", token);
        } else if (isNumber(token)) {
            printf("%s is a Number.\n", token);
        } else if (isIdentifier(token)) {
            printf("%s is an Identifier.\n", token);
        } else if (isComment(token)) {
            printf("%s is a Comment.\n", token);
        } else {
            printf("%s is an Unknown Token.\n", token);
        }
        token = strtok(NULL, " \t\n");
    }

    return 0;
}
