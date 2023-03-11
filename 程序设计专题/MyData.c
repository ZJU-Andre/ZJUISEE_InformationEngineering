#include "MyData.h"

#include <stdlib.h>
#include <math.h>
#include <limits.h>

void* minval = 0, * maxval = 0; // ��Сֵָ�룬���ֵָ��
int data_num = 0; // ��������
void* data = 0; // ����
int data_type = DATA_NULL; // ��������

int swaped_index = -1; // Ŀ����������ǰ���ڱ䶯�����ݵ����
int scan_index = -1; // Ŀ����������ǰ����ɨ������ݵ����

void* view_data=0;

void writeDataSnap(FILE* fp)
{
	fwrite(&data_type, sizeof(data_type), 1, fp);
	fwrite(&data_num, sizeof(data_num), 1, fp);

	int element_size = 0;
	switch (data_type)
	{
	case DATA_INT:
		element_size = sizeof(int);
		break;
	case DATA_FLOAT:
		element_size = sizeof(float);
		break;
	case DATA_DOUBLE:
		element_size = sizeof(double);
		break;
	}

	fwrite(minval, element_size, 1, fp);
	fwrite(maxval, element_size, 1, fp);
	fwrite(data, element_size, data_num, fp);

	fwrite(&swaped_index, sizeof(swaped_index), 1, fp);
	fwrite(&scan_index, sizeof(scan_index), 1, fp);
}

void readDataSnap(FILE* fp)
{
	releaseData();

	fread(&data_type, sizeof(data_type), 1, fp);
	fread(&data_num, sizeof(data_num), 1, fp);

	int element_size = 0;
	switch (data_type)
	{
	case DATA_INT:
		element_size = sizeof(int);
		break;
	case DATA_FLOAT:
		element_size = sizeof(float);
		break;
	case DATA_DOUBLE:
		element_size = sizeof(double);
		break;
	}

	minval = malloc(element_size);
	maxval = malloc(element_size);
	data = malloc(data_num * element_size);

	fread(minval, element_size, 1, fp);
	fread(maxval, element_size, 1, fp);
	fread(data, element_size, data_num, fp);

	fread(&swaped_index, sizeof(swaped_index), 1, fp);
	fread(&scan_index, sizeof(scan_index), 1, fp);
}

void swapi(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

void swapf(float* a, float* b)
{
	float t = *a;
	*a = *b;
	*b = t;
}

void swapd(double* a, double* b)
{
	double t = *a;
	*a = *b;
	*b = t;
}


// �ͷŲ���ʼ������
void releaseData()
{
	free(data);
	data = 0;

	data_num = 0;

	free(minval);
	free(maxval);
	minval = 0;
	maxval = 0;
	data_type = -1;
}

// ������С���ֵ�ĳ�ʼֵ
void setInitMinMax()
{
	switch (data_type)
	{
	case DATA_INT:
		minval = malloc(sizeof(int));
		maxval = malloc(sizeof(int));
		*(int*)minval = INT_MAX;
		*(int*)maxval = INT_MIN;
		break;
	case DATA_FLOAT:
		minval = malloc(sizeof(float));
		maxval = malloc(sizeof(float));
		*(float*)minval = INFINITY;
		*(float*)maxval = -INFINITY;
		break;
	case DATA_DOUBLE:
		minval = malloc(sizeof(double));
		maxval = malloc(sizeof(double));
		*(double*)minval = INFINITY;
		*(double*)maxval = -INFINITY;
		break;
	}
}

// ˢ����С���ֵ
void refreshMinMaxi(int val)
{
	*(int*)minval = min(*(int*)minval, val);
	*(int*)maxval = max(*(int*)maxval, val);
}

// ˢ����С���ֵ
void refreshMinMaxf(float val)
{
	*(float*)minval = min(*(float*)minval, val);
	*(float*)maxval = max(*(float*)maxval, val);
}

// ˢ����С���ֵ
void refreshMinMaxd(double val)
{
	*(double*)minval = min(*(double*)minval, val);
	*(double*)maxval = max(*(double*)maxval, val);
}