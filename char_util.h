#ifndef CHAR_UTIL_H
#define CHAR_UTIL_H

// アポストロフィかどうかを判定する関数
int isApostrophe(int c);

// ピリオドかどうかを判定する関数
int isPeriod(int c);

// 数字かどうかを判定する関数
int isNum(int c);

// アルファベットかどうかを判定する関数
int isAlphabet(int c);

// アルファベットまたは数字かどうかを判定する関数
int isAlphabetNum(int c);

#endif
