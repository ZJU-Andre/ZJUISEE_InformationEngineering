#include "MyButton.h"

#include "libgraphics/graphics.h"
#include "libgraphics/extgraph.h"
#include "libgraphics/imgui.h"

#include "GlobalVars.h"

const int button_num = 3;

void drawButton(int *event)
{
	double w = (winwidth - (button_num + 1) * xmargin) / (double)button_num;
	double step_x = w + xmargin;

	double x = xmargin;
	double y = ymargin;
	setButtonColors("ORANGE", "BLACK", "GRAY", "BLACK", 1);
	//if (button(GenUIID(0), x, y, w, ctrlHeight, "复位"))
	//	*event = BUTTON_RESET;

	if (button(GenUIID(0), x, y, w, ctrlHeight, "产生随机数"))
		*event = BUTTON_RANDOM;

	switch (state)
	{
	case STATE_STOP:
		if (button(GenUIID(0), x += step_x, y, w, ctrlHeight, "自动排序"))
		{
			*event = BUTTON_PLAY;
			state = STATE_PLAYING;
		}
		break;
	case STATE_PLAYING:
		if (button(GenUIID(0), x += step_x, y, w, ctrlHeight, "停止排序"))
		{
			*event = BUTTON_PLAY;
			state = STATE_STOP;
		}
		break;
	case STATE_FINISHED:
		SetPenColor("ORANGE");
		drawBox(x += step_x, y, w, ctrlHeight, 1, "排序完成", 'C', "BLACK");
		if (button(GenUIID(0), x, y, w, ctrlHeight, "排序完成")) {
			exit(0);
		}
			break;
	}

	if (button(GenUIID(0), x += step_x, y, w, ctrlHeight, "下一步"))
		*event = BUTTON_NEXT;
}