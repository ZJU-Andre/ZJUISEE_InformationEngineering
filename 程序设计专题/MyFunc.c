#include "MyFunc.h"

#include "libgraphics/simpio.h"
#include "libgraphics/random.h"
#include "libgraphics/linkedlist.h"
#include "libgraphics/strlib.h"

#include "libgraphics/graphics.h"
#include "libgraphics/extgraph.h"
#include "libgraphics/imgui.h"

#include "MyButton.h"
#include "GlobalVars.h"
#include "MyData.h"

#include "BubbleSort.h"
#include "SelectionSort.h"
#include "MergeSort.h"

void initSort()
{
	switch (sortType)
	{
	case SORT_BUBBLE:
		initBubble();
		break;
	case SORT_SELECTION:
		initSelection();
		break;
	case SORT_MERGE:
		initMerge();
		break;
	}
	state = STATE_STOP;
}

void sortOneStep()
{
	switch (sortType)
	{
	case SORT_BUBBLE:
		switch (data_type)
		{
		case DATA_INT:
			bubbleSortOneStepi();
			break;
		case DATA_FLOAT:
			bubbleSortOneStepf();
			break;
		case DATA_DOUBLE:
			bubbleSortOneStepd();
			break;
		}
		break;
	case SORT_SELECTION:
		switch (data_type)
		{
		case DATA_INT:
			selectionSortOneStepi();
			break;
		case DATA_FLOAT:
			selectionSortOneStepf();
			break;
		case DATA_DOUBLE:
			selectionSortOneStepd();
			break;
		}
		break;
	case SORT_MERGE:
		switch (data_type)
		{
		case DATA_INT:
			mergeSortOneStepi();
			break;
		case DATA_FLOAT:
			mergeSortOneStepf();
			break;
		case DATA_DOUBLE:
			mergeSortOneStepd();
			break;
		}
		break;
	}
}

// ������������ͼ
void drawData()
{
	// ���Ʊ���
	SetPenColor("LIGHT GRAY");
	double x0 = xmargin;
	double y0 = ymargin * 2 + ctrlHeight;
	double x1 = winwidth - xmargin;
	double y1 = winheight - ctrlHeight - ymargin;
	double w = x1 - x0;
	double h = y1 - y0;
	drawRectangle(x0, y0, x1 - x0, y1 - y0, 1);

	// ���������㷨����
	SetPenColor("ORANGE");
	char* curSortName = sortName[sortType];
	double xc = x0 + winwidth * 0.5;
	double ytitle = y1 + ymargin * 0.2;
	double wtitle = TextStringWidth(curSortName);
	double xtitle = xc - wtitle;
	drawLabel(xtitle, ytitle, curSortName);

	// ��������
	switch (data_type)
	{
	case DATA_INT:
	{
		double step = w / (double)data_num;

		// ������״ͼ
		SetPenColor("ORANGE");
		int val_range = *(int*)maxval - *(int*)minval;
		for (int i = 0; i < data_num; ++i)
		{
			double x = x0 + i * step;
			double y = y0;
			int val = ((int*)view_data)[i];
			double val_percent = (double)(val - *(int*)minval) / (double)val_range;
			double val_h = val_percent * h;

			if (i == swaped_index)
				SetPenColor("RED");
			else
				if (i == scan_index)
					SetPenColor("GRAY");
				else
					SetPenColor("ORANGE");
			drawRectangle(x, y, step, val_h, 1);
			SetPenColor("WHITE");
			MovePen(x, y);
			DrawLine(0, val_h);
			DrawLine(step, 0);
			DrawLine(0, -val_h);
			DrawLine(-step, 0);
		}

		// ��������
		SetPenColor("RED");
		for (int i = 0; i < data_num; ++i)
		{
			double x = x0 + i * step;
			double y = y0;
			int val = ((int*)view_data)[i];
			double val_percent = (double)(val - *(int*)minval) / (double)val_range;
			double val_h = val_percent * h;

			drawLabel(x, y + val_h, IntegerToString(val));
		}
		break;
	}
	case DATA_FLOAT:
	{
		double step = w / (double)data_num;

		// ������״ͼ
		SetPenColor("ORANGE");
		int val_range = *(float*)maxval - *(float*)minval;
		for (int i = 0; i < data_num; ++i)
		{
			double x = x0 + i * step;
			double y = y0;
			float val = ((float*)view_data)[i];
			double val_percent = (double)(val - *(float*)minval) / (double)val_range;
			double val_h = val_percent * h;

			if (i == swaped_index)
				SetPenColor("RED");
			else
				if (i == scan_index)
					SetPenColor("GRAY");
				else
					SetPenColor("ORANGE");
			drawRectangle(x, y, step, val_h, 1);
			SetPenColor("WHITE");
			MovePen(x, y);
			DrawLine(0, val_h);
			DrawLine(step, 0);
			DrawLine(0, -val_h);
			DrawLine(-step, 0);

		}

		// ��������
		SetPenColor("RED");
		for (int i = 0; i < data_num; ++i)
		{
			double x = x0 + i * step;
			double y = y0;
			float val = ((float*)view_data)[i];
			double val_percent = (double)(val - *(float*)minval) / (double)val_range;
			double val_h = val_percent * h;

			drawLabel(x, y + val_h, RealToString(val));
		}
		break;
	}
	case DATA_DOUBLE:
	{
		double step = w / (double)data_num;

		// ������״ͼ
		SetPenColor("ORANGE");
		int val_range = *(double*)maxval - *(double*)minval;
		for (int i = 0; i < data_num; ++i)
		{
			double x = x0 + i * step;
			double y = y0;
			double val = ((double*)view_data)[i];
			double val_percent = (double)(val - *(double*)minval) / (double)val_range;
			double val_h = val_percent * h;

			if (i == swaped_index)
				SetPenColor("RED");
			else
				if (i == scan_index)
					SetPenColor("GRAY");
				else
					SetPenColor("ORANGE");
			drawRectangle(x, y, step, val_h, 1);
			SetPenColor("WHITE");
			MovePen(x, y);
			DrawLine(0, val_h);
			DrawLine(step, 0);
			DrawLine(0, -val_h);
			DrawLine(-step, 0);
		}

		// ��������
		SetPenColor("RED");
		for (int i = 0; i < data_num; ++i)
		{
			double x = x0 + i * step;
			double y = y0;
			double val = ((double*)view_data)[i];
			double val_percent = (double)(val - *(double*)minval) / (double)val_range;
			double val_h = val_percent * h;

			drawLabel(x, y + val_h, RealToString(val));
		}
		break;
	}
	}
}

