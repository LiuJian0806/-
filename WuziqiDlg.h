
// WuziqiDlg.h : ͷ�ļ�
//

#pragma once
#include "Engine_Log.h"
#include "afxdialogex.h"
#include "Total_Control_Center.h"
#include "resource.h"
#define G_WUZIQI CWuziqiDlg::SetInstance()
#define G_BOARD Board::GetInstance()
//#include "stdio.h"
// CWuziqiDlg �Ի���
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
// ����
public:
	static CWuziqiDlg *SetInstance();
public:
	CDialogEx *m_pEngine;//��־����ָ��
	CDialogEx *m_pEngine_2;//��־����ָ��
	bool Log_Open;//�ж���־�����Ƿ��Ѿ���
	bool Log_Open_2;//�ж���־�����Ƿ��Ѿ���
	CWuziqiDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CImage png_pieces;	//���ӱ���
	static CWuziqiDlg *CWuziqi;
	//int Picture_Control_ID[15][15];	//��¼����picture�ؼ�ID
	//int Picture_Control_State[15][15]; //��¼����λ��״̬
	//int type_of_pieces;	//��¼��������[0�º��壬1�°���]
	CFont* m_Font;//�ڹ��캯����Ҫ��ʼ��
// �Ի�������
	enum { IDD = IDD_WUZIQI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void BackGround();//���ر���
	afx_msg void Show_Pieces();//��ʾ����
	afx_msg void Change_Style(CImage*png);//����͸������
public:
	afx_msg void Picture_Control_Show_White(int X);//picture�ؼ���ʾ����
	afx_msg void Picture_Control_Show_Black(int X);//picture�ؼ���ʾ����
	afx_msg void Picture_Control_Show_Empty(int X);//picture�ؼ��ÿ�
	afx_msg void Init_Data();//��ʼ�����ݡ�δ���á�
	afx_msg void Show_Icon();//�������ͼ��
	afx_msg void Clear_Board();//������̣��������������׼��״̬
	afx_msg void Back_Chess();//����
	afx_msg void Empty();//������̣����޸�����
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
