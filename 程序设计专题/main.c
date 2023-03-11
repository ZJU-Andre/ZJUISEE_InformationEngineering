
#include "libgraphics/graphics.h"
#include "libgraphics/extgraph.h"
#include "libgraphics/imgui.h"

#include "GlobalVars.h"
#include "MyMenu.h"
#include "MyButton.h"
#include "MyFunc.h"

#include<Windows.h>
#include<WinUser.h>
#define TIMER_RENDER_ID 1

// �û�����ʾ����
void display(void);

// ������Ϣ�ص�����
/* key��ʾ�ĸ�����event��ʾ���»��ɿ����¼� */
void KeyboardEventProcess(int key, int event);

// �ַ���Ϣ�ص�����
/* c��ʾ������ASCII�� */
void CharEventProcess(char c);

// �����Ϣ�ص�����
/* x,yλ�����꣬button�ĸ�����event����/�ɿ�/�ƶ����¼� */
void MouseEventProcess(int x, int y, int button, int event);

// ��ʱ����Ϣ�ص�����
/* timerID��ʱ����-�ĸ���ʱ����������Ϣ */
void TimerEventProcess(int timerID);

void Main()
{
	// ���ô�������
	SetWindowTitle("������ʾ v0.1");
	SetWindowSize(winwidth, winheight);

	// ��ʼ��
	InitGraphics();

	// ע���ʱ��
	startTimer(TIMER_RENDER_ID, 5);

	// ע���¼�
	registerTimerEvent(TimerEventProcess);
	registerMouseEvent(MouseEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	registerCharEvent(CharEventProcess);
}



void display()
{
	// ����
	DisplayClear();

	// ÿ֡���´�����Ϣ���ܿ�Ĺ������ƣ�����ʵ���ϲ�δˢ�£�
	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();
	ctrlHeight = GetFontHeight() * 1.5;

	// ���Ʊ���
	SetPenColor("BLACK");
	drawRectangle(0, 0, winwidth, winheight, 1);

	// ���ư�ť
	int event = 0;
	drawButton(&event);

	// ������״ͼ
	drawData();

	// ���Ʋ˵�
	drawMenu(&event);

	// �����¼�
	dealWithEvent(event);
}

// �û����ַ��¼���Ӧ����
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI�ַ�����
	
	display(); //ˢ����ʾ
}

// �û��ļ����¼���Ӧ����
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); // GUI��ȡ����
	
	if (event==KEY_UP&&key == VK_ESCAPE)
		exit(0); 
	display(); // ˢ����ʾ
}

// �û�������¼���Ӧ����
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event); //GUI��ȡ���
	display(); // ˢ����ʾ
}

void TimerEventProcess(int timer_id)
{
	switch (timer_id)
	{
	case TIMER_RENDER_ID:
		display();
		break;
	}
}