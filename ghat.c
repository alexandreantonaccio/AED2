#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 3

typedef struct Node {
    int keys[MAX_KEYS];
    struct Node* children[MAX_KEYS + 1];
    int numKeys;
    struct Node* parent;
} Node;

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->keys[0] = key;
    newNode->numKeys = 1;
    newNode->parent = NULL;
    for (int i = 0; i <= MAX_KEYS; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

Node* splitNode(Node* parent, int index) {
    Node* newNode = createNode(parent->keys[index]);
    Node* rightChild = parent->children[index + 1];
    parent->children[index + 1] = NULL;

    for (int i = index + 1; i < MAX_KEYS; i++) {
        newNode->keys[i - (index + 1)] = parent->keys[i];
        parent->keys[i] = 0;
        newNode->children[i - (index + 1)] = parent->children[i + 1];
        parent->children[i + 1] = NULL;
    }

    newNode->numKeys = MAX_KEYS - (index + 1);
    parent->numKeys = index;

    for (int i = 0; i <= newNode->numKeys; i++) {
        if (newNode->children[i] != NULL) {
            newNode->children[i]->parent = newNode;
        }
    }

    return newNode;
}

Node* insert(Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    Node* currentNode = root;
    Node* parent = NULL;

    while (1) {
        if (currentNode->numKeys < MAX_KEYS) {
            // Insert into a node with available space
            int i = 0;
            while (i < currentNode->numKeys && key > currentNode->keys[i]) {
                i++;
            }

            for (int j = currentNode->numKeys; j > i; j--) {
                currentNode->keys[j] = currentNode->keys[j - 1];
                currentNode->children[j + 1] = currentNode->children[j];
            }

            currentNode->keys[i] = key;
            currentNode->numKeys++;
            break;
        } else {
            // Split and move up
            int i = 0;
            while (i < currentNode->numKeys && key > currentNode->keys[i]) {
                i++;
            }

            if (i == MAX_KEYS) {
                i--;
            }

            if (currentNode->children[i] != NULL) {
                parent = currentNode;
                currentNode = currentNode->children[i];
            } else {
                break;
            }
        }
    }

    if (currentNode->numKeys == MAX_KEYS) {
        // Split the leaf node
        if (parent == NULL) {
            root = splitNode(currentNode, 0);
            parent = root;
        } else {
            int i = 0;
            while (parent->children[i] != currentNode) {
                i++;
            }
            parent->children[i] = splitNode(currentNode, i);
            currentNode = parent->children[i];
        }
    }

    return root;
}

void printTree(Node* root) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < root->numKeys; i++) {
        printf("%d ", root->keys[i]);
    }
    printf("\n");

    for (int i = 0; i <= root->numKeys; i++) {
        printTree(root->children[i]);
    }
}

int main() {
    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);

    printf("Tree contents:\n");
    printTree(root);

    return 0;
}
