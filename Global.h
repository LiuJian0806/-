/****ȫ�ֱ�����ȫ�ֶ���*****/
#include "stdafx.h"
#pragma once  
/****CPipe�����õ��ĳ���******/
const int LINE_INPUT_MAX_CHAR = 4096;
const int PATH_MAX_CHAR = 1024;
const int PATH_SEPERATOR = '\\';


// ����״̬
#define IDLE_UNLOAD		0	// ����δ����
#define IDLE_READY		1	// �������(����ֵ��������壬��ô������������)
#define BUSY_WAIT		2	// �ȴ�����ֹͣ˼��
#define BUSY_THINK		3	// ��������˼��

// ���ò���
#define OPTION_NONE		0	// ��
#define OPTION_SMALL	1	// С
#define OPTION_MEDIUM	2	// ��
#define OPTION_LARGE	3	// ��
#define OPTION_SOLID	0	// ����
#define OPTION_NORMAL	1	// ����
#define OPTION_RISKY	2	// ð��
