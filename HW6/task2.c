#include <stdio.h>
#include <stdlib.h>

// Определение структуры узла дерева
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Функция для создания нового узла
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Функция для вычисления суммы всех элементов в дереве
int sumTree(struct Node* root) {
    if (root == NULL) return 0;
    return root->data + sumTree(root->left) + sumTree(root->right);
}

int main() {
    // Создание дерева
    struct Node* root = newNode(1);
    root->left = newNode(3);
    root->right = newNode(5);
    root->left->left = newNode(7);
    root->left->right = newNode(6);
    root->right->left = newNode(10);
    root->right->right = newNode(15);
    root->right->left->left = newNode(13);
    root->right->left->right = newNode(18);

    printf("Сумма всех элементов в дереве: %d\n", sumTree(root));
    return 0;
}
