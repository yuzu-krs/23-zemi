#ifndef WORD_PROCESSOR_H
#define WORD_PROCESSOR_H

#include <stdio.h>

#include "tree.h"

void defineWord(TreeNode** root, FILE* inputFile, FILE* stopWordFile);

#endif
