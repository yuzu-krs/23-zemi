#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define uchar unsigned char
#define max(a, b) ((a) > (b) ? a : b)
// bm_search(str, strlen(str), bm, strlen(bm)));
/*長さtext_lenの文字列textから長さpat_lenの文字列patternを探索する（BM法)*/
int bm_search(uchar *text, int text_len, uchar *pattern, int pat_len) {
    /*テキストとパターンの不一致が見つかったときにどれだけずらすかを示す表*/
    int skip[256];
    /*変数iは注目しているテキストの位置，変数jは注目しているパターンの位置を表すポインタ*/
    int i, j;

    /*表skipを作成する*/
    for (i = 0; i < 256; i++) skip[i] = pat_len;
    for (i = 0; i < pat_len - 1; i++) skip[pattern[i]] = pat_len - i - 1;

    /*ポインタを初期化する．パターンを後ろから前に向かって比較する
    のでパターンの長さ-1に初期化する*/
    i = pat_len - 1;

    /*テキストの最後尾に行き当たるまで繰り返す*/
    while (i < text_len) {
        /*ポインタjをパターンの最後の文字を指すようにする*/
        j = pat_len - 1;
        /*テキストとパターンが一致する間，繰り返す*/
        while (text[i] == pattern[j]) {
            /*最初の文字まで一致したら，探索は成功*/
            if (j == 0) return i;

            /*ポインタiとjをそれぞれ1文字分戻す*/
            i--;
            j--;
        }
        /*一致しなかったのでパターンをずらす*/
        i = i + max(skip[text[i]], pat_len - j);
    }
    /*結局見つからなかった*/
    return -1;
}
