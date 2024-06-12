#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

// Функция для нахождения минимального элемента в дереве
int findMin(struct Node* root) {
    if (root == NULL) return INT_MAX;
    int minLeft = findMin(root->left);
    int minRight = findMin(root->right);
    return (root->data < minLeft ? (root->data < minRight ? root->data : minRight) : (minLeft < minRight ? minLeft : minRight));
}

// Функция для нахождения максимального элемента в дереве
int findMax(struct Node* root) {
    if (root == NULL) return INT_MIN;
    int maxLeft = findMax(root->left);
    int maxRight = findMax(root->right);
    return (root->data > maxLeft ? (root->data > maxRight ? root->data : maxRight) : (maxLeft > maxRight ? maxLeft : maxRight));
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

    int min = findMin(root);
    int max = findMax(root);

    printf("Разница между максимальным и минимальным элементами в дереве: %d\n", max - min);
    return 0;
}
