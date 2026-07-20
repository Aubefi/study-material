#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
    int data;
    struct Tree *left;
    struct Tree *right;
} Tree;

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

int BinarySearch(Tree *node, int value)
{
    while (node) {
        if (value < node->data) {
            node = node->left;
        } else if (value > node->data) {
            node = node->right;
        } else {
            return 1;
        }
    }
    return 0;
}

char *InvertString(char *string)
{
    char *pString = string;
    int count = 0;

    while (*pString) {
        pString++;
        count++;
    }
    pString--;

    char *invertedString = malloc(count + 1);
    if (!invertedString) {
        return NULL;
    }

    char *pInvertedString = invertedString;

    for (int i = 0; i < count; i++) {
        *pInvertedString = *pString;
        pInvertedString++;
        pString--;
    }
    *pInvertedString = '\0';

    return invertedString;
}

void RemoveConsecutiveDuplicates(char *string)
{
    if (!string || !*string) {
        return;
    }

    char *readPtr = string + 1;
    char *writePtr = string;

    while (*readPtr) {
        if (*readPtr != *writePtr) {
            writePtr++;
            *writePtr = *readPtr;
        }
        readPtr++;
    }

    writePtr++;
    *writePtr = '\0';
}

ListNode *InsertAtEnd(ListNode *head, int value)
{
    ListNode *newNode = malloc(sizeof(ListNode));
    if (!newNode) return head;

    newNode->data = value;
    newNode->next = NULL;

    if (!head) {
        return newNode;
    }

    ListNode *current = head;
    while (current->next) {
        current = current->next;
    }

    current->next = newNode;
    return head;
}

int IsSortedRecursively(ListNode *node)
{
    if (!node || !node->next) {
        return 1;
    }

    if (node->data > node->next->data) {
        return 0;
    }

    return IsSortedRecursively(node->next);
}
