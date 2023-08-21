#include <ctype.h>
#include <stdbool.h>
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
    // TreeNode構造体のメモリを確保する
    // sizeof(TreeNode)はTreeNode構造体のメモリサイズをバイト単位で返す．
    // malloc関数は，指定されたバイト数のメモリを確保してその先頭アドレスを
    // newNodeポインタに格納する．
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    // wordメンバを設定する
    // strdup関数は，引数として渡された文字列を複製して新しいメモリ領域に
    // 格納し，そのアドレスを返す．
    // この複製された文字列が新しいノードのwordメンバとして設定される．
    newNode->word = strdup(word);
    // lineNumber配列を初期化する．
    // lineNumber配列の先頭要素に最初の出現番号を格納する．
    newNode->lineNumber[0] = lineNumber;
    // 残りの要素には0を設定して初期化する．
    for (int i = 1; i < 1024; i++) {
        newNode->lineNumber[i] = 0;
    }

    // 子ノードをNULLに初期化し，leftおよびrightポインタをNULLに設定して，このノードが葉ノードとして開始されることを示す．
    newNode->left = NULL;
    newNode->right = NULL;

    // 初期化された新しいノードへのポインタを返し,新しいノードが正常に初期化されたのでそのポインタを呼び出し元に返す．
    return newNode;
}

// 二分探索木に単語を追加する関数
void insertWord(TreeNode** root, const char* word, int lineNumber) {
    // 2文探索木が空かどうかを確認する．
    if (*root == NULL) {
        // もし木が空であれば，新しいノードを作成し，そのノードを2文探索木のルートに設定し，最初のノードを作成する．
        *root = createNode(word, lineNumber);
        return;
    }

    // 新しい単語と現在のノードを比較する．
    // strcmp関数を使用し，新しい単語と現在のノードの単語を辞書順で比較する．
    int cmp = strcmp(word, (*root)->word);

    if (cmp < 0) {
        // もし新しい単語が現在のノードの単語よりも小さい場合，左のサブツリーを再帰的に追加する．
        insertWord(&((*root)->left), word, lineNumber);

    } else if (cmp > 0) {
        // もし新しい単語が現在のノードの単語よりも大きい場合，右のサブツリーに再帰的に追加する．
        insertWord(&((*root)->right), word, lineNumber);
    } else {
        // 新しい単語が既に存在する場合の処理
        int i = 0;
        // 同じ単語が既に存在する場合は，その行番号をチェックする．
        while ((*root)->lineNumber[i] != 0) {
            // 既に同じ行番号が存在する場合，何もせずに関数を終了
            if ((*root)->lineNumber[i] == lineNumber) {
                return;
            }
            i++;
        }
        // 同じ行番号が存在しない場合，新しい行番号を行番号配列に追加する．
        (*root)->lineNumber[i] = lineNumber;
    }
}

// 二分探索木のノードを再帰的に解放する関数
void freeTree(TreeNode* root) {
    // 現在のノードがNULLであるかどうか？
    // もし，現在のノードがNULLであれば，これ以上開放すべきノードがないため，関数終了．
    if (root == NULL) {
        return;
    }
    // rootノードの左の子ノードを再帰的に解放します．これにより，左の部分のすべてのノードが解放する．
    freeTree(root->left);
    // rootノードの右の子ノードを再帰的に解放します．これにより，右の部分のすべてのノードが解放する．
    freeTree(root->right);
    // 現在のノードwordメンバに割り当てられた，単語を格納するために割り当てられたメモリが解放される．
    free(root->word);
    // 最後にrootノード自体のメモリを解放します．これにより，現在のノードがメモリから解放されます．
    free(root);
}

// 二分探索木の内容を表示する関数（中間順トラバーサル）

void printTree(TreeNode* root) {
    // 現在のノードがNULLであるかどうかを確認
    // もし現在のノードがNULLならばこれ以上表示するノードは存在しないため，関数を終了する．
    if (root == NULL) {
        return;
    }

    // rootのノードの左の子ノードを再帰的に表示し,これにより，左の部分木のすべてのノードが表示される．
    printTree(root->left);

    // 現在のノードの情報を表示する．
    // 現在のノードの単語とそれに対応する行番号を表示します．
    printf("%-20s :", root->word);
    int i = 0;
    // 現在のrootノードが持つlineNumber配列の要素を走査して出現番号を表示する．行番号の配列は0で終了するため，0に達するまでループを実行する．
    while (root->lineNumber[i] != 0) {
        printf(" %2d ", root->lineNumber[i]);
        i++;
    }
    // 現在のノードの出現行数番号の表示が終了したら改行して次のノードに移ります．
    printf("\n");
    // rootノードの右の子ノードを再帰的に表示します．これにより，右の部分木のすべての表示がされる．
    printTree(root->right);
}

int isApostrophe(int c) { return (c == '\''); }

int isPeriod(int c) { return (c == '.'); }

int isNum(int c) { return (c >= '0' && c <= '9'); }

int isAlphabet(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int isAlphabetNum(int c) { return isAlphabet(c) || isNum(c); }

int main(int argc, char* argv[]) {
    TreeNode* root = NULL;
    char inputWord[1024];

    if (argc != 2) {
        fprintf(stderr, "使い方: %s <入力ファイル名> \n", argv[0]);
        exit(1);
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        fprintf(stderr, "入力ファイル %s を開く際にエラーが発生しました．\n",
                argv[1]);
        exit(1);
    }

    int c;
    int i = 0;
    int lineNumber = 1;

    while ((c = fgetc(inputFile)) != EOF) {
        // 数字以外+period+数字以外ならば無視
        if (isPeriod(inputWord[i - 1]) && !(isNum(c)) && i > 1) {
            inputWord[i - 1] = '\0';
            insertWord(&root, inputWord, lineNumber);
            i = 0;
        }

        // アルファベット+apostrophe+アルファベット
        if (isApostrophe(inputWord[i - 1]) && !(isAlphabet(c)) && i > 1) {
            inputWord[i - 1] = '\0';

            insertWord(&root, inputWord, lineNumber);
            i = 0;
        }

        // 1単語として取り出す
        // 大文字を小文字に変換する
        if (isAlphabetNum(c) || isNum(c) || (i > 0 && isPeriod(c)) ||
            (i > 0 && isApostrophe(c))) {
            inputWord[i] = tolower(c);
            i++;
        } else if ((i != 0) && !(isPeriod(inputWord[i - 1])) &&
                   !(isApostrophe(inputWord[i - 1]))) {
            inputWord[i] = '\0';

            insertWord(&root, inputWord, lineNumber);
            i = 0;

        } else {
            i = 0;
        }
        if (c == '\n') {
            i = 0;
            lineNumber++;
        }
    }

    // ファイルの末尾に単語があった場合
    if (i != 0) {
        inputWord[i] = '\0';
        insertWord(&root, inputWord, lineNumber);
    }

    // printTree関数を使用して，2文探索木の内容を表示します．これにより，中間順トラバーサルしたがってノードが表示され，各単語とその出現行番号が表示される．
    printTree(root);

    // freeTree関数を使用して，2文探索木のすべてのノードと関連するメモリを解放し，これによりプログラムが終了する際にメモリリークが防止される．
    freeTree(root);

    fclose(inputFile);
    return 0;
}
