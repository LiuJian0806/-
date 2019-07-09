#pragma once
#include "resource.h"
// Engine_Log 对话框

class Engine_Log : public CDialogEx
{
	DECLARE_DYNAMIC(Engine_Log)

public:
	Engine_Log(CWnd* pParent = NULL);   // 标准构造函数改陈该
	virtual ~Engine_Log();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
