
// Wuziqi.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWuziqiApp:
// �йش����ʵ�֣������ Wuziqi.cpp
//

class CWuziqiApp : public CWinApp
{
public:
	CWuziqiApp();
	/*picture�ؼ���ʾ���*/
	ULONG_PTR m_gdiplusToken;

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWuziqiApp theApp;