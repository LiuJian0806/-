#pragma once
#include "resource.h"
// Engine_Log �Ի���

class Engine_Log : public CDialogEx
{
	DECLARE_DYNAMIC(Engine_Log)

public:
	Engine_Log(CWnd* pParent = NULL);   // ��׼���캯���ĳ¸�
	virtual ~Engine_Log();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
