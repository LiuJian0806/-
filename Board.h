#pragma once
#include "stdafx.h"
#include <vector>
#define G_BOARD Board::GetInstance()

#include <iostream>
#include<conio.h>
#include<windows.h> 
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 
using namespace std;

#define EMPTY 0 //空
#define WHITE 1	//白棋
#define BLACK 2 //黑棋

//class CWuziqiDlg;
class Board
{
public:
	static Board *GetInstance();
public:
	Board(void);
	~Board(void);
	static Board *board;
	// 游戏窗口
	HWND m_pWnd;
public:
	int Picture_Control_ID[15][15];	//记录各个picture控件ID
	int Picture_Control_State[15][15]; //记录棋子位置状态 0为空，1为白棋，2为黑棋
	int type_of_pieces;	//记录下棋类型[2下黑棋，1下白棋]
	bool Start_Game;	//是否开始游戏
	bool Restart_Game;	//是否重新开始游戏
	int Back_Chess[15][15];	//悔棋使用，记录棋子顺序
	bool	AI_Start_1;
	bool	AI_Start_2;
	//static CWuziqiDlg *q_Chess;
public:
	//CWuziqiDlg *test;

	void Init_Board();	//初始化棋盘信息
	void Set_Chess(int X,int Y);	//下棋
	bool Check_If_Win(int LastX,int LastY,int Type);	//检查是否胜出

public:
	bool NewGame;	//记录是否是新游戏，默认为新游戏
	bool isEngine_1_Turn;	//判断是否引擎一下棋
	bool isEngine_2_Turn;	//判断是否引擎二下棋
	int last_X;		//上一步棋横坐标
	int last_Y;		//上一步棋纵坐标
	bool AI_To_People;//判断是否是人机对战


};

