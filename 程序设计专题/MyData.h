#pragma once

#include <stdio.h>

// 数据类型
#define DATA_NULL -1
#define DATA_INT 1
#define DATA_FLOAT 2
#define DATA_DOUBLE 3

extern void* minval, * maxval; // 最小值指针，最大值指针
extern int data_num; // 数据数量
extern void* data; // 数据
extern int data_type; // 数据类型

extern int swaped_index; // 目标索引，当前正在变动的数据的序号
extern int scan_index; // 目标索引，当前正在扫描的数据的序号

extern void *view_data; // 观察指针，此指针指向对象将绘制在屏幕上

// 读写快照
void writeDataSnap(FILE* fp);
void readDataSnap(FILE* fp);

// 交换内容
void swapi(int* a, int* b);
void swapf(float* a, float* b);
void swapd(double* a, double* b);

// 释放并初始化数据
void releaseData();

// 设置最小最大值的初始值
void setInitMinMax();

// 刷新最小最大值
void refreshMinMaxi(int val);
void refreshMinMaxf(float val);
void refreshMinMaxd(double val);