#pragma once

// 初始化
void initMerge();

// 单步排序
void mergeSortOneStepi();
void mergeSortOneStepf();
void mergeSortOneStepd();

// 写快照
void writeMergeSnap(FILE* fp);

// 读快照
void readMergeSnap(FILE* fp);