#include "BubbleSort.h"

#include <stdlib.h>
#include <string.h>

#include "GlobalVars.h"
#include "MyData.h"

void* origin_data=0;
void* merge_a = 0;
void* merge_b = 0;
int merge_seg;
int merge_i;
int merge_start;
int merge_low;
int merge_mid;
int merge_high;
int merge_k;
int merge_start1, merge_end1;
int merge_start2, merge_end2;

int merge_finished = 0;

void freeTempZone()
{
	if (merge_a && merge_a != origin_data)
	{
		free(merge_a); merge_a = 0;
	}
	if (merge_b && merge_b != origin_data)
	{
		free(merge_b); merge_b = 0;
	}

}

void allocTempZone()
{
	origin_data = data;
	merge_a = data;
	switch (data_type)
	{
	case DATA_INT:
		merge_b = (int*)malloc(data_num * sizeof(int));
		memcpy(merge_b, merge_a, data_num * sizeof(int));
		break;
	case DATA_FLOAT:
		merge_b = (float*)malloc(data_num * sizeof(float));
		memcpy(merge_b, merge_a, data_num * sizeof(float));
		break;
	case DATA_DOUBLE:
		merge_b = (double*)malloc(data_num * sizeof(double));
		memcpy(merge_b, merge_a, data_num * sizeof(double));
		break;
	}
	view_data = merge_b;

}

void initMerge()
{
	// 先释放之前的资源
	freeTempZone();

	allocTempZone();

	merge_seg = 1;
	merge_start = 0;
	merge_i = 0;
	merge_low = merge_start;
	merge_mid = min(merge_start + merge_seg, data_num);
	merge_high = min(merge_start + merge_seg + merge_seg, data_num);
	merge_k = merge_low;
	merge_start1 = merge_low; merge_end1 = merge_mid;
	merge_start2 = merge_mid; merge_end2 = merge_high;

	merge_finished = 0;
	swaped_index = -1;
	scan_index = -1;
}


void writeMergeSnap(FILE* fp)
{
	fwrite(&merge_finished, sizeof(merge_finished), 1, fp);
	if (merge_finished)
		return;

	fwrite(&merge_seg, sizeof(merge_seg), 1, fp);
	fwrite(&merge_start, sizeof(merge_start), 1, fp);
	fwrite(&merge_i, sizeof(merge_i), 1, fp);

	fwrite(&merge_low, sizeof(merge_low), 1, fp);
	fwrite(&merge_mid, sizeof(merge_mid), 1, fp);
	fwrite(&merge_high, sizeof(merge_high), 1, fp);

	fwrite(&merge_k, sizeof(merge_k), 1, fp);

	fwrite(&merge_start1, sizeof(merge_start1), 1, fp);
	fwrite(&merge_end1, sizeof(merge_end1), 1, fp);
	fwrite(&merge_start2, sizeof(merge_start2), 1, fp);
	fwrite(&merge_end2, sizeof(merge_end2), 1, fp);

	// 判断当前状态：
	//     排序过程中只有一个临时区，a,b分别要么指向临时区，要么指向结果区；增加一个变量指示a是否指向临时区。
	//     view_data也有可能指向临时区。所以，增加一个变量指示view_data是否指向临时区。
	//     还原时，读取此字段，若a指向临时区，则将b指向结果区，反之亦然。
	int a_is_temp_array=-1;
	void* temp_array = 0;
	if (merge_a != origin_data)
	{
		a_is_temp_array = 1;
		temp_array = merge_a;
	}
	else
	{
		a_is_temp_array = 0;
		temp_array = merge_b;
	}

	int view_data_is_temp_array = (view_data!=data);

	// 存储临时区数据
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
	fwrite(temp_array, element_size, data_num, fp);

	fwrite(&a_is_temp_array, sizeof(a_is_temp_array), 1, fp);
	fwrite(&view_data_is_temp_array, sizeof(view_data_is_temp_array), 1, fp);

}

