#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Node structure for Patricia tree
struct PatriciaNode {
    char *key;
    struct PatriciaNode *children[ALPHABET_SIZE];
};

// Function to create a new Patricia tree node
struct PatriciaNode *createNode(char *key) {
    struct PatriciaNode *newNode = (struct PatriciaNode *)malloc(sizeof(struct PatriciaNode));
    if (newNode) {
        newNode->key = strdup(key);
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

// Function to insert a key into the Patricia tree
void insert(struct PatriciaNode **root, char *key) {
    if (*root == NULL) {
        *root = createNode(key);
        return;
    }

    struct PatriciaNode *current = *root;
    while (1) {
        int i = 0;
        while (key[i] == current->key[i]) {
            i++;
        }

        if (key[i] == '\0') {
            return; // Key already exists in the tree
        } else if (key[i] == '\0' && current->key[i] != '\0') {
            // Split the current node and insert the new key
            struct PatriciaNode *newNode = createNode(key + i);
            newNode->children[key[i] - 'a'] = current;
            current->key[i] = '\0';
            current = newNode;
            return;
        } else if (key[i] == '\0' || key[i] < current->key[i]) {
            // Insert the new key as a child of the current node
            struct PatriciaNode *newNode = createNode(key + i);
            newNode->children[key[i] - 'a'] = current;
            current->key[i] = '\0';
            current = newNode;
            return;
        } else {
            // Move to the next child
            if (current->children[key[i] - 'a'] == NULL) {
                current->children[key[i] - 'a'] = createNode(key + i);
                return;
            }
            current = current->children[key[i] - 'a'];
        }
    }
}

// Function to find a key in the Patricia tree
struct PatriciaNode *search(struct PatriciaNode *root, char *key) {
    if (root == NULL) {
        return NULL;
    }

    struct PatriciaNode *current = root;
    while (1) {
        int i = 0;
        while (key[i] == current->key[i]) {
            i++;
        }

        if (key[i] == '\0' && current->key[i] == '\0') {
            return current; // Key found
        } else if (key[i] == '\0' || key[i] < current->key[i]) {
            return NULL; // Key not found
        } else {
            // Move to the next child
            if (current->children[key[i] - 'a'] == NULL) {
                return NULL; // Key not found
            }
            current = current->children[key[i] - 'a'];
        }
    }
}

// Function to recursively free the Patricia tree
void freeTree(struct PatriciaNode *root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freeTree(root->children[i]);
    }
    free(root->key);
    free(root);
}

// Function to print the Patricia tree in lexicographical order
void printTree(struct PatriciaNode *root, char *buffer, int depth) {
    if (root == NULL) {
        return;
    }

    if (root->key[0] == '\0') {
        printf("%s\n", buffer);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            buffer[depth] = 'a' + i;
            buffer[depth + 1] = '\0';
            printTree(root->children[i], buffer, depth + 1);
        }
    }
}

// Function to remove a key from the Patricia tree
void removeKey(struct PatriciaNode **root, char *key) {
    // Implement the removal logic here
    // This is a complex operation and requires handling various cases
    // You need to consider scenarios like node deletion, merging, etc.
}

int main() {
    struct PatriciaNode *root = NULL;

    // Insert keys
    insert(&root, "apple");
    insert(&root, "app");
    insert(&root, "bat");
    insert(&root, "batman");

    // Print the tree
    char buffer[100];
    printf("Patricia Tree:\n");
    printTree(root, buffer, 0);

    // Search for a key
    struct PatriciaNode *result = search(root, "app");
    if (result) {
        printf("Found: %s\n", result->key);
    } else {
        printf("Not Found\n");
    }

    // Remove a key (not implemented in this example)
    removeKey(&root, "app");

    // Free the tree
    freeTree(root);

    return 0;
}
