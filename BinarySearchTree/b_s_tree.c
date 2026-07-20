#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int data;
    struct Stack *next;
} Stack;

void Push(Stack **top, int value)
{
    Stack *newNode = malloc(sizeof(Stack));

    if (newNode != NULL) {
        newNode->data = value;
        newNode->next = *top;
        *top = newNode;
    }
}

typedef struct Tree {
    int data;
    struct Tree *left;
    struct Tree *right;
} Tree;

Tree* RemoveNode(Tree *root, int value)
{
    Tree *node = root;
    Tree *parent = NULL;

    while (node && node->data != value) {
        parent = node;
        if (value < node->data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    if (!node) {
        return root;
    }

    if (node->left == NULL || node->right == NULL) {
        Tree *child = (node->left != NULL) ? node->left : node->right;

        if (parent == NULL) {
            free(node);
            return child;
        }

        if (node == parent->left) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        free(node);
    } else {
        Tree *subParent = node;
        Tree *substitute = node->left;

        while (substitute->right) {
            subParent = substitute;
            substitute = substitute->right;
        }

        node->data = substitute->data;

        if (subParent != node) {
            subParent->right = substitute->left;
        } else {
            subParent->left = substitute->left;
        }
        free(substitute);
    }

    return root;
}

int CountLeaves(Tree *node)
{
    if (!node) {
        return 0;
    }

    if (!node->left && !node->right) {
        return 1;
    }

    return CountLeaves(node->left) + CountLeaves(node->right);
}

int GetMax(int a, int b)
{
    return (a > b) ? a : b;
}

int UpdateHeight(Tree *node)
{
    if (!node) {
        return 0;
    }

    int leftHeight = UpdateHeight(node->left);
    int rightHeight = UpdateHeight(node->right);

    return GetMax(leftHeight, rightHeight) + 1;
}
