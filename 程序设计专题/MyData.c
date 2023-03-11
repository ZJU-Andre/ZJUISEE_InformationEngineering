#include "MyData.h"

#include <stdlib.h>
#include <math.h>
#include <limits.h>

void* minval = 0, * maxval = 0; // 最小值指针，最大值指针
int data_num = 0; // 数据数量
void* data = 0; // 数据
int data_type = DATA_NULL; // 数据类型

int swaped_index = -1; // 目标索引，当前正在变动的数据的序号
int scan_index = -1; // 目标索引，当前正在扫描的数据的序号

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


// 释放并初始化数据
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

// 设置最小最大值的初始值
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

// 刷新最小最大值
void refreshMinMaxi(int val)
{
	*(int*)minval = min(*(int*)minval, val);
	*(int*)maxval = max(*(int*)maxval, val);
}

// 刷新最小最大值
void refreshMinMaxf(float val)
{
	*(float*)minval = min(*(float*)minval, val);
	*(float*)maxval = max(*(float*)maxval, val);
}

// 刷新最小最大值
void refreshMinMaxd(double val)
{
	*(double*)minval = min(*(double*)minval, val);
	*(double*)maxval = max(*(double*)maxval, val);
}