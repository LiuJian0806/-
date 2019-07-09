#include "stdafx.h"
#include"Total_Control_Center.h"
#include "Board.h"

#include "iostream"
#include <io.h>    
#include <fcntl.h>  
#include <io.h>    
#include <fcntl.h> 

using namespace std;

Command *Control_Center::s_pEngine(nullptr);//����һ״̬
Command *Control_Center::s_pEngine_2(nullptr);//�����״̬

CEdit *Control_Center::s_pEditEngine(nullptr);//����һ��־������
CEdit *Control_Center::s_pEditEngine_2(nullptr);//�������־������

//bool Control_Center::AI_Start_1(false); //����һ����ж�
//bool Control_Center::AI_Start_2(false);	//���������ж�

bool Control_Center::AI_2_Readiness(false);//������Ƿ������
bool Control_Center::Engine2_End(false);//�ж�������Ƿ�ر�

void Control_Center::Start_Monitor_1(CString Path,CEdit *_outputEngine)
{
	s_pEditEngine = _outputEngine;
	//����ǰ�Ƿ���������е�����
	if(G_BOARD->AI_Start_1)
	{
		Stop_Monitor();
	}
	G_BOARD->AI_Start_1 = InitAI(Path);
	if(G_BOARD->AI_Start_1)
	{
		AfxMessageBox(TEXT("����һ���سɹ�!"));
		if(G_BOARD->AI_To_People)
			_beginthread(Monitor,0,NULL);
	
		
	}
	else
	{
		AfxMessageBox(TEXT("����һ����ʧ��!"));
	}		
}

void Control_Center::Start_Monitor_2(CString Path,CEdit *_outputEngine)
{
	s_pEditEngine_2 = _outputEngine;

	//����ǰ�Ƿ���������е�����
	if(G_BOARD->AI_Start_2)
	{
		Stop_Monitor();
	}
	G_BOARD->AI_Start_2 = InitAI_2(Path);
	if(G_BOARD->AI_Start_2)
	{
		AfxMessageBox(TEXT("��������سɹ�!"));
		AI_2_Readiness = true;
		_beginthread(Monitor,0,NULL);
		_beginthread(Monitor_2,0,NULL);
		
	}
	else
	{
		AfxMessageBox(TEXT("���������ʧ��!"));
	}

}

void Control_Center::Monitor(LPVOID param)
{
	/*�ڿ���ʾ*/
	/*AllocConsole();
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle, _O_TEXT);
	FILE * hf = _fdopen(hCrt, "w");
	*stdout = *hf;*/
	//Board *p_Chess = new Board();//��ʼ�������Ϣ

	while(!AI_2_Readiness)	//�ȴ���������سɹ���Ϸ��ʼ
	{
		if(G_BOARD->AI_To_People)	//�����ǰΪ�˻���ս��Ĭ��������Ѽ������
			AI_2_Readiness = true;
		Sleep(1);
	}
	//AI_2_Readiness = false;
	clock_t clock_Begin;	//��¼��ʼʱ��
	clock_Begin = clock();
	CString text;	//��¼����״̬
	int Init = 0;
	CString	exX;
	CString exY;
	bool ifNewGame = 0;	//��¼�Ƿ�Ϊ����Ϸ
	if(s_pEngine)	//���������������
	{}
	bool PreInBoard = 0;//
	bool doNewGame = 0;//

	while(G_BOARD->NewGame)
	{
		if(isNewGame())
		{
			G_BOARD->NewGame = false;	//����������Ϸ
			s_pEditEngine->SetWindowTextW(s_pEngine->inBEGIN());
			break;
		}
		else
		{
			break;
		}
		Sleep(10);
	}
	//�������һ
	for(int i=1;G_BOARD->AI_Start_1&&AI_2_Readiness;i++)
	{
		if(Engine2_End)
		{
			Stop_Monitor();
			AI_2_Readiness = false;
			//G_BOARD->Restart_Game = false;
			/*s_pEngine->inEND();*/
			break;
		}

		else
		{
			if (isNewGame())
			{
				//s_pEngine->inRESTART();
				text.Append(L"����Ϸ��ʼ��\r\n");
				ifNewGame = 1;
			}

			if(G_BOARD->isEngine_1_Turn)
			{
				text.Append(L"�ֵ��ҷ����ӣ�\r\n");
				G_BOARD->isEngine_1_Turn = false;
				s_pEditEngine->SetWindowTextW(s_pEngine->inTURN(G_BOARD->last_X, G_BOARD->last_Y));
			}
		}
		//AI_2_Readiness = false;
		Sleep(20);
		/*len = s_pEdit->GetWindowTextLength();
		s_pEdit->SetSel(len, len);
		s_pEdit->ScrollWindow(0, 0);*/

	}
	AI_2_Readiness = false;
	Engine2_End = false;
	//CWuziqiDlg *p_CHESS = new CWuziqiDlg;

	//G_WUZIQI->Picture_Control_Show_Black(1001);
	//G_BOARD->Set_Chess(10,10);
	/*for(int i = 0;i<15;i++)
	for(int j = 0;j<15;j++)
	{
	cout<<G_BOARD->Picture_Control_State[i][j];
	G_BOARD->Picture_Control_State[i][j] = 9;
	cout<<G_BOARD->Picture_Control_State[i][j];
	}*/

	//AfxMessageBox(TEXT("�������ʧ��!"));
}

