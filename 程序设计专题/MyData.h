#pragma once

#include <stdio.h>

// ��������
#define DATA_NULL -1
#define DATA_INT 1
#define DATA_FLOAT 2
#define DATA_DOUBLE 3

extern void* minval, * maxval; // ��Сֵָ�룬���ֵָ��
extern int data_num; // ��������
extern void* data; // ����
extern int data_type; // ��������

extern int swaped_index; // Ŀ����������ǰ���ڱ䶯�����ݵ����
extern int scan_index; // Ŀ����������ǰ����ɨ������ݵ����

extern void *view_data; // �۲�ָ�룬��ָ��ָ����󽫻�������Ļ��

// ��д����
void writeDataSnap(FILE* fp);
void readDataSnap(FILE* fp);

// ��������
void swapi(int* a, int* b);
void swapf(float* a, float* b);
void swapd(double* a, double* b);

// �ͷŲ���ʼ������
void releaseData();

// ������С���ֵ�ĳ�ʼֵ
void setInitMinMax();

// ˢ����С���ֵ
void refreshMinMaxi(int val);
void refreshMinMaxf(float val);
void refreshMinMaxd(double val);