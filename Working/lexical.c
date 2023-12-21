#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
#define MAX_LENGTH 100

// Function to check if a character is a symbol
int isSymbol(char c) {
    return strchr("+-*/=;(){}[]<>", c) != NULL;
}

// Function to check if a string is a keyword
int isKeyword(char* str) {
    char keywords[34][10] = {"auto", "break", "case", "char", "const", "continue", "default",
                             "do", "double", "else", "enum", "extern", "float", "for", "goto",
                             "if", "int", "long", "register", "return", "short", "signed",
                             "sizeof", "static", "struct", "switch", "typedef", "union",
                             "unsigned", "void", "volatile", "while", "#include", "main"};
    for (int i = 0; i < 34; ++i) {
        if (strcmp(keywords[i], str) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to tokenize the input string
void tokenize(const char* input) {
    char token[MAX_LENGTH] = {0};
    int i = 0, j = 0;

    while (input[i] != '\0') {
        if (isalnum(input[i])) {
            token[j++] = input[i];
        } else if (isSymbol(input[i]) || input[i] == ' ' || input[i] == '\n') {
            if (j != 0) {
                token[j] = '\0';
                if (isKeyword(token)) {
                    printf("Keyword: %s\n", token);
                } else if (isdigit(token[0])) {
                    printf("Number: %s\n", token);
                } else {
                    printf("Identifier: %s\n", token);
                }
                j = 0;
            }
            if (isSymbol(input[i])) {
                printf("Symbol: %c\n", input[i]);
            }
        }
        i++;
    }
}

int main() {
    const char* input;
    ifstream f("Untitledk.txt"); //taking file as inputstream
    string str;
    if(f) {
        ostringstream ss;
        ss << f.rdbuf(); // reading data
        str = ss.str();
    }
    input = str.c_str();
    tokenize(input);

    return 0;
}