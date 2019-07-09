#include "Pipe.h"
#include "Board.h"
#pragma once
class Command
{
public:
	Command();
	~Command();

	// �����ļ�
	CString m_strEngineFile;
	// ����ܵ�
	CPipe *m_pPipe;
	// ����ʹ�õ��߳���	
	int m_nThreads;
	// �������ȼ� 0��3��ֵԽ���ʾ����Խ��
	int m_nPriority;
	// ����� 0��3��ֵԽ���ʾ�����Խ��
	int m_nRandomness;
	// ��� 0-���ء�1-���⡢2��ð��
	int m_nStyle;
	// ����˼����ʱ��
	int m_nTime;
	// ��������
	char *m_pcName;
	// ����汾
	char *m_pcVersion;
	// �����Ȩ
	char *m_pcCopyright;
	// ��������
	char *m_pcAuthor;
	// �������߹���
	char *m_pcCountry;
	// ����������վ
	char *m_pcWebsite;
	// ������������
	char *m_pcEmail;
	// ����״̬
	int m_nStatus;
	// ��̨˼����ɵ��ŷ�
	BYTE m_gcMove[4];
	// position�ַ�������position {fen <FEN��> | startpos} [moves <�����ŷ��б�>]��
	CString m_strPosition;
	// go�ַ�������go time 5000��
	CString m_strGo;
	//��¼������ͻ��˽�������
	static CEdit *s_pEditEngine;
	static CEdit *s_pEditEngine_2;
private:
	// �����淢��ָ��
	void Send(const char * pcLineStr);
	void Send_2(const char *pcLineStr);
	// ������˼��ʱ�����ղ��������淴������Ϣ
	bool Receive(void);
	// ��ʼ������
	CString Init();
	//������˼��
	void Run();
	// ��ֹ����˼��
	void Stop(void);
	// ���������
	void Idle(void);
	// �����������
	void SetOption(void);

public:
	// ������
	void Open(CString strEngineFile, CEdit *_outputEngine);
	// �ر�����
	void Close(void);
	// ���õ���˼��ʱ��
	void SetTime(int time);
	// ��������
	void SetEngine(unsigned int setInt);
	//ͨ��Э���е�BOARDָ��
	CString inBoard();
	//��ʼ����������
	void sendPreSetINFO();
	//չʾ
	void ShowReceive();
	//BEGINָ��
	CString inBEGIN();
	//TURNָ��
	CString inTURN(int lastx, int lasty);
	//ENDָ��
	void inEND();
	//�Ƿ�ִ���Զ�����
	bool AutoPlay;
	//RESTARTָ��
	void inRESTART();
};


