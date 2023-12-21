#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Token definitions
enum {
    INT, WHILE, IF, ELSE, IDENTIFIER, NUMBER, LPAREN, RPAREN, LBRACE, RBRACE,
    SEMICOLON, ASSIGNMENT, EQUALS, PLUS, MINUS, MULT, DIV, LESSTHAN, GREATERTHAN, END, COMMA
};

// Token structure
struct Token {
    int type;
    char lexeme[50];
};

// Example token stream representing various C statements
struct Token tokens[] = {
    { INT, "int" },
    { IDENTIFIER, "x" },
    { ASSIGNMENT, "=" },
    { NUMBER, "5" },
    { SEMICOLON, ";" },
    { WHILE, "while" },
    { LPAREN, "(" },
    { LESSTHAN, "<" },
    { NUMBER, "10" },
    { RPAREN, ")" },
    { LBRACE, "{" },
    { ASSIGNMENT, "=" },
    { PLUS, "+" },
    { NUMBER, "1" },
    { SEMICOLON, ";" },
    { RBRACE, "}" },
    { IF, "if" },
    { LPAREN, "(" },
    { IDENTIFIER, "x" },
    { GREATERTHAN, ">" },
    { NUMBER, "0" },
    { RPAREN, ")" },
    { LBRACE, "{" },
    { IDENTIFIER, "printf" },
    { LPAREN, "(" },
    { IDENTIFIER, "\"%d\\n\"" },
    { COMMA, "," },
    { IDENTIFIER, "x" },
    { RPAREN, ")" },
    { SEMICOLON, ";" },
    { RBRACE, "}" },
    { ELSE, "else" },
    { LBRACE, "{" },
    { IDENTIFIER, "printf" },
    { LPAREN, "(" },
    { IDENTIFIER, "\"Negative\\n\"" },
    { RPAREN, ")" },
    { SEMICOLON, ";" },
    { RBRACE, "}" },
    { END, "" }
};

int currentToken = 0;

// Function to match the current token type
void match(int expectedToken) {
    if (tokens[currentToken].type == expectedToken) {
        currentToken++;
    } else {
        printf("Syntax error\n");
        // Handle error, maybe exit the program or return to a higher-level parser
    }
}

// Recursive descent parser for the statement
void Statement() {
    switch (tokens[currentToken].type) {
        case INT:
            Declaration();
            break;
        case WHILE:
            WhileLoop();
            break;
        case IF:
            IfStatement();
            break;
        case IDENTIFIER:
            AssignmentOrFunctionCall();
            break;
        default:
            printf("Syntax error\n");
            break;
    }
}

// Recursive descent parser for variable declaration
void Declaration() {
    match(INT);
    match(IDENTIFIER);
    if (tokens[currentToken].type == ASSIGNMENT) {
        match(ASSIGNMENT);
        match(NUMBER); // For simplicity, assume only numbers for initialization
    }
    match(SEMICOLON);
}

// Recursive descent parser for while loop
void WhileLoop() {
    match(WHILE);
    match(LPAREN);
    Expression();
    match(RPAREN);
    Block();
}

// Recursive descent parser for if statement
void IfStatement() {
    match(IF);
    match(LPAREN);
    Expression();
    match(RPAREN);
    Block();

    if (tokens[currentToken].type == ELSE) {
        match(ELSE);
        Block();
    }
}

// Recursive descent parser for assignment or function call
void AssignmentOrFunctionCall() {
    match(IDENTIFIER);
    if (tokens[currentToken].type == ASSIGNMENT) {
        match(ASSIGNMENT);
        Expression();
    } else if (tokens[currentToken].type == LPAREN) {
        match(LPAREN);
        Expression();
        while (tokens[currentToken].type == COMMA) {
            match(COMMA);
            Expression();
        }
        match(RPAREN);
    }
    match(SEMICOLON);
}

// Recursive descent parser for expression
void Expression() {
    // For simplicity, assume basic expressions with numbers and operators
    match(IDENTIFIER); // For simplicity, assume identifiers as expressions
    match(EQUALS);
    match(NUMBER);
    while (tokens[currentToken].type == PLUS || tokens[currentToken].type == MINUS ||
           tokens[currentToken].type == MULT || tokens[currentToken].type == DIV) {
        match(tokens[currentToken].type);
        match(NUMBER);
    }
}

// Recursive descent parser for block
void Block() {
    match(LBRACE);
    while (tokens[currentToken].type != RBRACE && tokens[currentToken].type != END) {
        Statement();
    }
    match(RBRACE);
}

int main() {
    Statement(); // Start parsing with the Statement rule

    // Check if the entire token stream has been processed
    if (tokens[currentToken].type == END) {
        printf("Parsing successful\n");
    } else {
        printf("Syntax error\n");
    }

    return 0;
}
