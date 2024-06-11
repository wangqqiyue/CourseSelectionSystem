#ifndef INCLUDE_RECORD_PROCESS
#include "recordProcess.h"
#endif

int main(int argc, char** argv) {
	 
	if (SetConsoleCtrlHandler(CtrlHandler, TRUE))
    {
    	loadInfo();	//加载系统信息	
    	
        mainLoop(); //主循环 
	
		//存储信息到外部文件
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
