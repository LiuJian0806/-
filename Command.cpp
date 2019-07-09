#include "StdAfx.h"
#include "Command.h"
#include "atlconv.h"
#include "resource.h"


Command::Command()
{
	m_pPipe = new CPipe();
	m_nThreads = 0;
	m_nPriority = 4;

	m_nTime = 3000;
	m_pcName = nullptr;
	m_pcVersion = nullptr;
	m_pcCopyright = nullptr;
	m_pcAuthor = nullptr;
	m_pcCountry = nullptr;
	m_pcWebsite = nullptr;
	m_pcEmail = nullptr;
	m_nStatus = IDLE_UNLOAD;
	m_strGo = L"go time 3000";
}


Command::~Command()
{
	if (m_nStatus > IDLE_UNLOAD)
	{
		// 引擎未关闭
		Close();
	}
	delete m_pPipe;
	delete[] m_pcName;
	delete[] m_pcVersion;
	delete[] m_pcCopyright;
	delete[] m_pcAuthor;
	delete[] m_pcCountry;
	delete[] m_pcWebsite;
	delete[] m_pcEmail;
}
CEdit *Command::s_pEditEngine(nullptr);
CEdit *Command::s_pEditEngine_2(nullptr);

// 通过管道向引擎端发送指令，同时将发送的指令记录到引擎交互指令界面
void Command::Send(const char * pcLineStr)
{
	CString text(pcLineStr);
	int len;
	m_pPipe->LineOutput(pcLineStr);
	len = s_pEditEngine->GetWindowTextLength();
	s_pEditEngine->SetSel(len, len);
	s_pEditEngine->ScrollWindow(0, 0);
	s_pEditEngine->ReplaceSel(text);
}

void Command::Send_2(const char * pcLineStr)
{
	CString text(pcLineStr);
	int len;
	m_pPipe->LineOutput(pcLineStr);
	len = s_pEditEngine_2->GetWindowTextLength();
	s_pEditEngine_2->SetSel(len, len);
	s_pEditEngine_2->ScrollWindow(0, 0);
	s_pEditEngine_2->ReplaceSel(text);
}



// 判断引擎是否返回了一条指令，是则返回true，否则返回false
bool Command::Receive(void)
{
	char gcBuffer[LINE_INPUT_MAX_CHAR];
	if (m_nStatus == IDLE_UNLOAD)
	{
		return false;
	}
	if (!m_pPipe->LineInput(gcBuffer))
	{
		return false;
	}
	return true;
}


// 加载引擎，向引擎发送“START”指令以及“ABOUT”，若在规定时间内收到返回信息则将收到的指令返回，否则返回加载失败。
CString Command::Init()
{
	char gcBuffer[LINE_INPUT_MAX_CHAR]="";
	//Send("ABOUT\r\n");
	Send("START 15\r\n");

#pragma region 解析返回信息
	clock_t clockTime = clock();
	size_t len;
	CString text;
	while (m_nStatus == IDLE_UNLOAD)
	{
		if (m_pPipe->LineInput(gcBuffer))
		{
			/*if (!_memicmp(gcBuffer, "name=", 5))
			{
				if (m_pcName)
				{
					delete[] m_pcName;
				}
				len = strlen(gcBuffer);
				m_pcName = new char[len - 4];
				memcpy(m_pcName, gcBuffer + 5, len - 4);
			}
			else if (!_memicmp(gcBuffer, "version=", 8))
			{
				if (m_pcVersion)
				{
					delete[] m_pcVersion;
				}
				len = strlen(gcBuffer);
				m_pcVersion = new char[len - 7];
				memcpy(m_pcVersion, gcBuffer + 8, len - 7);
			}
			else if (!_memicmp(gcBuffer, "author=", 7))
			{
				if (m_pcAuthor)
				{
					delete[] m_pcAuthor;
				}
				len = strlen(gcBuffer);
				m_pcAuthor = new char[len - 6];
				memcpy(m_pcAuthor, gcBuffer + 7, len - 6);
			}
			else if (!_memicmp(gcBuffer, "country=", 8))
			{
				if (m_pcAuthor)
				{
					delete[] m_pcAuthor;
				}
				len = strlen(gcBuffer);
				m_pcCountry = new char[len - 7];
				memcpy(m_pcAuthor, gcBuffer + 8, len - 7);
			}
			else if (!_memicmp(gcBuffer, "www=", 4))
			{
				if (m_pcAuthor)
				{
					delete[] m_pcAuthor;
				}
				len = strlen(gcBuffer);
				m_pcWebsite = new char[len - 3];
				memcpy(m_pcAuthor, gcBuffer + 4, len - 3);
			}
			else if (!_memicmp(gcBuffer, "www=", 4))
			{
				if (m_pcAuthor)
				{
					delete[] m_pcAuthor;
				}
				len = strlen(gcBuffer);
				m_pcWebsite = new char[len - 3];
				memcpy(m_pcAuthor, gcBuffer + 4, len - 3);
			}
			else if (!_memicmp(gcBuffer, "email=", 6))
			{
				if (m_pcAuthor)
				{
					delete[] m_pcAuthor;
				}
				len = strlen(gcBuffer);
				m_pcEmail = new char[len - 5];
				memcpy(m_pcAuthor, gcBuffer + 6, len - 5);
			}*/
			if (!_memicmp(gcBuffer, "OK", 2))
			{
				sendPreSetINFO();
				m_nStatus = IDLE_READY;
				text = gcBuffer;
				return text;
			}
		}
		else
		{
			Sleep(1);
			// 发送ucci指令后1秒内如果没有返回OK信息，则当成加载失败
			if (clock() - clockTime > 1000)
			{
				text = "Time Out";
				return text;
				break;
			}
		}
	}
#pragma endregion 解析返回信息
}



