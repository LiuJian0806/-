#include "Pipe.h"
#include "Board.h"
#pragma once
class Command
{
public:
	Command();
	~Command();

	// 引擎文件
	CString m_strEngineFile;
	// 引擎管道
	CPipe *m_pPipe;
	// 引擎使用的线程数	
	int m_nThreads;
	// 引擎优先级 0～3数值越大表示级别越高
	int m_nPriority;
	// 随机性 0～3数值越大表示随机性越大
	int m_nRandomness;
	// 风格 0-保守、1-均衡、2－冒进
	int m_nStyle;
	// 引擎思考的时间
	int m_nTime;
	// 引擎名称
	char *m_pcName;
	// 引擎版本
	char *m_pcVersion;
	// 引擎版权
	char *m_pcCopyright;
	// 引擎作者
	char *m_pcAuthor;
	// 引擎作者国籍
	char *m_pcCountry;
	// 引擎作者网站
	char *m_pcWebsite;
	// 引擎作者邮箱
	char *m_pcEmail;
	// 引擎状态
	int m_nStatus;
	// 后台思考完成的着法
	BYTE m_gcMove[4];
	// position字符串：“position {fen <FEN串> | startpos} [moves <后续着法列表>]”
	CString m_strPosition;
	// go字符串：“go time 5000”
	CString m_strGo;
	//记录引擎与客户端交互过程
	static CEdit *s_pEditEngine;
	static CEdit *s_pEditEngine_2;
private:
	// 向引擎发送指令
	void Send(const char * pcLineStr);
	void Send_2(const char *pcLineStr);
	// 在引擎思考时，接收并处理引擎反馈的信息
	bool Receive(void);
	// 初始化引擎
	CString Init();
	//让引擎思考
	void Run();
	// 中止引擎思考
	void Stop(void);
	// 让引擎空闲
	void Idle(void);
	// 设置引擎参数
	void SetOption(void);

public:
	// 打开引擎
	void Open(CString strEngineFile, CEdit *_outputEngine);
	// 关闭引擎
	void Close(void);
	// 设置单步思考时间
	void SetTime(int time);
	// 设置引擎
	void SetEngine(unsigned int setInt);
	//通用协议中的BOARD指令
	CString inBoard();
	//初始化引擎设置
	void sendPreSetINFO();
	//展示
	void ShowReceive();
	//BEGIN指令
	CString inBEGIN();
	//TURN指令
	CString inTURN(int lastx, int lasty);
	//END指令
	void inEND();
	//是否执行自动落子
	bool AutoPlay;
	//RESTART指令
	void inRESTART();
};


