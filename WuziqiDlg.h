
// WuziqiDlg.h : 头文件
//

#pragma once
#include "Engine_Log.h"
#include "afxdialogex.h"
#include "Total_Control_Center.h"
#include "resource.h"
#define G_WUZIQI CWuziqiDlg::SetInstance()
#define G_BOARD Board::GetInstance()
//#include "stdio.h"
// CWuziqiDlg 对话框
//Board *q_Chess;
//Board *y_Chess;
//#ifndef XXX
//#define XXX    
//     Board *qChess;
//     printf("[DEBUG]  WuziqiDlg\n");
//#endif

//class Board;

class CWuziqiDlg : public CDialogEx
{
// 构造
public:
	static CWuziqiDlg *SetInstance();
public:
	CDialogEx *m_pEngine;//日志窗口指针
	CDialogEx *m_pEngine_2;//日志窗口指针
	bool Log_Open;//判断日志窗口是否已经打开
	bool Log_Open_2;//判断日志窗口是否已经打开
	CWuziqiDlg(CWnd* pParent = NULL);	// 标准构造函数
	CImage png_pieces;	//棋子变量
	static CWuziqiDlg *CWuziqi;
	//int Picture_Control_ID[15][15];	//记录各个picture控件ID
	//int Picture_Control_State[15][15]; //记录棋子位置状态
	//int type_of_pieces;	//记录下棋类型[0下黑棋，1下白棋]
	CFont* m_Font;//在构造函数中要初始化
// 对话框数据
	enum { IDD = IDD_WUZIQI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void BackGround();//加载背景
	afx_msg void Show_Pieces();//显示棋子
	afx_msg void Change_Style(CImage*png);//处理透明背景
public:
	afx_msg void Picture_Control_Show_White(int X);//picture控件显示白棋
	afx_msg void Picture_Control_Show_Black(int X);//picture控件显示黑棋
	afx_msg void Picture_Control_Show_Empty(int X);//picture控件置空
	afx_msg void Init_Data();//初始化数据【未调用】
	afx_msg void Show_Icon();//加载玩家图标
	afx_msg void Clear_Board();//清空棋盘，并把引擎更新至准备状态
	afx_msg void Back_Chess();//悔棋
	afx_msg void Empty();//清空棋盘，不修改数据
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton6();
public:
	static Board *p_Chess;
	void together(int type,int X,int Y);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
public:
	CString OpenFilePath;
	CEdit *_outputEngine;

	CString OpenFilePath_2;
	CEdit *_outputEngine_2;
	
public:
	//Control_Center *s_p;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
