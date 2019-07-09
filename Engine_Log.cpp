// Engine_Log.cpp : 实现文件
//

#include "stdafx.h"
#include "Wuziqi.h"
#include "Engine_Log.h"
#include "afxdialogex.h"


// Engine_Log 对话框

IMPLEMENT_DYNAMIC(Engine_Log, CDialogEx)

Engine_Log::Engine_Log(CWnd* pParent /*=NULL*/)
	: CDialogEx(Engine_Log::IDD, pParent)
{

}

Engine_Log::~Engine_Log()
{
}

void Engine_Log::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Engine_Log, CDialogEx)
END_MESSAGE_MAP()


// Engine_Log 消息处理程序
