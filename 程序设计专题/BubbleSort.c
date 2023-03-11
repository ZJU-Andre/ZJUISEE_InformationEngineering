#include "BubbleSort.h"

#include "GlobalVars.h"
#include "MyData.h"

int bubble_beg;
int bubble_end;
int bubble_finished;

void initBubble()
{
	bubble_beg = 0;
	bubble_end = data_num;
	bubble_finished = 0;
	swaped_index = -1;
	scan_index = -1;

	view_data = data;
}


void writeBubbleSnap(FILE* fp)
{
	fwrite(&bubble_beg, sizeof(bubble_beg), 1, fp);
	fwrite(&bubble_end, sizeof(bubble_end), 1, fp);
	fwrite(&bubble_finished, sizeof(bubble_finished), 1, fp);
}

void readBubbleSnap(FILE* fp)
{
	fread(&bubble_beg, sizeof(bubble_beg), 1, fp);
	fread(&bubble_end, sizeof(bubble_end), 1, fp);
	fread(&bubble_finished, sizeof(bubble_finished), 1, fp);

	view_data = data;
}


//for (int end=data_num;end>=0;--end)
//{
//	for (int beg = 0; beg < end - 1; ++beg)
//	{
//		if (array[beg] > array[beg + 1])
//		{
//			swap(&array[beg], &array[beg + 1]);
//		}
//	}
//}

void bubbleSortOneStepi()
{
	int* array = (int*)data;

	if (bubble_end >= 0)
	{
		if (bubble_beg < bubble_end - 1)
		{
			scan_index = bubble_beg;
			if (array[bubble_beg] > array[bubble_beg + 1])
			{
				swapi(&array[bubble_beg], &array[bubble_beg + 1]);
				swaped_index = bubble_beg + 1;
			}
			bubble_beg++;
		}
		else
		{
			bubble_end--;
			bubble_beg = 0;
		}
	}
	else
	{
		bubble_finished = 1;
		state = STATE_FINISHED;
		scan_index = -1;
		swaped_index = -1;
	}
}

void bubbleSortOneStepf()
{
	float* array = (float*)data;

	if (bubble_end >= 0)
	{
		if (bubble_beg < bubble_end - 1)
		{
			scan_index = bubble_beg;
			if (array[bubble_beg] > array[bubble_beg + 1])
			{
				swapf(&array[bubble_beg], &array[bubble_beg + 1]);
				swaped_index = bubble_beg + 1;
			}
			bubble_beg++;
		}
		else
		{
			bubble_end--;
			bubble_beg = 0;
		}
	}
	else
	{
		bubble_finished = 1;
		state = STATE_FINISHED;
		scan_index = -1;
		swaped_index = -1;
	}
}

void bubbleSortOneStepd()
{
	double* array = (double*)data;

	if (bubble_end >= 0)
	{
		if (bubble_beg < bubble_end - 1)
		{
			scan_index = bubble_beg;
			if (array[bubble_beg] > array[bubble_beg + 1])
			{
				swapd(&array[bubble_beg], &array[bubble_beg + 1]);
				swaped_index = bubble_beg + 1;
			}
			bubble_beg++;
		}
		else
		{
			bubble_end--;
			bubble_beg = 0;
		}
	}
	else
	{
		bubble_finished = 1;
		state = STATE_FINISHED;
		scan_index = -1;
		swaped_index = -1;
	}
}