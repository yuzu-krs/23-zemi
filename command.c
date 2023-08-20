#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int isApostrophe(int c) { return (c == '\''); }

int isPeriod(int c) { return (c == '.'); }

int isNum(int c) { return (c >= '0' && c <= '9'); }

int isAlphabet(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int isAlphabetNum(int c) { return isAlphabet(c) || isNum(c); }

int main(int argc, char* argv[]) {
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
        // 数字以外+Apostrophe+数字以外ならば無視
        if (isPeriod(inputWord[i - 1]) && !(isNum(c)) && i > 1) {
            inputWord[i - 1] = '\0';
            printf("行番号:%d,inputWord:%s \n", lineNumber, inputWord);
            i = 0;
        }

        // 1単語として取り出す
        // 大文字を小文字に変換する
        if (isAlphabetNum(c) || isApostrophe(c) || (i > 0 && isPeriod(c))) {
            inputWord[i] = tolower(c);
            i++;
        } else if ((i != 0) && !(isPeriod(inputWord[i - 1]))) {
            inputWord[i] = '\0';
            printf("行番号:%d,inputWord:%s \n", lineNumber, inputWord);
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
        printf("行番号:%d,inputWord:%s \n", lineNumber, inputWord);
    }

    fclose(inputFile);
    return 0;
}
