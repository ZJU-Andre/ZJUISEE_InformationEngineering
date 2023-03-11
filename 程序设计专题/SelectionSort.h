#pragma once

// 初始化
void initSelection();

// 单步排序
void selectionSortOneStepi();
void selectionSortOneStepf();
void selectionSortOneStepd();

// 写快照
void writeSelectionSnap(FILE* fp);

// 读快照
void readSelectionSnap(FILE* fp);