// 中止引擎思考
void Command::Stop(void)
{
	int nOldStatus;
	clock_t clockTime;
	//Send("stop");
	clockTime = clock();
	nOldStatus = m_nStatus;
	while (m_nStatus == nOldStatus)
	{
		if (!Receive())
		{
			Sleep(1);
			if (clock() - clockTime > 100)
			{
				break;
			}
		}
	}
	if (m_nStatus == nOldStatus)
	{
		m_nStatus = IDLE_READY;
	}
}


// 将引擎状态为处理信息中或者准备就绪
void Command::Idle(void)
{
	if (m_nStatus > BUSY_WAIT)
	{
		m_nStatus = BUSY_WAIT;
		Stop();
	}
	m_nStatus = IDLE_READY;
}





// 打开地址值为strEngineFile的引擎，并将结果（引擎加载成功/失败）返回给_outputEngine文本框。
void Command::Open(CString strEngineFile, CEdit *_outputEngine)
{
	s_pEditEngine = _outputEngine;	//同步set-command下引擎状态框信息
	if (m_nStatus > IDLE_UNLOAD)	//m_nStatus:引擎状态，初始值为0
	{
		// 引擎已加载，先关闭原有的引擎
		Close();
	}
	if (strEngineFile == L"")	//文件路径为空
	{
		// 引擎文件地址不存在
		AfxMessageBox(TEXT("引擎地址不存在!"));
		return;
	}
	m_strEngineFile = strEngineFile;
	m_pPipe->Open(m_strEngineFile.GetBuffer());	//为选择路径下引擎开辟进程
	Init();
}


// 向引擎发送“END指令”，关闭管道，并将引擎状态切换为“未加载”
void Command::Close(void)
{
	Idle();
	Send("END");
	m_pPipe->Close();
	m_nStatus = IDLE_UNLOAD;
}







//通用协议中的BEGIN指令，向引擎发送“BEGIN”指令，并检测是否为自动下棋模式，
//若是则将等待引擎返回正确信息后调用putpiece()方法，并返回引擎输出结果；若引擎未能在规定时间内返回正确信息，则返回“time out”
CString Command::inBEGIN()
{
	//检测是否自动下子
	/*if (BST_CHECKED == IsDlgButtonChecked((HWND)IDD_MY_DIALOG,IDC_CHECK1))
	{
		AutoPlay = 1;
	}
	else
	{
		AutoPlay = 0;
	}*/
	clock_t clockTime = clock();
	int x, y;
	bool isdown = 0;
	CString text;
	char gcBuffer[LINE_INPUT_MAX_CHAR] = "";
	Send("BEGIN\r\n");
	while (!isdown)
	{
		m_pPipe->LineInput(gcBuffer);
		if (sscanf(gcBuffer,"%d,%d", &x, &y) == 2)
		{			
			isdown = 1;
			text = gcBuffer;
//			if (AutoPlay)
//			{
			//pChess->PutPiece(x, y);
			G_BOARD->Set_Chess(x,y);
//			}
			return text;
		}
		else
		{
			Sleep(1);
			if (clock() - clockTime > 1000)
			{
				text = "Time Out";
				return text;
				break;
			}
		}
	}
}

