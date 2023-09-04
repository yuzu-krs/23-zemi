#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bm_search.h"
#include "char_util.h"
#include "tree.h"
#include "word_processor.h"

int main(int argc, char* argv[]) {
    TreeNode* root = NULL;

    if (argc != 3) {
        fprintf(stderr, "使い方: %s <input.txt> <stopword.txt>\n", argv[0]);
        exit(1);
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        fprintf(stderr, "入力ファイル %s を開く際にエラーが発生しました．\n",
                argv[1]);
        exit(1);
    }

    FILE* stopWordFile = fopen(argv[2], "r");
    if (stopWordFile == NULL) {
        fprintf(stderr, "%s を開く際にエラーが発生しました．\n", argv[2]);
        exit(1);
    }

    // 英単語を定義し，単語帳に登録
    defineWord(&root, inputFile, stopWordFile);
    // printTree関数を使用して，2文探索木の内容を表示します．これにより，中間順トラバーサルしたがってノードが表示され，各単語とその出現行番号が表示される．
    printTree(root);

    // ノード数を計算
    puts("-------------------------------");
    printf("2文探索木の深さは %d です\n\n", calcDepth(root));
    printf("%d 個の単語を出力しました\n\n", countWords(root));

    char searchInput[2048];  // 検索英単語
    while (1) {
        printf("検索単語を入力してください> ");
        fgets(searchInput, sizeof(searchInput), stdin);
        // 入力でのEnter(改行文字)を削除
        int inputLength = strlen(searchInput);
        if (inputLength > 0 && searchInput[inputLength - 1] == '\n') {
            searchInput[inputLength - 1] = '\0';
        }

        // 単語検索と表示
        searchWord(root, searchInput);
    }

    // freeTree関数を使用して，2文探索木のすべてのノードと関連するメモリを解放し，これによりプログラムが終了する際にメモリリークが防止される．
    freeTree(root);

    fclose(inputFile);
    fclose(stopWordFile);
    return 0;
}