void readMergeSnap(FILE* fp)
{
	freeTempZone();
	allocTempZone();

	// 
	fread(&merge_finished, sizeof(merge_finished), 1, fp);
	if (merge_finished)
	{
		merge_finished = 1;
		return;
	}

	fread(&merge_seg, sizeof(merge_seg), 1, fp);
	fread(&merge_start, sizeof(merge_start), 1, fp);
	fread(&merge_i, sizeof(merge_i), 1, fp);

	fread(&merge_low, sizeof(merge_low), 1, fp);
	fread(&merge_mid, sizeof(merge_mid), 1, fp);
	fread(&merge_high, sizeof(merge_high), 1, fp);

	fread(&merge_k, sizeof(merge_k), 1, fp);

	fread(&merge_start1, sizeof(merge_start1), 1, fp);
	fread(&merge_end1, sizeof(merge_end1), 1, fp);
	fread(&merge_start2, sizeof(merge_start2), 1, fp);
	fread(&merge_end2, sizeof(merge_end2), 1, fp);


	// 判断当前状态：
	//     排序过程中只有一个临时区，a,b分别要么指向临时区，要么指向结果区；
	//     但是data也有可能指向临时区。所以，增加一个变量指示a是否指向临时区。
	//     还原时，读取此字段，若a指向临时区，则将b指向结果区，反之亦然。
	void* temp_array = merge_b;

	// 读取临时区数据
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
	fread(temp_array, element_size, data_num, fp);

	int a_is_temp_array = -1;
	int view_data_is_temp_array = -1;
	fread(&a_is_temp_array, sizeof(a_is_temp_array), 1, fp);
	fread(&view_data_is_temp_array, sizeof(view_data_is_temp_array), 1, fp);

	if (a_is_temp_array)
	{
		merge_a = temp_array;
		merge_b = data;
	}
	else
	{
		merge_a = data;
		merge_b = temp_array;
	}

	if (view_data_is_temp_array)
	{
		view_data = temp_array;
	}
	else
	{
		view_data = data;
	}

}

//void merge_sort(int arr[], int len) {
//	int* a = arr;
//	int* b = (int*)malloc(len * sizeof(int));
//	int seg, start;
//	for (seg = 1; seg < len; seg += seg) {
//		for (start = 0; start < len; start += seg + seg) {
//			int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
//			int k = low;
//			int start1 = low, end1 = mid;
//			int start2 = mid, end2 = high;
//			while (start1 < end1 && start2 < end2)
//				b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
//			while (start1 < end1)
//				b[k++] = a[start1++];
//			while (start2 < end2)
//				b[k++] = a[start2++];
//		}
//		int* temp = a;
//		a = b;
//		b = temp;
//	}
//	if (a != arr) {
//		int i;
//		for (i = 0; i < len; i++)
//			b[i] = a[i];
//		b = a;
//	}
//	free(b);
//}

void mergeSortOneStepi()
{
	int* a = (int*)merge_a;
	int* b = (int*)merge_b;

	if (merge_finished)
		return;

	if (merge_seg < data_num)
	{
		if (merge_start < data_num)
		{
			if (merge_start1 < merge_end1 && merge_start2 < merge_end2)
			{
				scan_index = merge_k;// 设置操作元素序号

				if (a[merge_start1] < a[merge_start2])
				{
					b[merge_k++] = a[merge_start1++];
					swaped_index = merge_start1;// 设置操作元素序号

				}
				else
				{
					b[merge_k++] = a[merge_start2++];
					swaped_index = merge_start2;// 设置操作元素序号
				}
				return;
			}
			else
			{
				if (merge_start1 < merge_end1)
				{
					scan_index = merge_k;// 设置操作元素序号

					b[merge_k++] = a[merge_start1++];

					swaped_index = merge_start1;// 设置操作元素序号
					return;
				}

				if (merge_start2 < merge_end2)
				{
					scan_index = merge_k;// 设置操作元素序号

					b[merge_k++] = a[merge_start2++];

					swaped_index = merge_start2;// 设置操作元素序号
					return;
				}
			}

			scan_index = merge_k;
			swaped_index = -1;

			merge_start += merge_seg + merge_seg; // 中层循环增量

			// 中层循环开始
			merge_low = merge_start;
			merge_mid = min(merge_start + merge_seg, data_num);
			merge_high = min(merge_start + merge_seg + merge_seg, data_num);
			merge_k = merge_low;
			merge_start1 = merge_low, merge_end1 = merge_mid;
			merge_start2 = merge_mid, merge_end2 = merge_high;
		}
		else
		{
			// 交换指针a b
			int* temp = (int*)merge_a;
			merge_a = merge_b;
			merge_b = temp;

			// 观察指针始终指向 临时区
			view_data = merge_b;

			switch (data_type)
			{
			case DATA_INT:
				memcpy(merge_b, merge_a, data_num * sizeof(int));
				break;
			case DATA_FLOAT:
				memcpy(merge_b, merge_a, data_num * sizeof(float));
				break;
			case DATA_DOUBLE:
				memcpy(merge_b, merge_a, data_num * sizeof(double));
				break;
			}

			merge_seg += merge_seg; // 外层循环增量
			merge_start = 0; // 中层循环初始化

			// 中层循环开始
			merge_low = merge_start;
			merge_mid = min(merge_start + merge_seg, data_num);
			merge_high = min(merge_start + merge_seg + merge_seg, data_num);
			merge_k = merge_low;
			merge_start1 = merge_low, merge_end1 = merge_mid;
			merge_start2 = merge_mid, merge_end2 = merge_high;

		}
	}
	else
	{
		int* array = (int*)data;
		if (a != array)
		{
			// 最后一轮交换指针导致 a 指向 临时区
			if (merge_i < data_num)
			{
				b[merge_i] = a[merge_i];

				// 设置操作元素序号
				scan_index = merge_i;
				swaped_index = -1;

				merge_i++;
			}
			else
			{
				merge_b = merge_a;

				free(merge_b);
				merge_a = 0;
				merge_b = 0;
				view_data = data;

				// 排序完成
				merge_finished = 1;
				state = STATE_FINISHED;
				swaped_index = -1;
				scan_index = -1;
			}
		}
		else
		{
			free(merge_b);
			merge_a = 0;
			merge_b = 0;
			view_data = data;

			// 排序完成
			merge_finished = 1;
			state = STATE_FINISHED;
			swaped_index = -1;
			scan_index = -1;
		}
	}
}

