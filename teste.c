#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

// Trie Node
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
};

// Create a new Trie Node
struct TrieNode* createNode() {
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    if (node) {
        node->isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = NULL;
        }
    }
    return node;
}

// Insert a string into the Trie
void insert(struct TrieNode* root, const char* key) {
    if (root == NULL)
        return;

    struct TrieNode* current = root;
    for (int level = 0; key[level] != '\0'; level++) {
        int index = key[level] - 'a';
        if (current->children[index] == NULL) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->isEndOfWord = true;
}

// Search for a string in the Trie
bool search(struct TrieNode* root, const char* key) {
    if (root == NULL)
        return false;

    struct TrieNode* current = root;
    for (int level = 0; key[level] != '\0'; level++) {
        int index = key[level] - 'a';
        if (current->children[index] == NULL) {
            return false;
        }
        current = current->children[index];
    }
    return current != NULL && current->isEndOfWord;
}

// Helper function to check if a node has no children
bool isNodeEmpty(struct TrieNode* node) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            return false;
        }
    }
    return true;
}

// Recursive function to delete a string from the Trie
bool deleteHelper(struct TrieNode* root, const char* key, int level, int len) {
    if (root == NULL)
        return false;

    if (level == len) {
        if (root->isEndOfWord) {
            root->isEndOfWord = false;
            return isNodeEmpty(root);
        }
        return false;
    }

    int index = key[level] - 'a';
    if (deleteHelper(root->children[index], key, level + 1, len)) {
        free(root->children[index]);
        root->children[index] = NULL;
        return !root->isEndOfWord && isNodeEmpty(root);
    }

    return false;
}

// Delete a string from the Trie
void delete(struct TrieNode* root, const char* key) {
    int len = strlen(key);
    if (len > 0) {
        deleteHelper(root, key, 0, len);
    }
}

// Driver program
int main() {
    struct TrieNode* root = createNode();

    // Insert words into the Trie
    insert(root, "apple");
    insert(root, "app");
    insert(root, "banana");
    insert(root, "bat");

    // Search for words in the Trie
    printf("Search results:\n");
    printf("apple: %s\n", search(root, "apple") ? "Found" : "Not Found");
    printf("app: %s\n", search(root, "app") ? "Found" : "Not Found");
    printf("banana: %s\n", search(root, "banana") ? "Found" : "Not Found");
    printf("bat: %s\n", search(root, "bat") ? "Found" : "Not Found");
    printf("ball: %s\n", search(root, "ball") ? "Found" : "Not Found");

    // Delete words from the Trie
    delete(root, "apple");
    delete(root, "banana");

    // Search again after deletion
    printf("\nSearch results after deletion:\n");
    printf("apple: %s\n", search(root, "apple") ? "Found" : "Not Found");
    printf("banana: %s\n", search(root, "banana") ? "Found" : "Not Found");

    // Free memory
    free(root);

    return 0;
}
