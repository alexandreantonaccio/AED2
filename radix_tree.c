#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Structure representing a node in the radix tree
struct Node {
    struct Node* children[ALPHABET_SIZE];
    int isEndOfWord;
};

// Function to create a new node
struct Node* createNode() {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode) {
        newNode->isEndOfWord = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

// Function to insert a string into the radix tree
void insert(struct Node* root, const char* key) {
    struct Node* currentNode = root;
    for (int i = 0; i < strlen(key); i++) {
        int index = key[i] - 'a';
        if (!currentNode->children[index]) {
            currentNode->children[index] = createNode();
        }
        currentNode = currentNode->children[index];
    }
    currentNode->isEndOfWord = 1;
}

// Function to search for a string in the radix tree
int search(struct Node* root, const char* key) {
    struct Node* currentNode = root;
    for (int i = 0; i < strlen(key); i++) {
        int index = key[i] - 'a';
        if (!currentNode->children[index]) {
            return 0; // Key not found
        }
        currentNode = currentNode->children[index];
    }
    return currentNode->isEndOfWord; // Key found if isEndOfWord is true
}

int main() {
    struct Node* root = createNode();

    // Insert some strings
    insert(root, "apple");
    insert(root, "app");
    insert(root, "banana");

    // Search for strings
    printf("Search for 'apple': %s\n", search(root, "apple") ? "Found" : "Not found");
    printf("Search for 'app': %s\n", search(root, "app") ? "Found" : "Not found");
    printf("Search for 'banana': %s\n", search(root, "banana") ? "Found" : "Not found");
    printf("Search for 'cherry': %s\n", search(root, "cherry") ? "Found" : "Not found");

    // Clean up the memory (not shown here, but you should free the allocated memory)
    return 0;
}
