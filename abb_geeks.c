// C program to delete element in binary tree
#include <stdio.h>
#include <stdlib.h>

/* A binary tree node has key, pointer to left
child and a pointer to right child */
struct Node {
    int key;
    struct Node *left, *right;
};

/* function to create a new node of tree and
return pointer */
struct Node* newNode(int key) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

/* Inorder traversal of a binary tree*/
void inorder(struct Node* temp) {
    if (!temp)
        return;
    inorder(temp->left);
    printf("%d ", temp->key);
    inorder(temp->right);
}

/* function to delete the given deepest node
(d_node) in binary tree */
void deletDeepest(struct Node* root, struct Node* d_node) {
    struct Node* temp;
    struct Node* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    // Do level order traversal until last node
    while (front < rear) {
        temp = queue[front++];
        if (temp == d_node) {
            temp = NULL;
            free(d_node);
            return;
        }
        if (temp->right) {
            if (temp->right == d_node) {
                temp->right = NULL;
                free(d_node);
                return;
            } else {
                queue[rear++] = temp->right;
            }
        }
        if (temp->left) {
            if (temp->left == d_node) {
                temp->left = NULL;
                free(d_node);
                return;
            } else {
                queue[rear++] = temp->left;
            }
        }
    }
}

/* function to delete element in binary tree */
struct Node* deletion(struct Node* root, int key) {
    if (root == NULL)
        return NULL;

    if (root->left == NULL && root->right == NULL) {
        if (root->key == key)
            return NULL;
        else
            return root;
    }

    struct Node* temp;
    struct Node* key_node = NULL;
    struct Node* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    // Do level order traversal to find deepest
    // node(temp) and node to be deleted (key_node)
    while (front < rear) {
        temp = queue[front++];
        if (temp->key == key)
            key_node = temp;
        if (temp->left)
            queue[rear++] = temp->left;
        if (temp->right)
            queue[rear++] = temp->right;
    }

    if (key_node != NULL) {
        int x = temp->key;
        key_node->key = x;
        deletDeepest(root, temp);
    }
    return root;
}

// Driver code
int main() {
    struct Node* root = newNode(10);
    root->left = newNode(11);
    root->left->left = newNode(7);
    root->left->right = newNode(12);
    root->right = newNode(9);
    root->right->left = newNode(15);
    root->right->right = newNode(8);

    printf("Inorder traversal before deletion: ");
    inorder(root);

    int key = 11;
    root = deletion(root, key);

    printf("\nInorder traversal after deletion: ");
    inorder(root);

    return 0;
}
