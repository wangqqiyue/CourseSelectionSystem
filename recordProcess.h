#ifndef INCLUDE_RECORD_PROCESS
#define INCLUDE_RECORD_PROCESS


#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

/*
记录处理组件
进行各项数据记录的处理
包括导入记录、载入记录
*/


/*--------------------------------------文件操作--------------------------------------------------------*/
//信息加载 
void loadInfo();

//信息存储
void storeInfo();

//主循环 
void mainLoop();

//系统信号钩子
BOOL WINAPI CtrlHandler(DWORD fdwCtrlType);

//设置控制台标题 
void setTitle();

//统一的欢迎界面
bool greeting();

//打印帮助信息 
bool printAboutInfo();

#endif
