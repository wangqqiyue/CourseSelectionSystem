#ifndef INCLUDE_RECORD_PROCESS
#define INCLUDE_RECORD_PROCESS


#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

/*
��¼�������
���и������ݼ�¼�Ĵ���
���������¼�������¼
*/


/*--------------------------------------�ļ�����--------------------------------------------------------*/
//��Ϣ���� 
void loadInfo();

//��Ϣ�洢
void storeInfo();

//��ѭ�� 
void mainLoop();

//ϵͳ�źŹ���
BOOL WINAPI CtrlHandler(DWORD fdwCtrlType);

//���ÿ���̨���� 
void setTitle();

//ͳһ�Ļ�ӭ����
bool greeting();

//��ӡ������Ϣ 
bool printAboutInfo();

#endif
