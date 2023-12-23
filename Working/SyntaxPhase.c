
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void parseStatement(char *input, int depth);
void parseWhileLoop(char *input, int depth);
void parseExpression(char *input, int depth);
void parseCompoundStatement(char *input, int depth);
void parseStatements(char *input, int depth);
void parseOtherStatement(char *input, int depth);
void parseExpressionStatement(char *input, int depth);
void parsePrintStatement(char *input, int depth);
void parseIdentifiers(char *input, int depth);
void parseNumber(char *input, int depth);
void parseOperator(char *input, int depth);
void parseStringLiteral(char *input, int depth);

// Function to print indentation based on recursion depth
void printIndent(int depth) {
    for (int i = 0; i < depth; ++i) {
        printf("  ");
    }
}

// Function to parse and display the recursive structure of the CFG
void parseCFG(char *input, int depth) {
    parseStatement(input, depth);
}

void parseStatement(char *input, int depth) {
    printIndent(depth);
    printf("Statement\n");

    if (strstr(input, "while") == input) {
        parseWhileLoop(input, depth + 1);
    } else if (strstr(input, "printf") == input) {
        parsePrintStatement(input, depth + 1);
    } else {
        // printf("%s\n", input);
        parseOtherStatement(input, depth + 1);
    }
}

void parseWhileLoop(char *input, int depth) {
    printIndent(depth);
    printf("WhileLoop\n");

    // Assuming 'while' '(' Expression ')' CompoundStatement
    char *start = strstr(input, "(");
    char *end = strstr(input, ")");
    if (start && end) {
        // Extracting the Expression between '(' and ')'
        char expression[100];
        strncpy(expression, start + 1, end - start - 1);
        expression[end - start - 1] = '\0';

        parseExpression(expression, depth + 1);
    }

    // Move to the next part of the WhileLoop
    char *compoundStart = strstr(end, "{");
    if (compoundStart) {
        parseCompoundStatement(compoundStart, depth + 1);
    }
}

void parseExpression(char *input, int depth) {
    printIndent(depth);
    printf("Expression\n");

    char *operators[] = { "<=",">=",">", "<", "==", "!=", "+", "-", "*", "/",NULL}; // List of supported operators

    for (int i = 0; operators[i] != NULL; ++i) {
        char *operator = strstr(input, operators[i]);
        if (operator) {
            // Extracting Identifiers and Number
            size_t operatorLen = strlen(operators[i]);
            char identifiers[50], number[50];
            strncpy(identifiers, input, operator - input);
            identifiers[operator - input] = '\0';
            strcpy(number, operator + operatorLen);
            parseIdentifiers(identifiers, depth + 1);
            parseOperator(operators[i], depth + 1);
            parseNumber(number, depth + 1);
            return; // Stop after parsing the first occurrence of an operator
        }
    }
}

void parseCompoundStatement(char *input, int depth) {
    printIndent(depth);
    printf("CompoundStatement\n");

    // Assuming '{' Statements '}'
    char *statementsStart = strstr(input, "{");
    char *statementsEnd = strstr(input, "}");
    if (statementsStart && statementsEnd) {
        // Extracting Statements between '{' and '}'
        char statements[100];
        strncpy(statements, statementsStart + 1, statementsEnd - statementsStart - 1);
        statements[statementsEnd - statementsStart - 1] = '\0';

        parseStatements(statements, depth + 1);
    }
}

void parseStatements(char *input, int depth) {
    printIndent(depth);
    printf("Statements\n");

    // Assuming Statement Statements | Îµ
    char *statementDelimiter = strstr(input, ";");
    if (statementDelimiter) {
        // Extracting the first Statement
        char statement[100];
        strncpy(statement, input, statementDelimiter - input);
        statement[statementDelimiter - input] = '\0';

        parseStatement(statement, depth + 1);

        // Move to the next part of Statements
        parseStatements(statementDelimiter + 1, depth + 1);
    }
}

void parseOtherStatement(char *input, int depth) {
    printIndent(depth);
    printf("OtherStatement\n");

    // Placeholder: Assuming a simple rule for demonstration
    // You need to replace this with the actual grammar rules for OtherStatement
    // printf("input other: %s\n", input);
    char *identifier = strstr(input, "i");
    if (identifier) {
        parseExpressionStatement(identifier, depth + 1);
    }

    // Add more conditions based on your grammar rules
}

void parseExpressionStatement(char *input, int depth) {
    printIndent(depth);
    printf("ExpressionStatement\n");

    // Assuming it could be any expression followed by a semicolon ';'
    // printf("input: %s\n", input);
    char *semicolon = strstr(input, ";");

    if (semicolon) {
        char *expression = strtok(input, ";");
        // Parse the expression
        parseExpression(expression, depth + 1);

        // Print the semicolon
        printIndent(depth + 1);
        printf(";\n");
    } else {
        // If no semicolon found, consider it as an incomplete expression statement
        printf("Incomplete Expression Statement: Missing Semicolon\n");
    }
}

void parsePrintStatement(char *input, int depth) {
    printIndent(depth);
    printf("PrintStatement\n");

    // Assuming 'printf' '(' StringLiteral ', ' Identifier ')' ';'
    char *stringLiteralStart = strstr(input, "\"");
    char *stringLiteralEnd = strstr(stringLiteralStart + 1, "\"");
    if (stringLiteralStart && stringLiteralEnd) {
        // Extracting StringLiteral between '"' and '"'
        char stringLiteral[100];
        strncpy(stringLiteral, stringLiteralStart + 1, stringLiteralEnd - stringLiteralStart - 1);
        stringLiteral[stringLiteralEnd - stringLiteralStart - 1] = '\0';

        parseStringLiteral(stringLiteral, depth + 1);
    }

    // Assuming ',' Identifier ')' ';'
    char *identifierStart = strstr(stringLiteralEnd + 1, ",");
    char *identifierEnd = strstr(identifierStart + 1, ")");
    if (identifierStart && identifierEnd) {
        // Extracting Identifier between ',' and ')'
        char identifier[50];
        strncpy(identifier, identifierStart + 1, identifierEnd - identifierStart - 1);
        identifier[identifierEnd - identifierStart - 1] = '\0';

        parseIdentifiers(identifier, depth + 1);
    }

    // Print the semicolon
    printIndent(depth + 1);
    printf(";\n");
}

void parseIdentifiers(char *input, int depth) {
    printIndent(depth);
    printf("Identifiers: %s\n", input);
}

void parseNumber(char *input, int depth) {
    printIndent(depth);
    printf("Number: %s\n", input);
}

void parseOperator(char *input, int depth) {
    printIndent(depth);
    printf("Operator: %s\n", input);
}

void parseStringLiteral(char *input, int depth) {
    printIndent(depth);
    printf("StringLiteral: %s\n", input);
}

int main() {
    char input[] = "while (55 != i) {i++;printf(\"%d\\n\", i); i=3 ;}";
    parseCFG(input, 0);

    return 0;
}