//通用协议中的BOARD指令，向引擎发送“BOARD”指令,将m_gChessboard[i][j]中的棋盘信息转换为“BOARD”指令的格式，
//整个棋盘发送完毕后发送“DONE”指令，并检测是否为自动下棋模式，若是则将等待引擎返回正确信息后调用putpiece()方法，
//并返回引擎输出结果；若引擎未能在规定时间内返回正确信息，则返回“time out”
CString Command::inBoard()
{

	char gcBuffer[LINE_INPUT_MAX_CHAR] = "";
	clock_t clockTime = clock();
	bool myColor = 0;//白色;
	CString text;
	Send("BOARD\r\n");
	m_pPipe->LineInput(gcBuffer);
	CString CSi;
	CString CSj;
	/*if (pChess->isBlack == 1)
	{
		myColor = 1;
	}
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (pChess->m_gChessboard[i][j] !=0 )
			{
				CString text = nullptr;
				if (pChess->m_gChessboard[i][j] == 1)
				{
					CSi.Format(_T("%d"), i);
					CSj.Format(_T("%d"), j);
					text.Append(CSi);
					text.Append(L",");
					text.Append(CSj);
					text.Append(L",");
					if (pChess->isBlack)
					{
						text.Append(L"1\r\n");
					}
					else
					{
						text.Append(L"2\r\n");
					}
				}
				if (pChess->m_gChessboard[i][j] == 2)
				{
					CSi.Format(_T("%d"), i);
					CSj.Format(_T("%d"), j);
					text.Append(CSi);
					text.Append(L",");
					text.Append(CSj);
					text.Append(L",");
					if (!pChess->isBlack)
					{
						text.Append(L"1\r\n");
					}
					else
					{
						text.Append(L"2\r\n");
					}
				}
				USES_CONVERSION;
				char* p = T2A(text.GetBuffer(0));
				Send(p);
				m_pPipe->LineInput(gcBuffer);
			}
		}
	}*/
	Send("DONE\r\n");
	int x, y;
	bool isdown = 0;
	while (!isdown)
	{
		m_pPipe->LineInput(gcBuffer);
		if (sscanf(gcBuffer, "%d,%d", &x, &y) == 2)
		{

			isdown = 1;
			text = gcBuffer;
//			if (AutoPlay)
//			{
				//pChess->PutPiece(x, y);
			G_BOARD->Set_Chess(x,y);
//			}
			return text;
		}
	}
}

//预设引擎信息，向引擎发送预定义的设置信息，例如单步时长，总时长，游戏模式等。
void Command::sendPreSetINFO()
{
	Send("INFO timeout_match 600000\r\n");
	Send("INFO timeout_turn 6000\r\n");
	Send("INFO max_memory 83886080\r\n");
	Send("INFO game_type 0\r\n");
	Send("INFO rule 0\r\n");
}

//TURN指令，向引擎发送“TURN”指令，获取棋盘中的上一步棋并将其编码为 “TURN”指令的格式，
//并检测是否为自动下棋模式，若是则将等待引擎返回正确信息后调用putpiece()方法，并返回引擎输出结果；
//若引擎未能在规定时间内返回正确信息，则返回“time out”
CString Command::inTURN(int lastx, int lasty)
{
	/*if (BST_CHECKED == IsDlgButtonChecked((HWND)IDD_MY_DIALOG, IDC_CHECK1))
	{
		AutoPlay = 1;
	}
	else
	{
		AutoPlay = 0;
	}*/
	
	char gcBuffer[LINE_INPUT_MAX_CHAR] = "";
	clock_t clockTime = clock();
	CString text;
	CString inX, inY;
	inX.Format(_T("%d"), lastx);
	inY.Format(_T("%d"), lasty);
	text.Append(L"TURN");
	text.Append(L" ");
	text.Append(inX);
	text.Append(L",");
	text.Append(inY);
	text.Append(L"\r\n");
	USES_CONVERSION;
	char* p = T2A(text.GetBuffer(0));
	Send(p);
	int x, y;
	bool isdown = 0;
	while (!isdown)
	{
		m_pPipe->LineInput(gcBuffer);
		if (sscanf(gcBuffer, "%d,%d", &x, &y) == 2)
		{

			isdown = 1;
			text = gcBuffer;
//			if (AutoPlay)
//			{
			//pChess->PutPiece(x, y);
			G_BOARD->Set_Chess(x,y);
//			}
			return text;
		}
	}
}
 //END指令，向引擎发送“END”指令
void Command::inEND()
{
	Send("END\r\n");
}

//RESTART指令，向引擎发送“RESTART”指令
void Command::inRESTART()
{
	Send("RESTART\r\n");
}