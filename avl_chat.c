#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore AVL
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// Função para obter a altura de um nó
int height(Node* n) {
    if (n == NULL)
        return 0;
    return n->height;
}

// Função para obter o máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para criar um novo nó
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Função para rodar à direita a subárvore enraizada com y
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Realiza a rotação
    x->right = y;
    y->left = T2;

    // Atualiza alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Retorna a nova raiz
    return x;
}

// Função para rodar à esquerda a subárvore enraizada com x
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Realiza a rotação
    y->left = x;
    x->right = T2;

    // Atualiza alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Retorna a nova raiz
    return y;
}

// Função para obter o fator de balanceamento de um nó
int getBalance(Node* n) {
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

// Função para encontrar o menor nó em uma árvore
Node* minValueNode(Node* node) {
    Node* current = node;

    // Loop para encontrar a folha mais à esquerda
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Função para inserir um nó na árvore AVL
Node* insert(Node* node, int key) {
    // Passo 1: Realiza a inserção normal de BST
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    // Passo 2: Atualiza a altura do nó ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // Passo 3: Obtém o fator de balanceamento do nó ancestral para verificar se ele ficou desbalanceado
    int balance = getBalance(node);

    // Se o nó ficou desbalanceado, existem 4 casos

    // Caso Esquerda-Esquerda
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Caso Direita-Direita
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Caso Esquerda-Direita
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso Direita-Esquerda
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Função para remover um nó na árvore AVL
Node* deleteNode(Node* root, int key) {
    // Passo 1: Realiza a remoção normal de BST
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Nó com apenas um filho ou sem filhos
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;

            // Sem filho
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // Um filho
                *root = *temp; // Cópia dos conteúdos do filho não vazio

            free(temp);
        } else {
            // Nó com dois filhos: obtém o sucessor em ordem
            Node* temp = minValueNode(root->right);

            // Copia o conteúdo do sucessor em ordem para este nó
            root->key = temp->key;

            // Remove o sucessor em ordem
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // Se a árvore tinha apenas um nó, então retorne
    if (root == NULL)
        return root;

    // Passo 2: Atualiza a altura do nó atual
    root->height = 1 + max(height(root->left), height(root->right));

    // Passo 3: Obtém o fator de balanceamento do nó atual
    int balance = getBalance(root);

    // Se o nó ficou desbalanceado, existem 4 casos

    // Caso Esquerda-Esquerda
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Caso Esquerda-Direita
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Caso Direita-Direita
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Caso Direita-Esquerda
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Função para buscar uma chave na árvore AVL
Node* search(Node* root, int key) {
    // Caso base: a raiz é nula ou a chave está na raiz
    if (root == NULL || root->key == key)
        return root;

    // A chave é maior que a chave da raiz
    if (root->key < key)
        return search(root->right, key);

    // A chave é menor que a chave da raiz
    return search(root->left, key);
}

// Função para percorrer a árvore em pré-ordem e imprimir as chaves
void preOrder(Node*);
