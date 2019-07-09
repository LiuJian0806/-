#include "stdafx.h"
#include "Board.h"
#include "WuziqiDlg.h"


Board::Board(void)
{
	//Init_Board();
}

Board::~Board(void)
{
}
//CWuziqiDlg *Board::q_Chess(nullptr);
Board *Board::board = NULL;
//初始化棋盘信息
void Board::Init_Board()
{
	int x=1000;
	type_of_pieces = BLACK; //黑棋先下
	isEngine_1_Turn = false;
	isEngine_2_Turn = false;
	Start_Game = false;
	Restart_Game = false;
	AI_To_People = true;
	last_X = -1;
	last_Y = -1;
	NewGame = true;

	AI_Start_1 = false;
	AI_Start_2 = false;

	for(int i=0;i<15;i++)
		for(int j=0;j<15;j++)
		{
			Picture_Control_State[j][i] = EMPTY;
			Back_Chess[i][j] = 0;
			Picture_Control_ID[j][i] = x;
			x++;
		}
}

Board* Board::GetInstance()
{
	if (NULL == board)
	{
		board = new Board();
	}
	return board;
}
//下棋，模拟鼠标点击
void Board::Set_Chess(int X,int Y)
{
	int x,y;
	if(X == 0)
	{
		x = 50;
	}
	else
	{
		x = (X+1)*50;
	}
	if(Y == 0)
	{
		y = 49;
	}
	else
	{
		y = (Y+1)*49;
	}
	/*mouse_event(MOUSEEVENTF_LEFTDOWN,x,y,0,0);
	Sleep(100);
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
	AfxMessageBox(TEXT("yunxin1!"));*/
		 /* CWnd *wnd  = AfxGetMainWnd();
                     HWND hwnd = wnd->GetSafeHwnd();*/
	HWND h = ::FindWindow(NULL,L"广州大学创新项目--五子棋博弈系统");
	LPARAM lParam = MAKEWPARAM(x,y);
	PostMessage(h,WM_MOUSEMOVE,1,lParam);
	Sleep(100);
	PostMessage(h,WM_LBUTTONDOWN,1,lParam);
	PostMessage(h,WM_LBUTTONUP,1,lParam);
	Sleep(100);
	/*AfxGetMainWnd()->m_hWnd;
	m_pWnd->PostMessage(WM_MOUSEMOVE, 1, x + (y << 16));
	Sleep(20);
	m_pWnd->PostMessage(WM_LBUTTONDOWN, 1, x + (y << 16));
	m_pWnd->PostMessage(WM_LBUTTONUP, 1, x + (y << 16));
	Sleep(100);*/
}
//判断胜负情况
bool Board::Check_If_Win(int LastX,int LastY,int Type)
{
	int count = 1;	//记录方向相同棋子数,当前位置不检查
	int Num = 5;
	bool If_Win = false;	//是否已经胜出
	int i=0,j=0;
	//水平方向
	for(i = LastX-1, j = LastY;i>=0 && If_Win == false;i--)	//水平向左
	{
		if(Picture_Control_State[i][j] == Type)
		{
			count++;
		}
		else
			break;
	}

	for(i = LastX+1, j = LastY;i<15 && If_Win == false;i++)	//水平向右
	{
		if(Picture_Control_State[i][j] == Type)
		{
			count++;
		}
		else
			break;
	}

	//判断是否已经胜出
	if(count >= Num)
		If_Win = true;
	else
		count = 1;

	//垂直方向
	for(i = LastX, j = LastY-1;j>=0 && If_Win == false;j--)	//垂直向上
	{
		if(Picture_Control_State[i][j] == Type)
		{
			count++;
		}
		else
			break;
	}

	for(i = LastX, j = LastY+1;j<15 && If_Win == false;j++)	//垂直向下
	{
		if(Picture_Control_State[i][j] == Type)
		{
			count++;
		}
		else
			break;
	}
	//判断是否已经胜出
	if(count >= Num)
		If_Win = true;
	else
		count = 1;

	//左上右下方向
	for(i = LastX-1,j = LastY-1;(i>=0 || j>=0) && If_Win == false;i--,j--)	//左上方向
	{
		if(Picture_Control_State[i][j] == Type)
		{
			count++;
		}
		else
			break;
	}
	for(i = LastX+1, j = LastY+1;(i<15  || j<15) && If_Win == false;i++,j++)	//右下方向
	{
		if(Picture_Control_State[i][j] == Type)
		{
			count++;
		}
		else
			break;
	}

	//判断是否已经胜出
	if(count >= Num)
		If_Win = true;
	else
		count = 1;

	//左下右上方向
	for(i = LastX-1, j = LastY+1;(i>=0 || j<15) && If_Win == false;i--,j++)	//左下方向
	{
		if(Picture_Control_State[i][j] == Type)
		{
			count++;
		}
		else
			break;
	}
	for(i = LastX+1,j = LastY-1;(i<15 || j>=0) && If_Win == false;i++,j--)	//右上方向
	{
		if(Picture_Control_State[i][j] == Type)
		{
			count++;
		}
		else
			break;
	}

	//判断是否胜出
	if(count >= Num)
	{
		If_Win = true;
	}
	else
		count = 1;

	return If_Win;	//返回结果
}