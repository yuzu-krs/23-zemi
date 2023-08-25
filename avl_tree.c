#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// L(左が重い),E(バランスがとれている),R(右が重い)
typedef enum Label { L, E, R } Label;

typedef struct AvlNode {
    char* word;            // 英単語を格納する文字列
    int lineNumber[2048];  // 単語が出現する行数を格納する配列
    struct AvlNode* left;
    struct AvlNode* right;
    Label label;  // 木の重さ
} AvlNode;

// 単語の探索と行番号を出力
void searchWord(AvlNode* root, const char* word) {
    if (root == NULL) {
        printf("\"%s\" は存在しません\n\n", word);
        puts("-------------------------------");
        exit(1);
    }
    int cmp = strcmp(word, root->word);
    if (cmp < 0) {
        searchWord(root->left, word);
    } else if (cmp > 0) {
        searchWord(root->right, word);
    } else {
        printf("\"%s\"は以下の行に現れます\n", word);
        int i = 0;
        while (root->lineNumber[i] != 0) {
            printf("    %d", root->lineNumber[i]);
            i++;
        }
        printf("\n");
    }
}