// �����ı�����
void inputData()
{
	FILE* fp = fopen("input.txt", "r");
	if (fp == NULL)
		return;

	initSort();

	// �������
	releaseData();

	// ����һ��
	string line = ReadLine(fp);
	int len = StringLength(line);

	// �ж���������
	data_type = DATA_NULL;
	int i = 0;
	for (; i < len; ++i)
	{
		if (line[i] == ' ')
		{
			line[i] = 0;
			if (StringCompare(line, "int") == 0)
			{
				data_type = DATA_INT;
				i++;
				break;
			}
			if (StringCompare(line, "float") == 0)
			{
				data_type = DATA_FLOAT;
				i++;
				break;
			}
			if (StringCompare(line, "double") == 0)
			{
				data_type = DATA_DOUBLE;
				i++;
				break;
			}
		}
	}

	if (data_type == DATA_NULL)
		return;

	// ��ʼ����С���ֵ
	setInitMinMax();

	// ��������
	linkedlistADT head;
	linkedlistADT* cur = &head;

	// temp�б�����ǵ�ǰ�������ַ�����ָ��λ��
	string temp = &line[i];
	for (; i < len; ++i)
	{
		char c = line[i];
		if ((c >= '0' && c <= '9') || c == '.')
		{
			continue;
		}
		if (c == ' ')
		{
			line[i] = 0;

			// �Ѿ���һ����������
			switch (data_type)
			{
			case DATA_INT:
			{
				// ��ȡ��ֵ
				int val = StringToInteger(temp);

				// ����һ���ڵ�
				*cur = NewLinkedList();

				// ��������
				(*cur)->dataptr = malloc(sizeof(int));
				*((int*)(*cur)->dataptr) = val;

				// �ƶ���ǰ�ڵ�
				cur = &(*cur)->next;

				data_num++;
				refreshMinMaxi(val);
				break;
			}
			case DATA_FLOAT:
			{
				// ��������
				float val = StringToReal(temp);
				*cur = NewLinkedList();
				(*cur)->dataptr = malloc(sizeof(float));
				*((float*)(*cur)->dataptr) = val;

				cur = &(*cur)->next;

				data_num++;
				refreshMinMaxf(val);
				break;
			}
			case DATA_DOUBLE:
			{
				// ��������
				double val = StringToReal(temp);
				*cur = NewLinkedList();
				(*cur)->dataptr = malloc(sizeof(double));
				*((double*)(*cur)->dataptr) = val;

				cur = &(*cur)->next;

				data_num++;
				refreshMinMaxd(val);
				break;
			}
			}

			temp = &line[i + 1];
		}
	}

	// Ϊdata����ռ䣬���������л�ȡ����
	switch (data_type)
	{
	case DATA_INT:
	{
		data = malloc(data_num * sizeof(int));
		int* array = (int*)data;
		int pos = 0;
		linkedlistADT cur = head;
		while (cur)
		{
			int val = *((int*)(cur->dataptr));
			array[pos++] = val;
			cur = cur->next;
		}
		break;
	}
	case DATA_FLOAT:
	{
		data = malloc(data_num * sizeof(float));
		float* array = (float*)data;
		int pos = 0;
		linkedlistADT cur = head;
		while (cur)
		{
			float val = *((float*)(cur->dataptr));
			array[pos++] = val;
			cur = cur->next;
		}
		break;
	}
	case DATA_DOUBLE:
	{
		data = malloc(data_num * sizeof(double));
		double* array = (double*)data;
		int pos = 0;
		linkedlistADT cur = head;
		while (cur)
		{
			double val = *((double*)(cur->dataptr));
			array[pos++] = val;
			cur = cur->next;
		}
		break;
	}
	}

	// �ͷ�����
	FreeLinkedList(head);

	// �ͷ��ַ���
	FreeBlock(line);

	// �ر��ļ�
	fclose(fp);

	// ��ʼ������״̬
	initSort();
}

void writeSortSnap(FILE* fp)
{
	fwrite(&sortType, sizeof(sortType), 1, fp);

	switch (sortType)
	{
	case SORT_BUBBLE:
		writeBubbleSnap(fp);
		break;
	case SORT_SELECTION:
		writeSelectionSnap(fp);
		break;
	case SORT_MERGE:
		writeMergeSnap(fp);
		break;
	}
}

void readSortSnap(FILE* fp)
{
	fread(&sortType, sizeof(sortType), 1, fp);

	switch (sortType)
	{
	case SORT_BUBBLE:
		readBubbleSnap(fp);
		break;
	case SORT_SELECTION:
		readSelectionSnap(fp);
		break;
	case SORT_MERGE:
		readMergeSnap(fp);
		break;
	}
}

void saveSnap()
{
	FILE* fp = fopen("snap.dat", "wb");
	if (fp == NULL)
		return;

	writeDataSnap(fp);
	writeSortSnap(fp);

	fclose(fp);
}

void readSnap()
{
	FILE* fp = fopen("snap.dat", "rb");
	if (fp == NULL)
		return;

	readDataSnap(fp);
	readSortSnap(fp);

	fclose(fp);

	state = STATE_STOP;
}

void genRandomArray()
{
	initSort();

	// �����������

	releaseData();
	Randomize();

	data_type = DATA_INT;
	setInitMinMax();

	data_num = randomArrayLength;

	data = malloc(data_num * sizeof(int));
	int* array = (int*)data;
	for (int i = 0; i < data_num; ++i)
	{
		int val = RandomInteger(0, 100);
		array[i] = val;

		//
		refreshMinMaxi(val);
	}

	initSort();
}

void dealWithEvent(int event)
{
	switch (event)
	{
	case MENU_INPUT_DATA:
	{
		inputData();
		break;
	}
	case MENU_WRITE_SNAP:
	{
		saveSnap();
		break;
	}
	case MENU_READ_SNAP:
	{
		readSnap();
		break;
	}
	case MENU_QUIT:
		exit(0);
		break;
	case EVENT_SORT_CHANGE:
		initSort();
		break;
	case BUTTON_RANDOM:
		genRandomArray();
	break;
	case BUTTON_PLAY:
		//state = STATE_PLAYING;
		break;
	case BUTTON_NEXT:
		sortOneStep();
		break;
	}

	switch (state)
	{
	case STATE_PLAYING:
		sortOneStep();
		break;
	}
}