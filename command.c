#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
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
    char inputData[1024];
    int i = 0;
    while ((c = fgetc(inputFile)) != EOF) {
        // 大文字を小文字に変換する
        inputData[i] = tolower(c);
        i++;
    }

    i = 0;
    int j = 1;

    while (inputData[i] != '\0') {
        if (i == 0) {
            printf("%d:", j++);
        }
        printf("%c", inputData[i]);
        // 行数を表示する
        if (inputData[i] == '\n') {
            printf("%d:", j++);
        }
        i++;
    }

    fclose(inputFile);

    return 0;
}
