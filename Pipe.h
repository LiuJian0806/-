#pragma once
#include "stdafx.h"
#include "Global.h"


class CPipe
{
public:
	CPipe(void);
	~CPipe(void);


	HANDLE hInput, hOutput;
	BOOL bConsole;
	int nBytesLeft;

	int nReadEnd;
	char szBuffer[LINE_INPUT_MAX_CHAR];

	void Open(const wchar_t *szExecFile = nullptr);
	void Close(void) const;
	void ReadInput(void);
	bool CheckInput(void);
	bool GetBuffer(char *szLineStr);
	bool LineInput(char *szLineStr);
	void LineOutput(const char *szLineStr) const;
};
