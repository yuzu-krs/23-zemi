#ifndef TREE_H
#define TREE_H

typedef struct TreeNode {
    char* word;            // 英単語を格納する文字列
    int lineNumber[2048];  // 英単語が出現する行番号を格納する配列
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ノードを作成
TreeNode* createNode(const char* word, int lineNumber);

// 二分探索木に英単語を追加する関数
void insertWord(TreeNode** root, const char* word, int lineNumber);

// 二分探索木のノードを開放する関数
void freeTree(TreeNode* root);

// 二分探索木の内容を表示(中間順トラバーサル)
void printTree(TreeNode* root);

// 単語数を数える(ノードの数を数える)
int countWords(TreeNode* root);

// 単語の探索と行番号を出力
void searchWord(TreeNode* root, const char* word);

// 2文探索木から最小値を持つノードを探す
TreeNode* findMin(TreeNode* root);

// 英単語に基づきノードを削除する関数
int deleteNodeByWord(TreeNode** root, const char* word);

// 木の深さを計算する
int calcDepth(TreeNode* root);

#endif