void Control_Center::Monitor_2(LPVOID param)
{
	while(!G_BOARD->AI_Start_1 )	//�ȴ�����һ��ʼ���
	{
		Sleep(100);
	}

	//AI_2_Readiness = false;	//��ԭ���������״̬����Ϸ������Ϸ���

	clock_t clock_Begin;	//��¼��ʼʱ��
	clock_Begin = clock();
	CString text;	//��¼����״̬
	int Init = 0;
	CString	exX;
	CString exY;
	bool ifNewGame = 0;	//��¼�Ƿ�Ϊ����Ϸ
	if(s_pEngine_2)	//���������������
	{}
	bool PreInBoard = 0;//
	bool doNewGame = 0;//

	//while(G_BOARD->NewGame)
	//{
	//	if(isNewGame())
	//	{
	//		G_BOARD->NewGame = false;	//����������Ϸ
	//		s_pEditEngine->SetWindowTextW(s_pEngine->inBoard());
	//		break;
	//	}
	//	else
	//	{
	//		break;
	//	}
	//}
	//��������
	for(int i=1;G_BOARD->AI_Start_2;i++)
	{
		if(G_BOARD->Restart_Game)
		{
			Stop_Monitor();	
			AI_2_Readiness = false;
			Engine2_End = true;
			//G_BOARD->Restart_Game = false;
			/*s_pEngine_2->inEND();*/
			break;
		}
		else
		{
			if (isNewGame())
			{
				//s_pEngine_2->inRESTART();
				text.Append(L"����Ϸ��ʼ��\r\n");
				ifNewGame = 1;
			}

			if(G_BOARD->isEngine_2_Turn)
			{
				text.Append(L"�ֵ��ҷ����ӣ�\r\n");
				G_BOARD->isEngine_2_Turn = false;
				s_pEditEngine_2->SetWindowTextW(s_pEngine_2->inTURN(G_BOARD->last_X, G_BOARD->last_Y));
			}
		}
		Sleep(10);
	}
	//AI_2_Readiness = false;
	//G_BOARD->Restart_Game = false;

}

void Control_Center::Stop_Monitor()
{
	//Control_Center::AI_Start_1 = false;
	//Control_Center::AI_Start_2 = false;
	G_BOARD->AI_Start_1 = false;
	G_BOARD->AI_Start_2	= false;
	s_pEngine->Close();
	//_endthreadex(NULL);
	//AfxMessageBox(TEXT("������ֹͣ���!"));
}

bool Control_Center::InitAI(CString Path)
{
	if(s_pEngine)
	{
		delete s_pEngine;
		s_pEngine = nullptr;
	}
	s_pEngine = new Command();
	s_pEngine->Open(Path,s_pEditEngine);
	return s_pEngine->m_nStatus;
}

bool Control_Center::InitAI_2(CString Path)
{
	if(s_pEngine_2)
	{
		delete s_pEngine_2;
		s_pEngine_2 = nullptr;
	}
	s_pEngine_2 = new Command();
	s_pEngine_2->Open(Path,s_pEditEngine_2);
	return s_pEngine_2->m_nStatus;
}

bool Control_Center::isNewGame()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (G_BOARD->Picture_Control_State[i][j] != 0)
			{
				return false;
			}
		}
	}
	return true;
}