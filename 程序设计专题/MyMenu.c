#include "MyMenu.h"

#include "libgraphics/graphics.h"
#include "libgraphics/extgraph.h"
#include "libgraphics/imgui.h"

#include "GlobalVars.h"
#include "MyFunc.h"

// �˵�
void drawMenu(int *event)
{
	static char* menuListFile[] = { "�ļ�",
		"�����ı����� | Ctrl-O", // ��ݼ��������[Ctrl-X]��ʽ�������ַ����Ľ�β
		"��ȡ���� | Ctrl-R",
		"������� | Ctrl-S",
		"�˳� | ESC" };
	static char* menuListSort[] = { "����ʽ",
		"ð������ | Ctrl-B",
		"ѡ������ | Ctrl-N",
		"�鲢���� | Ctrl-M" };
	static char* menuListRandom[] = { "���������",
		"����10��",
		"����50��",
		"����100��",
		"����250��" };

	double x = 0; //fH/8;
	double y = winheight;
	double h = ctrlHeight; // �ؼ��߶�
	double w = TextStringWidth(menuListFile[0]); // �ؼ����
	double wlist = TextStringWidth(menuListFile[1]) * 1.2;
	double xindent = winheight / 20; // ����

	// menu bar
	setMenuColors("BLACK", "ORANGE", "GRAY", "RED", 1);
	drawMenuBar(0, y - h, winwidth, h);

	// �˵�
	int ret = menuList(GenUIID(0), x, y - h, w*1.5, wlist+0.01, h, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (ret > 0)
		*event = ret;

	// �˵�
	int ret_sort = menuList(GenUIID(0), x += w*1.5, y - h, w*2.5, wlist, h, menuListSort, sizeof(menuListSort) / sizeof(menuListSort[0]));
	if (ret_sort > 0)
	{
		if (sortType != ret_sort)
		{
			sortType = ret_sort;
			*event = EVENT_SORT_CHANGE;
		}
	}

	// �˵�
	int ret_random = menuList(GenUIID(0), x += w*2.5, y - h, w*3, wlist, h, menuListRandom, sizeof(menuListRandom) / sizeof(menuListRandom[0]));
	switch (ret_random)
	{
	case 1:
		randomArrayLength = 10;
		genRandomArray();
		break;
	case 2:
		randomArrayLength = 50;
		genRandomArray();
		break;
	case 3:
		randomArrayLength = 100;
		genRandomArray();
		break;
	case 4:
		randomArrayLength = 250;
		genRandomArray();
		break;
	}
}