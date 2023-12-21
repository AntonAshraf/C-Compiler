#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ID 1
#define NUM 2
#define WHILE 3
#define TRUE 4
#define FALSE 5
#define RELOP 6
#define ADDOP 7
#define MULOP 8
#define LPAREN 9
#define RPAREN 10
#define END 11
#define LBRACE 12
#define RBRACE 13

int currentToken;
char currentChar;

// Function to get the next character from the input
char *input;
unsigned int inputPos;

void getNextChar() {
    if (inputPos < strlen(input)) {
        currentChar = input[inputPos++];
    } else {
        currentChar = EOF;
    }
}

void term();
void expr();
void factor();
void condition();
void stmt();


// Function to get the next token from the input
int getNextToken() {
    while (isspace(currentChar)) {
        getNextChar();
    }

    if (isalpha(currentChar)) {
        currentToken = ID;
    } else if (isdigit(currentChar)) {
        currentToken = NUM;
    } else {
        switch (currentChar) {
            case '+':
            case '-':
                currentToken = ADDOP;
                break;
            case '*':
            case '/':
                currentToken = MULOP;
                break;
            case '<':
            case '>':
            case '=':
                currentToken = RELOP;
                break;
            case '(':
                currentToken = LPAREN;
                break;
            case ')':
                currentToken = RPAREN;
                break;
            case '{':
                currentToken = LBRACE;
                break;
            case '}':
                currentToken = RBRACE;
                break;
            case EOF:
                currentToken = END;
                break;
            default:
                printf("Unknown character: %c\n", currentChar);
                // exit(EXIT_FAILURE);
        }
    }

    getNextChar();  // Move on to the next character
    return currentToken;
}
// Function to match the current token against an expected token
void match(int expectedToken) {
    if (currentToken == expectedToken) {
        getNextToken();  // Move on to the next token
    } else {
        printf("Unexpected token: %d\n", currentToken);
        // exit(EXIT_FAILURE);
    }
}

// Function to handle errors
void error() {
    printf("Error\n");
    // exit(EXIT_FAILURE);
}
void expr() {
    term();
    int token = getNextToken();
    while (token == '+' || token == '-') {
        match(token);
        term();
        token = getNextToken();
    }
}

void factor() {
    int token = getNextToken();
    if (token == ID || token == NUM) {
        match(token);
    } else if (token == '(') {
        match('(');
        expr();
        match(')');
    } else {
        error();
    }
}

void term() {
    factor();
    int token = getNextToken();
    while (token == '*' || token == '/') {
        match(token);
        factor();
        token = getNextToken();
    }
}



void condition() {
    int token = getNextToken();
    if (token == TRUE || token == FALSE) {
        match(token);
    } else {
        expr();
        token = getNextToken();
        if (token == '<' || token == '>' || token == RELOP) {
            match(token);
            expr();
        } else {
            error();
        }
    }
}

void stmt() {
    int token = getNextToken();
    if (token == WHILE) {
        match(WHILE);
        match('(');
        condition();
        match(')');
        match('{');
        stmt();
        match('}');
    } else {
        error();
    }
}

int main() {
    input = "while(x < 5) { x = x + 1; }";
    inputPos = 0;
    getNextChar();  // Initialize currentChar
    getNextToken();  // Initialize currentToken
    stmt();
    return 0;
}