#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the types of nodes in the AST
typedef enum {
    WHILE_NODE,
    NUMBER_NODE,
    VARIABLE_NODE,
    ASSIGNMENT_NODE,
    ADDITION_NODE,
    SUBTRACTION_NODE,
    MULTIPLICATION_NODE,
    DIVISION_NODE
} NodeType;

// Structure for the AST nodes
typedef struct ast_node {
    NodeType type;
    struct ast_node *left;
    struct ast_node *right;
    int value; // For NUMBER_NODE
    char* variable_name; // For VARIABLE_NODE
} ASTNode;

// Function to create a new AST node
ASTNode* create_node(NodeType type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (node == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    node->value = 0;
    node->variable_name = NULL;
    return node;
}

// Function to free the memory allocated for the AST
void free_ast(ASTNode* root) {
    if (root != NULL) {
        free_ast(root->left);
        free_ast(root->right);
        free(root);
    }
}

// Function to parse a while loop statement and build the AST
ASTNode* parse_while_loop() {
    // Assuming input is tokenized and parsed accordingly
    // Parsing while loop syntax (while (condition) { body })
    // Example: while (x < 10) { x = x + 1; }
    
    ASTNode* while_node = create_node(WHILE_NODE);

    // Mock conditions and body for demonstration purposes
    ASTNode* condition = create_node(VARIABLE_NODE);
    condition->variable_name = strdup("x");

    ASTNode* body = create_node(ASSIGNMENT_NODE);
    body->left = create_node(VARIABLE_NODE);
    body->left->variable_name = strdup("x");
    body->right = create_node(ADDITION_NODE);
    body->right->left = create_node(VARIABLE_NODE);
    body->right->left->variable_name = strdup("x");
    body->right->right = create_node(NUMBER_NODE);
    body->right->right->value = 1;

    while_node->left = condition;
    while_node->right = body;

    return while_node;
}

// Function to print the AST nodes (inorder traversal)
void print_ast(ASTNode* root) {
    if (root != NULL) {
        print_ast(root->left);

        switch (root->type) {
            case WHILE_NODE:
                printf("While loop\n");
                break;
            case NUMBER_NODE:
                printf("Number: %d\n", root->value);
                break;
            case VARIABLE_NODE:
                printf("Variable: %s\n", root->variable_name);
                break;
            case ASSIGNMENT_NODE:
                printf("Assignment\n");
                break;
            case ADDITION_NODE:
                printf("Addition\n");
                break;
            default:
                break;
        }

        print_ast(root->right);
    }
}

int main() {
    ASTNode* ast = parse_while_loop();

    printf("Abstract Syntax Tree:\n");
    print_ast(ast);

    // Free the allocated memory for the AST
    free_ast(ast);

    return 0;
}
