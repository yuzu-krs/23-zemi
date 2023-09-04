#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bm_search.h"
#include "char_util.h"
#include "tree.h"

void defineWord(TreeNode** root, FILE* inputFile, FILE* stopWordFile) {
    char inputWord[1024];
    char stopWord[1024];
    int c;
    int i = 0;
    int lineNumber = 1;
    while ((c = fgetc(inputFile)) != EOF) {
        // 数字以外+period+数字以外ならば無視
        if (isPeriod(inputWord[i - 1]) && !(isNum(c)) && i > 1) {
            inputWord[i - 1] = '\0';
            insertWord(root, inputWord, lineNumber);
            i = 0;
        }

        // アルファベット+apostrophe+アルファベット
        if (isApostrophe(inputWord[i - 1]) && !(isAlphabet(c)) && i > 1) {
            inputWord[i - 1] = '\0';

            insertWord(root, inputWord, lineNumber);
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

            insertWord(root, inputWord, lineNumber);
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
        insertWord(root, inputWord, lineNumber);
    }

    i = 0;
    while ((c = fgetc(stopWordFile)) != EOF) {
        if (c == '\n') {
            stopWord[i] = '\0';

            deleteNodeByWord(root, stopWord);
            i = 0;
        } else {
            stopWord[i] = c;
            i++;
        }
    }

    if (i != 0) {
        stopWord[i] = '\0';
        deleteNodeByWord(root, stopWord);
    }
}