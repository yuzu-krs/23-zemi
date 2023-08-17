#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
int isAlphabetNum(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9');
}

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
        // 1単語として取り出す．
        // 大文字を小文字に変換する
        if (isAlphabetNum(c)) {
            inputWord[i] = tolower(c);
            i++;
        } else if (i != 0) {
            inputWord[i] = '\0';
            printf("行番号:%d,inputWord:%s \n", lineNumber, inputWord);
            i = 0;
        }
        // 改行があれば，+1
        if (c == '\n') {
            lineNumber++;
        }
    }

    fclose(inputFile);
    return 0;
}
