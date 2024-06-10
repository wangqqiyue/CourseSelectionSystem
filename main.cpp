#ifndef INCLUDE_RECORD_PROCESS
#include "recordProcess.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_ADMINISTATOR
#include "administrator.h"
#endif

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif 

//系统信号钩子
BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
        // CTRL-CLOSE: 关闭窗口时存储当前信息到外部文件,再退出系统 
	    case CTRL_CLOSE_EVENT:
	        Beep(600, 200);
	        
	        //存储信息到外部文件
			storeInfo();
			Sleep(1000);
	        return TRUE;
	
	    default:
	        return FALSE;
    }
}


int main(int argc, char** argv) {
	bool exitSystem = false; 
        	
	//设置标题 
	setTitle(); 
	 
	if (SetConsoleCtrlHandler(CtrlHandler, TRUE))
    {
    	loadInfo();	//加载系统信息	
    	
        while(greeting()){
        		
			int role = -1;
			//获取用户身份 
			while(Global::ROLE_MAX != role){
				role = getRole();
	
				//确认身份并根据身份不同登陆不同的界面 
				if(role == Global::ADMINISTRATOR){
					Administrator::process();
				}else if(role == Global::TEACHER){
					Teacher::process();
				}else if(role == Global::STUDENT){
					Student::process();
				}	
			}
		} 
			
			
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
