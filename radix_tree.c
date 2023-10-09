#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct RadixNode {
    struct RadixNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
};

typedef struct RadixNode RadixNode;

RadixNode* createNode() {
    RadixNode* newNode = (RadixNode*)malloc(sizeof(RadixNode));
    if (newNode) {
        newNode->isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

RadixNode* insert(RadixNode* root, const char* key) {
    if (root == NULL) {
        root = createNode();
    }

    if (*key == '\0') {
        root->isEndOfWord = true;
    } else {
        int index = *key - 'a';
        root->children[index] = insert(root->children[index], key + 1);
    }

    return root;
}

bool search(RadixNode* root, const char* key) {
    if (root == NULL) {
        return false;
    }

    if (*key == '\0') {
        return root->isEndOfWord;
    } else {
        int index = *key - 'a';
        return search(root->children[index], key + 1);
    }
}

bool isNodeEmpty(RadixNode* node) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            return false;
        }
    }
    return true;
}

RadixNode* removeKey(RadixNode* root, const char* key) {
    if (root == NULL) {
        return NULL;
    }

    if (*key == '\0') {
        if (root->isEndOfWord) {
            root->isEndOfWord = false;
        }

        if (isNodeEmpty(root)) {
            free(root);
            return NULL;
        }

        return root;
    }

    int index = *key - 'a';
    root->children[index] = removeKey(root->children[index], key + 1);

    if (isNodeEmpty(root) && !root->isEndOfWord) {
        free(root);
        return NULL;
    }

    return root;
}

void printTreeHelper(RadixNode* node, char* buffer, int depth) {
    if (node == NULL) {
        return;
    }

    if (node->isEndOfWord) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            buffer[depth] = i + 'a';
            printTreeHelper(node->children[i], buffer, depth + 1);
        }
    }
}

void printTree(RadixNode* root) {
    char buffer[256]; // Assuming a maximum key length of 255
    printTreeHelper(root, buffer, 0);
}

void freeTree(RadixNode* root) {
    if (root) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            freeTree(root->children[i]);
        }
        free(root);
    }
}

int main() {
    RadixNode* root = NULL;

    // Insert keys
    root = insert(root, "apple");
    root = insert(root, "app");
    root = insert(root, "banana");

    // Search for keys
    printf("Search for 'apple': %s\n", search(root, "apple") ? "Found" : "Not Found");
    printf("Search for 'app': %s\n", search(root, "app") ? "Found" : "Not Found");
    printf("Search for 'banana': %s\n", search(root, "banana") ? "Found" : "Not Found");
    printf("Search for 'cherry': %s\n", search(root, "cherry") ? "Found" : "Not Found");

    // Print the tree
    printf("Radix Tree:\n");
    printTree(root);

    // Remove keys
    root = removeKey(root, "apple");
    root = removeKey(root, "app");

    // Search again after removal
    printf("Search for 'apple' after removal: %s\n", search(root, "apple") ? "Found" : "Not Found");
    printf("Search for 'app' after removal: %s\n", search(root, "app") ? "Found" : "Not Found");

    // Free memory
    freeTree(root);

    return 0;
}
