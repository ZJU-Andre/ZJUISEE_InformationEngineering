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
	// ���ͷ�֮ǰ����Դ
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

	// �жϵ�ǰ״̬��
	//     ���������ֻ��һ����ʱ����a,b�ֱ�Ҫôָ����ʱ����Ҫôָ������������һ������ָʾa�Ƿ�ָ����ʱ����
	//     view_dataҲ�п���ָ����ʱ�������ԣ�����һ������ָʾview_data�Ƿ�ָ����ʱ����
	//     ��ԭʱ����ȡ���ֶΣ���aָ����ʱ������bָ����������֮��Ȼ��
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

	// �洢��ʱ������
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


	// �жϵ�ǰ״̬��
	//     ���������ֻ��һ����ʱ����a,b�ֱ�Ҫôָ����ʱ����Ҫôָ��������
	//     ����dataҲ�п���ָ����ʱ�������ԣ�����һ������ָʾa�Ƿ�ָ����ʱ����
	//     ��ԭʱ����ȡ���ֶΣ���aָ����ʱ������bָ����������֮��Ȼ��
	void* temp_array = merge_b;

	// ��ȡ��ʱ������
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
				scan_index = merge_k;// ���ò���Ԫ�����

				if (a[merge_start1] < a[merge_start2])
				{
					b[merge_k++] = a[merge_start1++];
					swaped_index = merge_start1;// ���ò���Ԫ�����

				}
				else
				{
					b[merge_k++] = a[merge_start2++];
					swaped_index = merge_start2;// ���ò���Ԫ�����
				}
				return;
			}
			else
			{
				if (merge_start1 < merge_end1)
				{
					scan_index = merge_k;// ���ò���Ԫ�����

					b[merge_k++] = a[merge_start1++];

					swaped_index = merge_start1;// ���ò���Ԫ�����
					return;
				}

				if (merge_start2 < merge_end2)
				{
					scan_index = merge_k;// ���ò���Ԫ�����

					b[merge_k++] = a[merge_start2++];

					swaped_index = merge_start2;// ���ò���Ԫ�����
					return;
				}
			}

			scan_index = merge_k;
			swaped_index = -1;

			merge_start += merge_seg + merge_seg; // �в�ѭ������

			// �в�ѭ����ʼ
			merge_low = merge_start;
			merge_mid = min(merge_start + merge_seg, data_num);
			merge_high = min(merge_start + merge_seg + merge_seg, data_num);
			merge_k = merge_low;
			merge_start1 = merge_low, merge_end1 = merge_mid;
			merge_start2 = merge_mid, merge_end2 = merge_high;
		}
		else
		{
			// ����ָ��a b
			int* temp = (int*)merge_a;
			merge_a = merge_b;
			merge_b = temp;

			// �۲�ָ��ʼ��ָ�� ��ʱ��
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

			merge_seg += merge_seg; // ���ѭ������
			merge_start = 0; // �в�ѭ����ʼ��

			// �в�ѭ����ʼ
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
			// ���һ�ֽ���ָ�뵼�� a ָ�� ��ʱ��
			if (merge_i < data_num)
			{
				b[merge_i] = a[merge_i];

				// ���ò���Ԫ�����
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

				// �������
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

			// �������
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
				scan_index = merge_k;// ���ò���Ԫ�����

				if (a[merge_start1] < a[merge_start2])
				{
					b[merge_k++] = a[merge_start1++];
					swaped_index = merge_start1;// ���ò���Ԫ�����

				}
				else
				{
					b[merge_k++] = a[merge_start2++];
					swaped_index = merge_start2;// ���ò���Ԫ�����
				}
				return;
			}
			else
			{
				if (merge_start1 < merge_end1)
				{
					scan_index = merge_k;// ���ò���Ԫ�����

					b[merge_k++] = a[merge_start1++];

					swaped_index = merge_start1;// ���ò���Ԫ�����
					return;
				}

				if (merge_start2 < merge_end2)
				{
					scan_index = merge_k;// ���ò���Ԫ�����

					b[merge_k++] = a[merge_start2++];

					swaped_index = merge_start2;// ���ò���Ԫ�����
					return;
				}
			}

			scan_index = merge_k;
			swaped_index = -1;

			merge_start += merge_seg + merge_seg; // �в�ѭ������

			// �в�ѭ����ʼ
			merge_low = merge_start;
			merge_mid = min(merge_start + merge_seg, data_num);
			merge_high = min(merge_start + merge_seg + merge_seg, data_num);
			merge_k = merge_low;
			merge_start1 = merge_low, merge_end1 = merge_mid;
			merge_start2 = merge_mid, merge_end2 = merge_high;
		}
		else
		{
			// ����ָ��a b
			float* temp = (float*)merge_a;
			merge_a = merge_b;
			merge_b = temp;

			// �۲�ָ��ʼ��ָ�� ��ʱ��
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

			merge_seg += merge_seg; // ���ѭ������
			merge_start = 0; // �в�ѭ����ʼ��

			// �в�ѭ����ʼ
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
			// ���һ�ֽ���ָ�뵼�� a ָ�� ��ʱ��
			if (merge_i < data_num)
			{
				b[merge_i] = a[merge_i];

				// ���ò���Ԫ�����
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

				// �������
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

			// �������
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
				scan_index = merge_k;// ���ò���Ԫ�����

				if (a[merge_start1] < a[merge_start2])
				{
					b[merge_k++] = a[merge_start1++];
					swaped_index = merge_start1;// ���ò���Ԫ�����

				}
				else
				{
					b[merge_k++] = a[merge_start2++];
					swaped_index = merge_start2;// ���ò���Ԫ�����
				}
				return;
			}
			else
			{
				if (merge_start1 < merge_end1)
				{
					scan_index = merge_k;// ���ò���Ԫ�����

					b[merge_k++] = a[merge_start1++];

					swaped_index = merge_start1;// ���ò���Ԫ�����
					return;
				}

				if (merge_start2 < merge_end2)
				{
					scan_index = merge_k;// ���ò���Ԫ�����

					b[merge_k++] = a[merge_start2++];

					swaped_index = merge_start2;// ���ò���Ԫ�����
					return;
				}
			}

			scan_index = merge_k;
			swaped_index = -1;

			merge_start += merge_seg + merge_seg; // �в�ѭ������

			// �в�ѭ����ʼ
			merge_low = merge_start;
			merge_mid = min(merge_start + merge_seg, data_num);
			merge_high = min(merge_start + merge_seg + merge_seg, data_num);
			merge_k = merge_low;
			merge_start1 = merge_low, merge_end1 = merge_mid;
			merge_start2 = merge_mid, merge_end2 = merge_high;
		}
		else
		{
			// ����ָ��a b
			double* temp = (double*)merge_a;
			merge_a = merge_b;
			merge_b = temp;

			// �۲�ָ��ʼ��ָ�� ��ʱ��
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

			merge_seg += merge_seg; // ���ѭ������
			merge_start = 0; // �в�ѭ����ʼ��

			// �в�ѭ����ʼ
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
			// ���һ�ֽ���ָ�뵼�� a ָ�� ��ʱ��
			if (merge_i < data_num)
			{
				b[merge_i] = a[merge_i];

				// ���ò���Ԫ�����
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

				// �������
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

			// �������
			merge_finished = 1;
			state = STATE_FINISHED;
			swaped_index = -1;
			scan_index = -1;
		}
	}
}