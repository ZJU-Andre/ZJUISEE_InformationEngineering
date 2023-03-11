#pragma once

// x y����߾�
extern const double xmargin;
extern const double ymargin;

// ���ڴ�С
extern double winwidth, winheight;

// �ؼ��߶�
extern double ctrlHeight;

// ��ǰ״̬
#define STATE_STOP 0
#define STATE_PLAYING 1
#define STATE_FINISHED 2
extern int state;

// ��ǰ��������
extern int sortType;
#define SORT_BUBBLE 1
#define SORT_SELECTION 2
#define SORT_MERGE 3

extern char* sortName[];

// �˵���id
#define MENU_INPUT_DATA 1
#define MENU_READ_SNAP 2
#define MENU_WRITE_SNAP 3
#define MENU_QUIT 4

#define EVENT_SORT_CHANGE 50

// ��ťid
#define BUTTON_RESET 101
#define BUTTON_RANDOM 102
#define BUTTON_PLAY 103
#define BUTTON_NEXT 104

extern int randomArrayLength;