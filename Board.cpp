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
//��ʼ��������Ϣ
void Board::Init_Board()
{
	int x=1000;
	type_of_pieces = BLACK; //��������
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
//���壬ģ�������
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
	HWND h = ::FindWindow(NULL,L"���ݴ�ѧ������Ŀ--�����岩��ϵͳ");
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
//�ж�ʤ�����
bool Board::Check_If_Win(int LastX,int LastY,int Type)
{
	int count = 1;	//��¼������ͬ������,��ǰλ�ò����
	int Num = 5;
	bool If_Win = false;	//�Ƿ��Ѿ�ʤ��
	int i=0,j=0;
	//ˮƽ����
	for(i = LastX-1, j = LastY;i>=0 && If_Win == false;i--)	//ˮƽ����
	{
		if(Picture_Control_State[i][j] == Type)
		{
			count++;
		}
		else
			break;
	}

	for(i = LastX+1, j = LastY;i<15 && If_Win == false;i++)	//ˮƽ����
	{
		if(Picture_Control_State[i][j] == Type)
		{
			count++;
		}
		else
			break;
	}

	//�ж��Ƿ��Ѿ�ʤ��
	if(count >= Num)
		If_Win = true;
	else
		count = 1;

	//��ֱ����
	for(i = LastX, j = LastY-1;j>=0 && If_Win == false;j--)	//��ֱ����
	{
		if(Picture_Control_State[i][j] == Type)
		{
			count++;
		}
		else
			break;
	}

	for(i = LastX, j = LastY+1;j<15 && If_Win == false;j++)	//��ֱ����
	{
		if(Picture_Control_State[i][j] == Type)
		{
			count++;
		}
		else
			break;
	}
	//�ж��Ƿ��Ѿ�ʤ��
	if(count >= Num)
		If_Win = true;
	else
		count = 1;

	//�������·���
	for(i = LastX-1,j = LastY-1;(i>=0 || j>=0) && If_Win == false;i--,j--)	//���Ϸ���
	{
		if(Picture_Control_State[i][j] == Type)
		{
			count++;
		}
		else
			break;
	}
	for(i = LastX+1, j = LastY+1;(i<15  || j<15) && If_Win == false;i++,j++)	//���·���
	{
		if(Picture_Control_State[i][j] == Type)
		{
			count++;
		}
		else
			break;
	}

	//�ж��Ƿ��Ѿ�ʤ��
	if(count >= Num)
		If_Win = true;
	else
		count = 1;

	//�������Ϸ���
	for(i = LastX-1, j = LastY+1;(i>=0 || j<15) && If_Win == false;i--,j++)	//���·���
	{
		if(Picture_Control_State[i][j] == Type)
		{
			count++;
		}
		else
			break;
	}
	for(i = LastX+1,j = LastY-1;(i<15 || j>=0) && If_Win == false;i++,j--)	//���Ϸ���
	{
		if(Picture_Control_State[i][j] == Type)
		{
			count++;
		}
		else
			break;
	}

	//�ж��Ƿ�ʤ��
	if(count >= Num)
	{
		If_Win = true;
	}
	else
		count = 1;

	return If_Win;	//���ؽ��
}