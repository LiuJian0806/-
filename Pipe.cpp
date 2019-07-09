#include "StdAfx.h"
#include "Pipe.h"

inline void ParsePath(char *szDir, char *szFile, const char *szPath) 
{
	char *lpSeperator;
	strcpy(szDir, szPath);
	lpSeperator = strrchr(szDir, PATH_SEPERATOR);
	if (lpSeperator == NULL) {
		szDir[0] = '\0';
		strcpy(szFile, szPath);
	}
	else {
		*lpSeperator = '\0';
		strcpy(szFile, lpSeperator + 1);
	}
}
/*

#ifdef PIPE_DLL

extern "C" __declspec(dllexport) VOID WINAPI PipeOpen(CPipe *lppipe, LPCSTR szProcFile);
extern "C" __declspec(dllexport) VOID WINAPI PipeClose(CPipe *lppipe);
extern "C" __declspec(dllexport) LPSTR WINAPI PipeLineInput(CPipe *lppipe);
extern "C" __declspec(dllexport) VOID WINAPI PipeLineOutput(CPipe *lppipe, LPCSTR szLineStr);

VOID WINAPI PipeOpen(CPipe *lppipe, LPCSTR szProcFile) {
lppipe->Open(szProcFile);
}

VOID WINAPI PipeClose(CPipe *lppipe) {
lppipe->Close();
}

LPSTR WINAPI PipeLineInput(CPipe *lppipe) {
static char szBuffer[LINE_INPUT_MAX_CHAR];
if (lppipe->LineInput(szBuffer)) {
return szBuffer;
} else {
return NULL;
}
}

VOID WINAPI PipeLineOutput(CPipe *lppipe, LPCSTR szLineStr) {
lppipe->LineOutput(szLineStr);
}

#endif
*/

CPipe::CPipe(void)
{
}


CPipe::~CPipe(void)
{
}
//ʵ����·��ֵΪszProcFile�����棬����CreatePipe()��CreateProcess()����������pipeInAI(����ܵ�)�Լ�pipeFromAI������ܵ����������������ӽ��̡�
void CPipe::Open(const wchar_t *szProcFile) 
{
	DWORD dwMode;
	HANDLE hStdinRead, hStdinWrite, hStdoutRead, hStdoutWrite;
	SECURITY_ATTRIBUTES sa;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	if (!szProcFile) 
	{
		hInput = GetStdHandle(STD_INPUT_HANDLE);
		hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		bConsole = GetConsoleMode(hInput, &dwMode);
	}
	else 
	{
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.bInheritHandle = TRUE;
		sa.lpSecurityDescriptor = NULL;
		
		//�����ܵ�
		CreatePipe(&hStdinRead, &hStdinWrite, &sa, 0);
		CreatePipe(&hStdoutRead, &hStdoutWrite, &sa, 0);

		si.cb = sizeof(STARTUPINFO);
		si.lpReserved = si.lpDesktop = si.lpTitle = NULL;
		si.dwFlags = STARTF_USESTDHANDLES;
		si.cbReserved2 = 0;
		si.lpReserved2 = NULL;
		si.hStdInput = hStdinRead;
		si.hStdOutput = hStdoutWrite;
		si.hStdError = hStdoutWrite;
		//�����ӽ���
		CreateProcess(szProcFile, NULL, NULL, NULL, TRUE, DETACHED_PROCESS | CREATE_NEW_PROCESS_GROUP | IDLE_PRIORITY_CLASS, NULL, NULL, &si, &pi);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		CloseHandle(hStdinRead);
		CloseHandle(hStdoutWrite);
		hInput = hStdoutRead;
		hOutput = hStdinWrite;
		bConsole = FALSE;
	}
	if (bConsole) 
	{
		SetConsoleMode(hInput, dwMode & ~(ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT));
		FlushConsoleInputBuffer(hInput);
	}
	nBytesLeft = 0;
	nReadEnd = 0;
}
//�ر���open()�����д�����pipeInAI��pipeFromAI�ܵ�
void CPipe::Close(void) const 
{
	CloseHandle(hInput);
	CloseHandle(hOutput);
}
//��ȡpipeFromAI������������
void CPipe::ReadInput(void) 
{
	DWORD dwBytes;
	ReadFile(hInput, szBuffer + nReadEnd, LINE_INPUT_MAX_CHAR - nReadEnd, &dwBytes, NULL);
	nReadEnd += dwBytes;
	if (nBytesLeft > 0) 
	{
		nBytesLeft -= dwBytes;
	}
}
//���pipeFromAI�����Ƿ��ȡ���
bool CPipe::CheckInput(void) 
{
	DWORD dwEvents, dwBytes;
	if (bConsole) 
	{ // a tty, or an un-redirected handle
		GetNumberOfConsoleInputEvents(hInput, &dwEvents);
		return dwEvents > 1;
	}
	else if (nBytesLeft > 0) 
	{ // a pipe with remainder data
		return true;
	}
	else if (PeekNamedPipe(hInput, NULL, 0, NULL, &dwBytes, NULL)) 
	{ // a pipe without remainder data 
		nBytesLeft = dwBytes;
		return nBytesLeft > 0;
	}
	else 
	{ // a file, always true
		return true;
	}
}
//���pipeFromAI��pipeFromAI�Ƿ�������Ҫ���������о͵���readInput()��ȡ�������
void CPipe::LineOutput(const char *szLineStr) const 
{
	DWORD dwBytes;
	int nStrLen;
	char szWriteBuffer[LINE_INPUT_MAX_CHAR];
	nStrLen = strlen(szLineStr);
	memcpy(szWriteBuffer, szLineStr, nStrLen);
	szWriteBuffer[nStrLen] = '\r';
	szWriteBuffer[nStrLen + 1] = '\n';
	WriteFile(hOutput, szWriteBuffer, nStrLen + 2, &dwBytes, NULL);
}

//��ȡ������������
bool CPipe::GetBuffer(char *szLineStr) 
{
	char *lpFeedEnd;
	int nFeedEnd;
	lpFeedEnd = (char *)memchr(szBuffer, '\n', nReadEnd);
	if (lpFeedEnd == NULL) 
	{
		return false;
	}
	else 
	{
		nFeedEnd = lpFeedEnd - szBuffer;
		memcpy(szLineStr, szBuffer, nFeedEnd);
		szLineStr[nFeedEnd] = '\0';
		nFeedEnd++;
		nReadEnd -= nFeedEnd;
		memcpy(szBuffer, szBuffer + nFeedEnd, nReadEnd);
		lpFeedEnd = (char *)strchr(szLineStr, '\r');
		if (lpFeedEnd != NULL) 
		{
			*lpFeedEnd = '\0';
		}
		return true;
	}
}
//ͨ���ܵ�������˷���ָ��
bool CPipe::LineInput(char *szLineStr) 
{
	if (GetBuffer(szLineStr)) 
	{
		return true;
	}
	else if (CheckInput()) 
	{
		ReadInput();
		if (GetBuffer(szLineStr)) 
		{
			return true;
		}
		else if (nReadEnd == LINE_INPUT_MAX_CHAR) 
		{
			memcpy(szLineStr, szBuffer, LINE_INPUT_MAX_CHAR - 1);
			szLineStr[LINE_INPUT_MAX_CHAR - 1] = '\0';
			szBuffer[0] = szBuffer[LINE_INPUT_MAX_CHAR - 1];
			nReadEnd = 1;
			return true;
		}
		else 
		{
			return false;
		}
	}
	else 
	{
		return false;
	}
}