void mergeSortOneStepf()
{
	float* a = (float*)merge_a;
	float* b = (float*)merge_b;

	if (merge_finished)
		return;

	if (merge_seg < data_num)
	{
		if (merge_start < data_num)
		{
			if (merge_start1 < merge_end1 && merge_start2 < merge_end2)
			{
				scan_index = merge_k;// 设置操作元素序号

				if (a[merge_start1] < a[merge_start2])
				{
					b[merge_k++] = a[merge_start1++];
					swaped_index = merge_start1;// 设置操作元素序号

				}
				else
				{
					b[merge_k++] = a[merge_start2++];
					swaped_index = merge_start2;// 设置操作元素序号
				}
				return;
			}
			else
			{
				if (merge_start1 < merge_end1)
				{
					scan_index = merge_k;// 设置操作元素序号

					b[merge_k++] = a[merge_start1++];

					swaped_index = merge_start1;// 设置操作元素序号
					return;
				}

				if (merge_start2 < merge_end2)
				{
					scan_index = merge_k;// 设置操作元素序号

					b[merge_k++] = a[merge_start2++];

					swaped_index = merge_start2;// 设置操作元素序号
					return;
				}
			}

			scan_index = merge_k;
			swaped_index = -1;

			merge_start += merge_seg + merge_seg; // 中层循环增量

			// 中层循环开始
			merge_low = merge_start;
			merge_mid = min(merge_start + merge_seg, data_num);
			merge_high = min(merge_start + merge_seg + merge_seg, data_num);
			merge_k = merge_low;
			merge_start1 = merge_low, merge_end1 = merge_mid;
			merge_start2 = merge_mid, merge_end2 = merge_high;
		}
		else
		{
			// 交换指针a b
			float* temp = (float*)merge_a;
			merge_a = merge_b;
			merge_b = temp;

			// 观察指针始终指向 临时区
			view_data = merge_b;

			switch (data_type)
			{
			case DATA_INT:
				memcpy(merge_b, merge_a, data_num * sizeof(int));
				break;
			case DATA_FLOAT:
				memcpy(merge_b, merge_a, data_num * sizeof(float));
				break;
			case DATA_DOUBLE:
				memcpy(merge_b, merge_a, data_num * sizeof(double));
				break;
			}

			merge_seg += merge_seg; // 外层循环增量
			merge_start = 0; // 中层循环初始化

			// 中层循环开始
			merge_low = merge_start;
			merge_mid = min(merge_start + merge_seg, data_num);
			merge_high = min(merge_start + merge_seg + merge_seg, data_num);
			merge_k = merge_low;
			merge_start1 = merge_low, merge_end1 = merge_mid;
			merge_start2 = merge_mid, merge_end2 = merge_high;

		}
	}
	else
	{
		float* array = (float*)data;
		if (a != array)
		{
			// 最后一轮交换指针导致 a 指向 临时区
			if (merge_i < data_num)
			{
				b[merge_i] = a[merge_i];

				// 设置操作元素序号
				scan_index = merge_i;
				swaped_index = -1;

				merge_i++;
			}
			else
			{
				merge_b = merge_a;

				free(merge_b);
				merge_a = 0;
				merge_b = 0;
				view_data = data;

				// 排序完成
				merge_finished = 1;
				state = STATE_FINISHED;
				swaped_index = -1;
				scan_index = -1;
			}
		}
		else
		{
			free(merge_b);
			merge_a = 0;
			merge_b = 0;
			view_data = data;

			// 排序完成
			merge_finished = 1;
			state = STATE_FINISHED;
			swaped_index = -1;
			scan_index = -1;
		}
	}
}

