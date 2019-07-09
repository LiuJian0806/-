#pragma once
#include "Command.h"
#include "stdafx.h"
#include "Board.h"
#include "WuziqiDlg.h"
//��¼AI��������״̬
//extern Board *q_Chess;
class Control_Center
{
public:
	Control_Center();
	~Control_Center();
	

private:
	static Command *s_pEngine;
	static Command *s_pEngine_2;

public:
	//static bool AI_Start_1;	//��ر���
	//static bool AI_Start_2;
	static CEdit *s_pEditEngine;
	static CEdit *s_pEditEngine_2;
	static bool AI_2_Readiness;
	static bool Engine2_End;
	//��ʼ������һ
	static bool InitAI(CString Path);
	//��ʼ�������
	static bool InitAI_2(CString Path);
	//�������һ
	static void Monitor(LPVOID param);
	//��������
	static void Monitor_2(LPVOID param);
	//��ʼ�������һ
	static void Start_Monitor_1(CString Path,CEdit *_outputEngine);
	//��ʼ��������
	static void Start_Monitor_2(CString Path,CEdit *_outputEngine);
	//ֹͣ���
	static void Stop_Monitor();
	//�ж��Ƿ�Ϊ����Ϸ
	static bool isNewGame();
};