#include <stdio.h>
#include <stdlib.h>

// Define enumeration for different types of AST nodes
typedef enum {
    NUMBER,
    ADDITION,
    MULTIPLICATION
} NodeType;

// Define a structure for AST nodes
typedef struct ASTNode {
    NodeType type;
    int value;
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

// Function to create a new AST node
ASTNode* createNode(NodeType type, int value) {
    ASTNode* newNode = (ASTNode*)malloc(sizeof(ASTNode));
    newNode->type = type;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to generate an abstract syntax tree for the expression (5 + 3) * 7
ASTNode* generateAST() {
    ASTNode* multiplicationNode = createNode(MULTIPLICATION, 0);
    ASTNode* additionNode = createNode(ADDITION, 0);
    ASTNode* fiveNode = createNode(NUMBER, 5);
    ASTNode* threeNode = createNode(NUMBER, 3);
    ASTNode* sevenNode = createNode(NUMBER, 7);

    // Constructing the abstract syntax tree
    multiplicationNode->left = additionNode;
    multiplicationNode->right = sevenNode;
    additionNode->left = fiveNode;
    additionNode->right = threeNode;

    return multiplicationNode;
}

// Function to print the abstract syntax tree in a tree-like format
void printASTRecursive(ASTNode* node, int depth) {
    if (node == NULL) {
        return;
    }

    // Print indentation based on the depth
    for (int i = 0; i < depth; ++i) {
        printf("  ");
    }

    // Print the node's value or type
    if (node->type == NUMBER) {
        printf("%d\n", node->value);
    } else {
        printf("%c\n", node->type == ADDITION ? '+' : '*');
    }

    // Recursively print left and right subtrees with increased depth
    printASTRecursive(node->left, depth + 1);
    printASTRecursive(node->right, depth + 1);
}

// Wrapper function to start printing the abstract syntax tree
void printAST(ASTNode* node) {
    printASTRecursive(node, 0);
}

// Function to free memory allocated for the abstract syntax tree
void freeAST(ASTNode* node) {
    if (node == NULL) {
        return;
    }
    freeAST(node->left);
    freeAST(node->right);
    free(node);
}

int main() {
    // Generate and print a simple abstract syntax tree for the expression
    ASTNode* root = generateAST();
    printf("Generated Abstract Syntax Tree (in tree format):\n");
    printAST(root);

    // Free the allocated memory for the abstract syntax tree
    freeAST(root);

    return 0;
}
