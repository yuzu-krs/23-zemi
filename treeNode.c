#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 二分探索木のノードを表す構造体
typedef struct TreeNode {
    char* word;            // 英単語を格納する文字列
    int lineNumber[1024];  // 英単語が出現する行番号を格納する配列
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(const char* word, int lineNumber) {
    // 新しいTreNode構造体メモリを割り当てる．malloc関数は，指定されたサイズのメモリを動的に確保し，そのポインタを返します．(TreeNode*)キャストは，割り当てられたメモリをTreeNode*型にキャストしています．
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    // word文字列をコピーして，新しいノードのwordメンバーに設定します．strdup関数は与えられた文字列を新たにメモリ猟奇にコピーして返します．
    newNode->word = strdup(word);
    // 新しいノードのlinuNumber配列の最初の要素に与えられた行番号を設定
    newNode->lineNumber[0] = lineNumber;
    // lineNumber配列要素をすべて0で初期化する．これにより，行番号のデータが格納される配列が初期化される
    for (int i = 1; i < 1024; i++) {
        newNode->lineNumber[i] = 0;
    }

    // 新しいノードの左の子ノードをNULLに初期化します．
    newNode->left = NULL;
    // 新しいノードの右の子ノードをNULLに初期化します．
    newNode->right = NULL;

    // 初期化された新しいノードへのポインタを返します．これにより，ノードが呼び出し元に返され，2文探索木に追加される準備が整います．
    return newNode;
}

// 二分探索木に単語を追加する関数
void insertWord(TreeNode** root, const char* word, int lineNumber) {
    // 2文探索木が空の場合，新しいノードを作成して根ノードとします．これにより，初めて単語が挿入される場合や，再帰的な挿入の基準となる場合に使用されます．
    if (*root == NULL) {
        *root = createNode(word, lineNumber);
        return;
    }

    // strcmp関数を使用して挿入しようとしている単語と現在のノードの単語を比較する．cmpは比較結果を示す整数です．cmpが負の値の場合挿入する単語が現在のノードの単語より小さいことを示します．
    int cmp = strcmp(word, (*root)->word);

    // 小さい時左部分岐にwordを格納
    if (cmp < 0) {
        insertWord(&((*root)->left), word, lineNumber);
        // 大きい場合は右部分木にwordを格納
    } else if (cmp > 0) {
        insertWord(&((*root)->right), word, lineNumber);
    } else {
        // 同じ単語が既に存在する場合
        int i = 0;
        // 行が最後まで
        while ((*root)->lineNumber[i] != 0) {
            // 同じ行があるか動かを確認する
            if ((*root)->lineNumber[i] == lineNumber) {
                // 同じ行番号が既に存在する場合、何もしない
                return;
            }
            i++;
        }
        // 同じ単語が既に存在し，新しい行番号を追加する．
        (*root)->lineNumber[i] = lineNumber;
    }
}

// 二分探索木のノードを再帰的に解放する関数
void freeTree(TreeNode* root) {
    // 与えられたノードrootがNULLである場合，再帰のベースケースに達したことを意味します．その場合，何もせず関数を終了します．これは，再帰呼び出しの停止条件です．
    if (root == NULL) {
        return;
    }
    // rootノードの左の子ノードを再帰的に開放します．これにより，左の部分のすべてのノードが解放されます．
    freeTree(root->left);
    // rootノードの右の子ノードを再帰的に解放します．これにより，右の部分のすべてのノードが解放されます．
    freeTree(root->right);
    // rootノードが保持している英単語のメモリを開放します．これはstrdup関数によって割り当てられたメモリです．
    free(root->word);
    // 最後にrootノード自体のメモリを開放します．これにより，現在のノードがメモリから解放されます．
    free(root);
}

// 二分探索木の内容を表示する関数（中間順トラバーサル）

void printTree(TreeNode* root) {
    // 与えられたノードrootがNULLである場合，再帰のベースケースに達したことを意味します．その場合，何もせずに関数を終了します．これは，再帰呼び出しの停止条件です．
    if (root == NULL) {
        return;
    }

    // rootのノードの左の子ノードを再帰的に表示します．これにより，左の部分木のすべてのノードが表示されます．
    printTree(root->left);

    // 現在のrootノードの単語を表示します．%sふぉ0マット指定しは，文字列を表示するために使用されます．
    printf("Word: %s, Line Numbers:", root->word);
    int i = 0;
    // 現在のrootノードが持つlineNumber配列の要素を走査して出現番号を表示する．行番号の配列は0で終了するため，0に達するまでループを実行します．
    while (root->lineNumber[i] != 0) {
        // 各行番号を表示する．%dフォーマット指定しは，整数を表現するために使用されます．
        printf(" %d", root->lineNumber[i]);
        i++;
    }
    // 現在のノードの出現行数番号の表示が終了したら改行して次のノードに移ります．
    printf("\n");
    // rootノードの右の子ノードを再帰的に表示します．これにより，右の部分木のすべての表示がされる．
    printTree(root->right);
}

int main() {
    // 2文探索木の根ノードへのポインタrootをNULLで初期化します．これは，2分探索木の最初はノードが存在しないことを示します．
    TreeNode* root = NULL;

    // insertWord関数を使用して，英単語とその出現行数番号を持つ新しいノードを2文探索木に追加します．これにより，指定した単語と行番号が適切な位置に挿入されます．
    insertWord(&root, "b", 1);
    insertWord(&root, "c", 1);
    insertWord(&root, "a", 1);
    insertWord(&root, "e", 2);
    insertWord(&root, "d", 3);
    insertWord(&root, "d", 3);
    insertWord(&root, "a", 3);

    // printTree関数を使用して，2文探索木の内容を表示します．これにより，中間順トラバースにしたがってノードが表示され，各単語とその出現行番号が表示されます．
    printTree(root);

    // freeTree関数を使用して，2文探索木のすべてのノードと関連するメモリを解放します．これによりプログラムが終了する際にメモリリークが防がれます．
    freeTree(root);

    return 0;
}