void mergeSortOneStepd()
{
	double* a = (double*)merge_a;
	double* b = (double*)merge_b;

	if (merge_finished)
		return;

	if (merge_seg < data_num)
	{
		if (merge_start < data_num)
		{
			if (merge_start1 < merge_end1 && merge_start2 < merge_end2)
			{
				scan_index = merge_k;// 设置操作元素序号

				if (a[merge_start1] < a[merge_start2])
				{
					b[merge_k++] = a[merge_start1++];
					swaped_index = merge_start1;// 设置操作元素序号

				}
				else
				{
					b[merge_k++] = a[merge_start2++];
					swaped_index = merge_start2;// 设置操作元素序号
				}
				return;
			}
			else
			{
				if (merge_start1 < merge_end1)
				{
					scan_index = merge_k;// 设置操作元素序号

					b[merge_k++] = a[merge_start1++];

					swaped_index = merge_start1;// 设置操作元素序号
					return;
				}

				if (merge_start2 < merge_end2)
				{
					scan_index = merge_k;// 设置操作元素序号

					b[merge_k++] = a[merge_start2++];

					swaped_index = merge_start2;// 设置操作元素序号
					return;
				}
			}

			scan_index = merge_k;
			swaped_index = -1;

			merge_start += merge_seg + merge_seg; // 中层循环增量

			// 中层循环开始
			merge_low = merge_start;
			merge_mid = min(merge_start + merge_seg, data_num);
			merge_high = min(merge_start + merge_seg + merge_seg, data_num);
			merge_k = merge_low;
			merge_start1 = merge_low, merge_end1 = merge_mid;
			merge_start2 = merge_mid, merge_end2 = merge_high;
		}
		else
		{
			// 交换指针a b
			double* temp = (double*)merge_a;
			merge_a = merge_b;
			merge_b = temp;

			// 观察指针始终指向 临时区
			view_data = merge_b;

			switch (data_type)
			{
			case DATA_INT:
				memcpy(merge_b, merge_a, data_num * sizeof(int));
				break;
			case DATA_FLOAT:
				memcpy(merge_b, merge_a, data_num * sizeof(float));
				break;
			case DATA_DOUBLE:
				memcpy(merge_b, merge_a, data_num * sizeof(double));
				break;
			}

			merge_seg += merge_seg; // 外层循环增量
			merge_start = 0; // 中层循环初始化

			// 中层循环开始
			merge_low = merge_start;
			merge_mid = min(merge_start + merge_seg, data_num);
			merge_high = min(merge_start + merge_seg + merge_seg, data_num);
			merge_k = merge_low;
			merge_start1 = merge_low, merge_end1 = merge_mid;
			merge_start2 = merge_mid, merge_end2 = merge_high;

		}
	}
	else
	{
		double* array = (double*)data;
		if (a != array)
		{
			// 最后一轮交换指针导致 a 指向 临时区
			if (merge_i < data_num)
			{
				b[merge_i] = a[merge_i];

				// 设置操作元素序号
				scan_index = merge_i;
				swaped_index = -1;

				merge_i++;
			}
			else
			{
				merge_b = merge_a;

				free(merge_b);
				merge_a = 0;
				merge_b = 0;
				view_data = data;

				// 排序完成
				merge_finished = 1;
				state = STATE_FINISHED;
				swaped_index = -1;
				scan_index = -1;
			}
		}
		else
		{
			free(merge_b);
			merge_a = 0;
			merge_b = 0;
			view_data = data;

			// 排序完成
			merge_finished = 1;
			state = STATE_FINISHED;
			swaped_index = -1;
			scan_index = -1;
		}
	}
}