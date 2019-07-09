/****全局变量和全局对象*****/
#include "stdafx.h"
#pragma once  
/****CPipe类中用到的常量******/
const int LINE_INPUT_MAX_CHAR = 4096;
const int PATH_MAX_CHAR = 1024;
const int PATH_SEPERATOR = '\\';


// 引擎状态
#define IDLE_UNLOAD		0	// 引擎未加载
#define IDLE_READY		1	// 引擎待命(如果轮到电脑走棋，那么引擎立即工作)
#define BUSY_WAIT		2	// 等待引擎停止思考
#define BUSY_THINK		3	// 引擎正常思考

// 设置参数
#define OPTION_NONE		0	// 无
#define OPTION_SMALL	1	// 小
#define OPTION_MEDIUM	2	// 中
#define OPTION_LARGE	3	// 大
#define OPTION_SOLID	0	// 保守
#define OPTION_NORMAL	1	// 均衡
#define OPTION_RISKY	2	// 冒进
