#ifndef INCLUDE_RECORD_PROCESS
#include "recordProcess.h"
#endif

int main(int argc, char** argv) {
	 
	if (SetConsoleCtrlHandler(CtrlHandler, TRUE))
    {
    	loadInfo();	//����ϵͳ��Ϣ	
    	
        mainLoop(); //��ѭ�� 
	
		//�洢��Ϣ���ⲿ�ļ�
		storeInfo();		
		
		return 0;
    }
	else
    {
        printf("\nERROR: Could not set control handler");
        return 1;
    }
    return 0;
    
}
