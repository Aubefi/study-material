#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode
{
    int data;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

AVLNode *CreateNode(int value)
{
    AVLNode *newNode = malloc(sizeof(AVLNode));

    newNode->data = value;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

int GetMax(int a, int b)
{
    return a > b ? a : b;
}

int GetHeight(AVLNode *node)
{
    return node ? node->height : 0;
}
int CalculateHeight(AVLNode *node)
{
    if (!node) {
        return 0;
    }

    int hLeft = GetHeight(node->left) + 1;
    int hRight = GetHeight(node->right) + 1;

    return GetMax(hLeft, hRight);
}

int GetBalanceFactor(AVLNode *node)
{
    return node ? GetHeight(node->left) - GetHeight(node->right) : 0;
}

AVLNode *LeftRotation(AVLNode *root)
{
    AVLNode *newRoot = root->right;
    AVLNode *newRootLSubtree = newRoot->left;

    newRoot->left = root;
    root->right = newRootLSubtree;

    root->height = CalculateHeight(root);
    newRoot->height = CalculateHeight(newRoot);

    return newRoot;
}

AVLNode *RightRotation(AVLNode *root)
{
    AVLNode *newRoot = root->left;
    AVLNode *newRootRSubtree = newRoot->right;

    newRoot->right = root;
    root->left = newRootRSubtree;

    root->height = CalculateHeight(root);
    newRoot->height = CalculateHeight(newRoot);

    return newRoot;
}

AVLNode *BalanceNode(AVLNode *node)
{
    // Right Rotation
    if (GetBalanceFactor(node) > 1 && GetBalanceFactor(node->left) >= 0) {
        node = RightRotation(node);

    // Left Rotation
    } else if (GetBalanceFactor(node) < -1 && GetBalanceFactor(node->right) <= 0) {
        node = LeftRotation(node);

    // Left-Right Rotation
    } else if (GetBalanceFactor(node) > 1 && GetBalanceFactor(node->left) < 0) {
        node->left = LeftRotation(node->left);
        node = RightRotation(node);

    // Right-Left Rotation
    } else if (GetBalanceFactor(node) < -1 && GetBalanceFactor(node->right) > 0) {
        node->right = RightRotation(node->right);
        node = LeftRotation(node);
    }

    return node;
}

AVLNode *InsertNode(AVLNode *node, int value)
{
    if (!node) {
        node = CreateNode(value);
        return node;
    }

    if (value < node->data) {
        node->left = InsertNode(node->left, value);
    } else if (value > node->data) {
        node->right = InsertNode(node->right, value);
    } else {
        return node;
    }

    node->height = CalculateHeight(node);
    node = BalanceNode(node);

    return node;
}

AVLNode *RemoveNode(AVLNode *node, int value)
{
    if (!node) {
        return NULL;
    }

    if (value < node->data) {
        node->left = RemoveNode(node->left, value);
    } else if (value > node->data) {
        node->right = RemoveNode(node->right, value);
    } else {
        if (!node->left) {
            AVLNode *temp = node->right;
            free(node);
            return temp;
        } else if (!node->right) {
            AVLNode *temp = node->left;
            free(node);
            return temp;
        } else {
            AVLNode *substituteNode = node->left;
            while (substituteNode->right) {
                substituteNode = substituteNode->right;
            }
            int temp = node->data;
            node->data = substituteNode->data;
            substituteNode->data = temp;
            node->left = RemoveNode(node->left, temp);
        }
    }

    if (node) {
        node->height = CalculateHeight(node);
        node = BalanceNode(node);
    }

    return node;
}

void PrintTree(AVLNode *root, int space)
{
    if (root == NULL) {
        return;
    }

    int distance = 5;
    space += distance;

    PrintTree(root->right, space);

    printf("\n");
    for (int i = distance; i < space; i++) {
        printf(" ");
    }

    printf("%d\n", root->data);

    PrintTree(root->left, space);
}

int main()
{
    AVLNode *root = NULL;

    printf("--- AVL TREE ---\n");

    root = InsertNode(root, 10);
    root = InsertNode(root, 20);
    root = InsertNode(root, 30);
    root = InsertNode(root, 40);
    root = InsertNode(root, 50);
    root = InsertNode(root, 25);
    root = InsertNode(root, 60);

    printf("\n------------------------------------------------------\n");
    PrintTree(root, 0);
    printf("\n------------------------------------------------------\n");

    return 0;
}
