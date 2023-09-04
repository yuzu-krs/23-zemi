int isApostrophe(int c) { return (c == '\''); }

int isPeriod(int c) { return (c == '.'); }

int isNum(int c) { return (c >= '0' && c <= '9'); }

int isAlphabet(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int isAlphabetNum(int c) { return isAlphabet(c) || isNum(c); }