#include "MyMenu.h"

#include "libgraphics/graphics.h"
#include "libgraphics/extgraph.h"
#include "libgraphics/imgui.h"

#include "GlobalVars.h"
#include "MyFunc.h"

// 菜单
void drawMenu(int *event)
{
	static char* menuListFile[] = { "文件",
		"读入文本数据 | Ctrl-O", // 快捷键必须采用[Ctrl-X]格式，放在字符串的结尾
		"读取快照 | Ctrl-R",
		"保存快照 | Ctrl-S",
		"退出 | ESC" };
	static char* menuListSort[] = { "排序方式",
		"冒泡排序 | Ctrl-B",
		"选择排序 | Ctrl-N",
		"归并排序 | Ctrl-M" };
	static char* menuListRandom[] = { "生成随机数",
		"生成10个",
		"生成50个",
		"生成100个",
		"生成250个" };

	double x = 0; //fH/8;
	double y = winheight;
	double h = ctrlHeight; // 控件高度
	double w = TextStringWidth(menuListFile[0]); // 控件宽度
	double wlist = TextStringWidth(menuListFile[1]) * 1.2;
	double xindent = winheight / 20; // 缩进

	// menu bar
	setMenuColors("BLACK", "ORANGE", "GRAY", "RED", 1);
	drawMenuBar(0, y - h, winwidth, h);

	// 菜单
	int ret = menuList(GenUIID(0), x, y - h, w*1.5, wlist+0.01, h, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (ret > 0)
		*event = ret;

	// 菜单
	int ret_sort = menuList(GenUIID(0), x += w*1.5, y - h, w*2.5, wlist, h, menuListSort, sizeof(menuListSort) / sizeof(menuListSort[0]));
	if (ret_sort > 0)
	{
		if (sortType != ret_sort)
		{
			sortType = ret_sort;
			*event = EVENT_SORT_CHANGE;
		}
	}

	// 菜单
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