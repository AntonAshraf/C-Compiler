#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

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
void parseoperator(char *input, int depth);
void parseStringLiteral(char *input, int depth);
void parsenumOrIdentifier(char *input, int depth);


int isWordCharacter(char c) {
    return isalpha(c) || c == '_';
}

void insertCharacters(char *input,char *result) {
    // char result[500] = ""; // Adjust the size according to your needs
    int idx = 0;
    int len = strlen(input);
    int inPrintfString = 0;

    for (int i = 0; i < len; ++i) {
        if (strncmp(input + i, "printf(\"", 7) == 0) {
            inPrintfString = 1;
            strcat(result, "printf(\""); // Copy 'printf(' without modification
            idx += 7;
            i += 6;
        } else if (input[i] == '\"' && strncmp(input + i - 6, "printf(\"", 7) == 0) {
            inPrintfString = 0;
            result[idx++] = '\"'; // Copy closing quote of printf string
        }

        if (inPrintfString) {
            result[idx++] = input[i]; // Copy characters inside printf string
        } else if (isWordCharacter(input[i])) {
            int wordStart = i;
            while (isWordCharacter(input[i])) {
                ++i;
            }
            int wordEnd = i;

            char word[50] = "";
            strncpy(word, input + wordStart, wordEnd - wordStart);
            word[wordEnd - wordStart] = '\0';

            if (strcmp(word, "while") == 0) {
                strcat(result, word); // Add 'while' without 'i'
                idx += strlen(word);
            } else {
                result[idx++] = 'i'; // Insert 'i' before a word
                strcat(result, word);
                idx += strlen(word);
            }
            --i;
        } else if (isdigit(input[i])) {
            result[idx++] = 'n'; // Insert 'n' before a number
            while (isdigit(input[i])) {
                result[idx++] = input[i++];
            }
            --i;
        } else {
            result[idx++] = input[i];
        }
    }
    result[idx] = '\0';

    printf("Modified String: %s\n", result);
}

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
        parseExpressionStatement(input, depth + 1);
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
    //printf("salma: %s\n", input);
    printf("Expression\n");

    char *operators[] = { "<=",">=",">", "<", "==", "!=", "+", "-", "*", "/",NULL}; // List of supported operator1s

    for (int i = 0; operators[i] != NULL; ++i) {
        char *operator1 = strstr(input, operators[i]);
        if (operator1) {
            // Extracting Identifiers and Number
            size_t operatorLen = strlen(operators[i]);
            char left[50], right[50];
          
          //1.if condition hena ya2oly dah number wala la2a
          
            strncpy(left, input, operator1 - input); //llidentifier 
            left[operator1 - input] = '\0';
            
            strcpy(right, operator1 + operatorLen); //llnumber 
           
           //ba send el batal3o
            parsenumOrIdentifier(left, depth + 1);
            // parseIdentifiers(identifiers, depth + 1);
            parseoperator(operators[i], depth + 1);
            parsenumOrIdentifier(right, depth + 1);
            // parseNumber(number, depth + 1);
            return; // Stop after parsing the first occurrence of an operator1
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
    //2.if()if wa7da ah aw wa7da la yab2aa error yab2a el curly brackets msh ma2fola 
}

void parseStatements(char *input, int depth) {
    printIndent(depth);
    printf("Statements\n");
//input:i++;printf(\"%d\\n\", i);ii=z3;

    // Assuming Statement Statements | Îµ
    char *statementDelimiter = strstr(input, ";");
    
    //  printf("salma: %s\n", statementDelimiter+1);
    if (statementDelimiter) {
        // Extracting the first Statement
        char statement[100];
        strncpy(statement, input, statementDelimiter - input);
         printf("salma: %s\n", statement);
        statement[statementDelimiter - input] = '\0';

        parseStatement(statement, depth + 1);

        // Move to the next part of Statements
        parseStatements(statementDelimiter + 1, depth + 1);
    }
}

// // void parseOtherStatement(char *input, int depth) {
// //     printIndent(depth);
// //     printf("OtherStatement\n");

// //     // Placeholder: Assuming a simple rule for demonstration
// //     // You need to replace this with the actual grammar rules for OtherStatement
// //     char *identifier = strstr(input, "i");
// //     if (identifier) {
// //         parseExpressionStatement(identifier, depth + 1);
// //     }

//     // Add more conditions based on your grammar rules
// }

void parseExpressionStatement(char *input, int depth) {
    printIndent(depth);
    printf("ExpressionStatement\n");
    printf("input of ExpressionStatement: %s",input);
    // Assuming Identifiers operator1 Identifiers ';'
    char *identifier1 = strstr(input,"i" );
    char *operator1 = strstr(input, "++");
    // char *identifier2 = strstr(input, "Identifier");
    char *semicolon = strstr(input, ";");

    if (identifier1 && operator1) {
        parseIdentifiers(identifier1, depth + 1);
        parseoperator(operator1, depth + 1);
        // parseIdentifiers(identifier2, depth + 1);
        // Print the semicolon
        printIndent(depth + 1);
        // printf(";\n");
    }

    // Add more conditions based on your grammar rules
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
}

void parsenumOrIdentifier(char *input, int depth) {
    // printf("%s",input);
    const char* tok = " ";
    input = strtok(input,tok);
    char first = input[0];
    char *rest = input + 1;

    if (first == 'i') {
        parseIdentifiers(rest,depth);
    } else if (first == 'n') {
        parseNumber(rest,depth);
    } else {
        printf("The first character is neither 'i' nor 'n'.\n");
    }
}

void parseIdentifiers(char *input, int depth) {
    printIndent(depth);
    printf("Identifiers: %s\n", input);
}

void parseNumber(char *input, int depth) {
    printIndent(depth);
    printf("Number: %s\n", input);
}

void parseoperator(char *input, int depth) {
    printIndent(depth);
    printf("operator: %s\n", input);
}

void parseStringLiteral(char *input, int depth) {
    printIndent(depth);
    printf("StringLiteral: %s\n", input);
}

int main() {
    char input[] = "while (5 >= p) { x= y+ 25;printf(\"hjhjj %s\",x);}";
    
    char result[200];
insertCharacters(input, result);

parseCFG(result, 0);

    return 0;
}