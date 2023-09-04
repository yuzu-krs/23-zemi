#include <stdio.h>
#include <stdlib.h>

// 赤黒木の色
typedef enum Color { R, B, Error } Color;

// 赤黒木のノード
typedef struct Node {
    Color color;  // 色
    // キーと値は適切な型を選んでください
    int key;
    int value;
    struct Node* lst;  // 左部分木
    struct Node* rst;  // 右部分木
} Node;

// ２分探索木 v の左回転。回転した木を返す
Node* rotateL(Node* v) {
    Node* u = v->rst;
    Node* t2 = u->lst;
    u->lst = v;
    v->rst = t2;
    return u;
}

// ２分探索木 u の右回転。回転した木を返す
Node* rotateR(Node* u) {
    Node* v = u->lst;
    Node* t2 = v->rst;
    v->rst = u;
    u->lst = t2;
    return v;
}

// ２分探索木 t の二重回転(左回転 -> 右回転)。回転した木を返す
Node* rotateLR(Node* t) {
    t->lst = rotateL(t->lst);
    return rotateR(t);
}

// ２分探索木 t の二重回転(右回転 -> 左回転)。回転した木を返す
Node* rotateRL(Node* t) {
    t->rst = rotateR(t->rst);
    return rotateL(t);
}

Node* insert(Node* t, int key, int x, int* active) {
    if (t == NULL) {
        *active = 1;
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->color = R;
        // Set key and value
        newNode->key = key;
        newNode->value = x;
        newNode->lst = NULL;
        newNode->rst = NULL;
        return newNode;
    }

    int cmp = key.compareTo(t->key);  // Adjust this comparison
    if (cmp < 0) {
        t->lst = insert(t->lst, key, x, active);
        return balance(t, active);
    } else if (cmp > 0) {
        t->rst = insert(t->rst, key, x, active);
        return balance(t, active);
    } else {
        // Update value
        // t->value = x;
        return t;
    }
}

Node* balance(Node* t, int* active) {
    if (!(*active))
        return t;
    else if (!(t->color == B))
        return t;
    else if (isR(t->lst) && isR(t->lst->lst)) {
        t = rotateR(t);
        t->lst->color = B;
    } else if (isR(t->lst) && isR(t->lst->rst)) {
        t = rotateLR(t);
        t->lst->color = B;
    } else if (isR(t->rst) && isR(t->rst->lst)) {
        t = rotateRL(t);
        t->rst->color = B;
    } else if (isR(t->rst) && isR(t->rst->rst)) {
        t = rotateL(t);
        t->rst->color = B;
    } else {
        *active = 0;
    }
    return t;
}