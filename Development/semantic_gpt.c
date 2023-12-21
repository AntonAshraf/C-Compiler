#include <stdio.h>
#include <stdlib.h>

// Define a structure for a simple semantic tree node
typedef struct SemanticNode {
    char* value;
    struct SemanticNode* left;
    struct SemanticNode* right;
} SemanticNode;

// Function to create a new semantic tree node
SemanticNode* createSemanticNode(char* value) {
    SemanticNode* newNode = (SemanticNode*)malloc(sizeof(SemanticNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to generate a simple semantic tree for an arithmetic expression: (a + b) * c
SemanticNode* generateSemanticTree() {
    // Creating nodes for variables and operators
    SemanticNode* rootNode = createSemanticNode("*");
    SemanticNode* addNode = createSemanticNode("+");
    SemanticNode* aNode = createSemanticNode("a");
    SemanticNode* bNode = createSemanticNode("b");
    SemanticNode* cNode = createSemanticNode("c");

    // Constructing the semantic tree
    rootNode->left = addNode;
    rootNode->right = cNode;
    addNode->left = aNode;
    addNode->right = bNode;

    return rootNode;
}

// Function to traverse and print the generated semantic tree (inorder traversal)
void printSemanticTree(SemanticNode* node) {
    if (node == NULL) {
        return;
    }
    printSemanticTree(node->left);
    printf("%s ", node->value);
    printSemanticTree(node->right);
}

// Function to free memory allocated for the semantic tree
void freeSemanticTree(SemanticNode* node) {
    if (node == NULL) {
        return;
    }
    freeSemanticTree(node->left);
    freeSemanticTree(node->right);
    free(node);
}

int main() {
    // Generate and print a simple semantic tree for an arithmetic expression
    SemanticNode* root = generateSemanticTree();
    printf("Generated Semantic Tree: ");
    printSemanticTree(root);
    printf("\n");

    // Free the allocated memory for the semantic tree
    freeSemanticTree(root);

    return 0;
}
