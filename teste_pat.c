#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LENGTH 32

// Structure for a PATRICIA node
struct Node {
    char key[MAX_KEY_LENGTH];
    struct Node* left;
    struct Node* right;
};

// Create a new PATRICIA node
struct Node* createNode(const char* key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    strncpy(node->key, key, MAX_KEY_LENGTH);
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Insert a key into the PATRICIA trie
void insert(struct Node** root, const char* key) {
    if (*root == NULL) {
        *root = createNode(key);
    } else {
        struct Node* node = *root;
        struct Node* parent = NULL;
        int i = 0;
        while (node && key[i] == node->key[i]) {
            parent = node;
            i++;
        }
        
        if (i == strlen(key)) {
            // Key already exists
            return;
        } else if (i == 0) {
            // No common prefix, split the root
            struct Node* newRoot = createNode("");
            if (key[i] == '0') {
                newRoot->left = createNode(key);
                newRoot->right = *root;
            } else {
                newRoot->left = *root;
                newRoot->right = createNode(key);
            }
            *root = newRoot;
        } else {
            // Common prefix, insert recursively
            char* remainingKey = strdup(&key[i]);
            if (key[i] == '0') {
                insert(&parent->left, remainingKey);
            } else {
                insert(&parent->right, remainingKey);
            }
            free(remainingKey);
        }
    }
}

// Search for a key in the PATRICIA trie
struct Node* search(struct Node* root, const char* key) {
    if (root == NULL) {
        return NULL;
    }
    
    struct Node* node = root;
    int i = 0;
    while (node && key[i] == node->key[i]) {
        i++;
    }
    
    if (i == strlen(key)) {
        return node;
    } else if (key[i] == '0') {
        return search(node->left, &key[i]);
    } else {
        return search(node->right, &key[i]);
    }
}

// In-order traversal to print the PATRICIA trie
void printTrie(struct Node* root) {
    if (root) {
        printTrie(root->left);
        printf("%s\n", root->key);
        printTrie(root->right);
    }
}

int main() {
    struct Node* root = NULL;

    insert(&root, "ramone");
    insert(&root, "ramona");
    insert(&root, "carro");
    insert(&root, "barco");

    printf("PATRICIA Trie:\n");
    printTrie(root);

    struct Node* result = search(root, "carro");
    if (result) {
        printf("Search Result: %s\n", result->key);
    } else {
        printf("Key not found.\n");
    }

    return 0;
}

