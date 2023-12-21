#include <stdio.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_INPUT_SIZE 100

// Enum for token types
enum TokenType {
    WHILE, LPAREN, RPAREN, ID, ASSIGN, SEMICOLON, PLUS, NUM, END
};

// Stack to store states and symbols
int stack[MAX_STACK_SIZE];
int top = -1;

// LR parsing table
int parsingTable[8][9] = {
    {4, -1, -1, 5, -1, -1, -1, 0, -1},
    {-1, 6, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, 0, -1},
    {-1, -1, -1, -1, -1, -1, -1, 0, -1},
    {4, -1, -1, 5, -1, -1, -1, 0, -1},
    {-1, -1, 7, -1, 7, -1, -1, -1, -1},
    {4, -1, -1, 5, -1, -1, -1, 0, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1}
};

// Input tokens
int inputTokens[MAX_INPUT_SIZE];
int inputIndex = 0;

// Function to push an element onto the stack
void push(int state) {
    if (top < MAX_STACK_SIZE - 1) {
        stack[++top] = state;
    } else {
        printf("Stack overflow!\n");
    }
}

// Function to pop an element from the stack
int pop() {
    if (top >= 0) {
        return stack[top--];
    } else {
        printf("Stack underflow!\n");
        return -1;
    }
}

// Function to get the next input token
int getNextToken() {
    return inputTokens[inputIndex++];
}

// LR parser function
void parse() {
    int currentState, token;

    // Initial state
    push(0);

    // Main parsing loop
    while (1) {
        currentState = stack[top];
        token = getNextToken();

        if (parsingTable[currentState][token] > 0) {
            // Shift operation
            push(parsingTable[currentState][token]);
        } else if (parsingTable[currentState][token] < 0) {
            // Reduce operation
            int production = -parsingTable[currentState][token];
            for (int i = 0; i < production; i++) {
                pop();
            }
            currentState = stack[top];
            push(parsingTable[currentState][ID]);
        } else {
            // Acceptance
            if (currentState == 7 && token == END) {
                printf("Accepted!\n");
                break;
            } else {
                printf("Rejected!\n");
                break;
            }
        }
    }
}

int main() {
    printf("Enter the input tokens (0 for end): ");
    int token;
    while (1) {
        scanf("%d", &token);
        if (token == 0) {
            break;
        }
        inputTokens[inputIndex++] = token;
    }

    inputTokens[inputIndex++] = END;

    parse();

    return 0;
}