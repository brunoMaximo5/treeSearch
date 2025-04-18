#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

int getHeight(Node* n) {
    return n ? n->height : 0;
}

int getBalance(Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

void updateHeight(Node* n) {
    n->height = 1 + max(getHeight(n->left), getHeight(n->right));
}

// Rotação simples à direita
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Rotação simples à esquerda
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Função de balanceamento
Node* balance(Node* n) {
    updateHeight(n);
    int balanceFactor = getBalance(n);

    // Esquerda pesada
    if (balanceFactor > 1) {
        if (getBalance(n->left) < 0)
            n->left = rotateLeft(n->left);
        return rotateRight(n);
    }

    // Direita pesada
    if (balanceFactor < -1) {
        if (getBalance(n->right) > 0)
            n->right = rotateRight(n->right);
        return rotateLeft(n);
    }

    return n;
}

// Inserção balanceada
Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // não permite duplicados

    return balance(node);
}

// Busca
bool search(Node* root, int key) {
    if (!root) return false;
    if (key == root->key) return true;
    return key < root->key ? search(root->left, key) : search(root->right, key);
}

// Impressão em ordem
void inOrder(Node* root) {
    if (!root) return;
    inOrder(root->left);
    cout << root->key << " ";
    inOrder(root->right);
}

// Liberação da memória
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Teste
int main() {
    Node* root = nullptr;

    int valores[] = {30, 20, 40, 10, 25, 50, 5};
    for (int val : valores) {
        root = insert(root, val);
    }

    cout << "Árvore em ordem: ";
    inOrder(root);
    cout << endl;

    int busca = 25;
    cout << "Buscar " << busca << ": " << (search(root, busca) ? "Encontrado" : "Não encontrado") << endl;

    freeTree(root);
    return 0;
}
