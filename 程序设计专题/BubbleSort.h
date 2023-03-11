#pragma once

#include <stdio.h>

// 初始化
void initBubble();

// 排序走一步
void bubbleSortOneStepi();
void bubbleSortOneStepf();
void bubbleSortOneStepd();

// 写快照
void writeBubbleSnap(FILE *fp);

// 读快照
void readBubbleSnap(FILE* fp);