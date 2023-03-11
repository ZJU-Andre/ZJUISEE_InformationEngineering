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
	//if (button(GenUIID(0), x, y, w, ctrlHeight, "��λ"))
	//	*event = BUTTON_RESET;

	if (button(GenUIID(0), x, y, w, ctrlHeight, "���������"))
		*event = BUTTON_RANDOM;

	switch (state)
	{
	case STATE_STOP:
		if (button(GenUIID(0), x += step_x, y, w, ctrlHeight, "�Զ�����"))
		{
			*event = BUTTON_PLAY;
			state = STATE_PLAYING;
		}
		break;
	case STATE_PLAYING:
		if (button(GenUIID(0), x += step_x, y, w, ctrlHeight, "ֹͣ����"))
		{
			*event = BUTTON_PLAY;
			state = STATE_STOP;
		}
		break;
	case STATE_FINISHED:
		SetPenColor("ORANGE");
		drawBox(x += step_x, y, w, ctrlHeight, 1, "�������", 'C', "BLACK");
		if (button(GenUIID(0), x, y, w, ctrlHeight, "�������")) {
			exit(0);
		}
			break;
	}

	if (button(GenUIID(0), x += step_x, y, w, ctrlHeight, "��һ��"))
		*event = BUTTON_NEXT;
}