#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_INPUT_SIZE 100

// Define the grammar rules
typedef struct {
    char left[10];
    char right[10];
} Rule;

Rule rules[] = {
    {"E", "E+T"},
    {"E", "T"},
    {"T", "T*F"},
    {"T", "F"},
    {"F", "(E)"},
    {"F", "id"}
};

// Define the stack structure
typedef struct {
    char stack[MAX_STACK_SIZE];
    int top;
} Stack;

// Function to initialize the stack
void initStack(Stack *s) {
    s->top = -1;
}

// Function to push a symbol onto the stack
void push(Stack *s, char symbol) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->stack[++s->top] = symbol;
    } else {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

// Function to pop a symbol from the stack
char pop(Stack *s) {
    if (s->top >= 0) {
        return s->stack[s->top--];
    } else {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
}

// Function to perform shift operation
void shift(Stack *s, char *input, int *inputIndex) {
    push(s, input[(*inputIndex)++]);
}

// Function to perform reduce operation
void reduce(Stack *s, Rule *rule) {
    int len = strlen(rule->right);
    for (int i = 0; i < len; i++) {
        pop(s);
    }
    push(s, rule->left[0]);
}

// Function to perform shift-reduce parsing
void parse(Stack *s, char *input) {
    int inputIndex = 0;

    while (1) {
        printf("Stack: %s, Input: %s\n", s->stack, input + inputIndex);

        // Check for reduce
        for (unsigned int i = 0; i < sizeof(rules) / sizeof(rules[0]); i++) {
            if (strncmp(s->stack + s->top - strlen(rules[i].right) + 1, rules[i].right, strlen(rules[i].right)) == 0) {
                reduce(s, &rules[i]);
                break;
            }
        }

        // Check for shift
        if (input[inputIndex] != '\0') {
            shift(s, input, &inputIndex);
        } else {
            // If the input is empty, break
            break;
        }
    }

    printf("Parsing completed\n");
}

int main() {
    Stack stack;
    initStack(&stack);

    char input[MAX_INPUT_SIZE];

    printf("Enter the input string: ");
    scanf("%[^\n]s", input);

    // Add a '$' symbol to the end of the input string
    strcat(input, "$");

    parse(&stack, input);

    return 0;
}