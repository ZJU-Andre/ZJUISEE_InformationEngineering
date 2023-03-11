#include "BubbleSort.h"

#include "GlobalVars.h"
#include "MyData.h"

int selection_i;
int selection_j;
int selection_min;
int selection_finished;

void initSelection()
{
	selection_i = 0;
	selection_j = 1;
	selection_min = 0;
	selection_finished = 0;
	swaped_index = -1;
	scan_index = -1;

	view_data = data;
}


void writeSelectionSnap(FILE* fp)
{
	fwrite(&selection_i, sizeof(selection_i), 1, fp);
	fwrite(&selection_j, sizeof(selection_j), 1, fp);
	fwrite(&selection_min, sizeof(selection_min), 1, fp);
	fwrite(&selection_finished, sizeof(selection_finished), 1, fp);
}

void readSelectionSnap(FILE* fp)
{
	fread(&selection_i, sizeof(selection_i), 1, fp);
	fread(&selection_j, sizeof(selection_j), 1, fp);
	fread(&selection_min, sizeof(selection_min), 1, fp);
	fread(&selection_finished, sizeof(selection_finished), 1, fp);

	view_data = data;
}

//void selection_sort(int arr[], int len) {
//	int i, j, min, temp;
//	for (i = 0; i < len - 1; i++) {
//		min = i;
//		for (j = i + 1; j < len; j++)
//			if (arr[min] > arr[j])
//				min = j;
//		temp = arr[min];
//		arr[min] = arr[i];
//		arr[i] = temp;
//	}
//}

void selectionSortOneStepi()
{
	int* array = (int*)data;

	if (selection_i < data_num - 1)
	{
		if (selection_j < data_num)
		{
			// 设置当前扫描元素序号
			scan_index = selection_j;

			if (array[selection_j] < array[selection_min])
			{
				selection_min = selection_j;
			}
			selection_j++;
		}
		else
		{
			// 设置交换元素序号
			swaped_index = selection_i;

			swapi(&array[selection_min], &array[selection_i]);

			selection_i++;
			selection_j = selection_i + 1;
			selection_min = selection_i;
		}
	}
	else
	{
		// 排序完成
		selection_finished = 1;
		state = STATE_FINISHED;
		swaped_index = -1;
		scan_index = -1;
	}
}

void selectionSortOneStepf()
{
	float* array = (float*)data;

	if (selection_i < data_num - 1)
	{
		if (selection_j < data_num)
		{
			// 设置当前扫描元素序号
			scan_index = selection_j;

			if (array[selection_min] > array[selection_j])
			{
				selection_min = selection_j;
			}
			selection_j++;
		}
		else
		{
			// 设置交换元素序号
			swaped_index = selection_i;


			swapf(&array[selection_min], &array[selection_i]);
			selection_i++;
			selection_j = selection_i + 1;
			selection_min = selection_i;
		}
	}
	else
	{
		// 排序完成
		selection_finished = 1;
		state = STATE_FINISHED;
		swaped_index = -1;
		scan_index = -1;
	}
}

void selectionSortOneStepd()
{
	double* array = (double*)data;

	if (selection_i < data_num - 1)
	{
		if (selection_j < data_num)
		{
			// 设置当前扫描元素序号
			scan_index = selection_j;

			if (array[selection_min] > array[selection_j])
			{
				selection_min = selection_j;
			}
			selection_j++;
		}
		else
		{
			// 设置交换元素序号
			swaped_index = selection_i;


			swapd(&array[selection_min], &array[selection_i]);
			selection_i++;
			selection_j = selection_i + 1;
			selection_min = selection_i;
		}
	}
	else
	{
		// 排序完成
		selection_finished = 1;
		state = STATE_FINISHED;
		swaped_index = -1;
		scan_index = -1;
	}
}
