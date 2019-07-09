#pragma once
#include "stdafx.h"
#include <vector>
#define G_BOARD Board::GetInstance()

#include <iostream>
#include<conio.h>
#include<windows.h> 
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 
using namespace std;

#define EMPTY 0 //��
#define WHITE 1	//����
#define BLACK 2 //����

//class CWuziqiDlg;
class Board
{
public:
	static Board *GetInstance();
public:
	Board(void);
	~Board(void);
	static Board *board;
	// ��Ϸ����
	HWND m_pWnd;
public:
	int Picture_Control_ID[15][15];	//��¼����picture�ؼ�ID
	int Picture_Control_State[15][15]; //��¼����λ��״̬ 0Ϊ�գ�1Ϊ���壬2Ϊ����
	int type_of_pieces;	//��¼��������[2�º��壬1�°���]
	bool Start_Game;	//�Ƿ�ʼ��Ϸ
	bool Restart_Game;	//�Ƿ����¿�ʼ��Ϸ
	int Back_Chess[15][15];	//����ʹ�ã���¼����˳��
	bool	AI_Start_1;
	bool	AI_Start_2;
	//static CWuziqiDlg *q_Chess;
public:
	//CWuziqiDlg *test;

	void Init_Board();	//��ʼ��������Ϣ
	void Set_Chess(int X,int Y);	//����
	bool Check_If_Win(int LastX,int LastY,int Type);	//����Ƿ�ʤ��

public:
	bool NewGame;	//��¼�Ƿ�������Ϸ��Ĭ��Ϊ����Ϸ
	bool isEngine_1_Turn;	//�ж��Ƿ�����һ����
	bool isEngine_2_Turn;	//�ж��Ƿ����������
	int last_X;		//��һ���������
	int last_Y;		//��һ����������
	bool AI_To_People;//�ж��Ƿ����˻���ս


};

