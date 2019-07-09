#pragma once
#include "Command.h"
#include "stdafx.h"
#include "Board.h"
#include "WuziqiDlg.h"
//记录AI引擎运行状态
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
	//static bool AI_Start_1;	//监控变量
	//static bool AI_Start_2;
	static CEdit *s_pEditEngine;
	static CEdit *s_pEditEngine_2;
	static bool AI_2_Readiness;
	static bool Engine2_End;
	//初始化引擎一
	static bool InitAI(CString Path);
	//初始化引擎二
	static bool InitAI_2(CString Path);
	//监控引擎一
	static void Monitor(LPVOID param);
	//监控引擎二
	static void Monitor_2(LPVOID param);
	//开始监控引擎一
	static void Start_Monitor_1(CString Path,CEdit *_outputEngine);
	//开始监控引擎二
	static void Start_Monitor_2(CString Path,CEdit *_outputEngine);
	//停止监控
	static void Stop_Monitor();
	//判断是否为新游戏
	static bool isNewGame();
};