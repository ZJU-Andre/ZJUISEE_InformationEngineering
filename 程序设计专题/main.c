
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

// 用户的显示函数
void display(void);

// 键盘消息回调函数
/* key表示哪个键，event表示按下或松开等事件 */
void KeyboardEventProcess(int key, int event);

// 字符消息回调函数
/* c表示按键的ASCII码 */
void CharEventProcess(char c);

// 鼠标消息回调函数
/* x,y位置坐标，button哪个键，event按下/松开/移动等事件 */
void MouseEventProcess(int x, int y, int button, int event);

// 定时器消息回调函数
/* timerID定时器号-哪个定时器触发了消息 */
void TimerEventProcess(int timerID);

void Main()
{
	// 设置窗口属性
	SetWindowTitle("排序演示 v0.1");
	SetWindowSize(winwidth, winheight);

	// 初始化
	InitGraphics();

	// 注册计时器
	startTimer(TIMER_RENDER_ID, 5);

	// 注册事件
	registerTimerEvent(TimerEventProcess);
	registerMouseEvent(MouseEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	registerCharEvent(CharEventProcess);
}



void display()
{
	// 清屏
	DisplayClear();

	// 每帧更新窗口信息（受库的功能限制，长宽实际上并未刷新）
	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();
	ctrlHeight = GetFontHeight() * 1.5;

	// 绘制背景
	SetPenColor("BLACK");
	drawRectangle(0, 0, winwidth, winheight, 1);

	// 绘制按钮
	int event = 0;
	drawButton(&event);

	// 绘制柱状图
	drawData();

	// 绘制菜单
	drawMenu(&event);

	// 处理事件
	dealWithEvent(event);
}

// 用户的字符事件响应函数
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI字符输入
	
	display(); //刷新显示
}

// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); // GUI获取键盘
	
	if (event==KEY_UP&&key == VK_ESCAPE)
		exit(0); 
	display(); // 刷新显示
}

// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event); //GUI获取鼠标
	display(); // 刷新显示
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