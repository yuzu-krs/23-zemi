#ifndef BM_SEARCH_H
#define BM_SEARCH_H

#define uchar unsigned char

// 例:テキスト(abcd),テキストの長さ(4),パターン(ed),パターンの長さ(2) 戻り値-1
int bm_search(uchar *text, int text_len, uchar *pattern, int pat_len);

#endif
