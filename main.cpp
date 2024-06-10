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

//ϵͳ�źŹ���
BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
        // CTRL-CLOSE: �رմ���ʱ�洢��ǰ��Ϣ���ⲿ�ļ�,���˳�ϵͳ 
	    case CTRL_CLOSE_EVENT:
	        Beep(600, 200);
	        
	        //�洢��Ϣ���ⲿ�ļ�
			storeInfo();
			Sleep(1000);
	        return TRUE;
	
	    default:
	        return FALSE;
    }
}


int main(int argc, char** argv) {
	bool exitSystem = false; 
        	
	//���ñ��� 
	setTitle(); 
	 
	if (SetConsoleCtrlHandler(CtrlHandler, TRUE))
    {
    	loadInfo();	//����ϵͳ��Ϣ	
    	
        while(greeting()){
        		
			int role = -1;
			//��ȡ�û���� 
			while(Global::ROLE_MAX != role){
				role = getRole();
	
				//ȷ����ݲ�������ݲ�ͬ��½��ͬ�Ľ��� 
				if(role == Global::ADMINISTRATOR){
					Administrator::process();
				}else if(role == Global::TEACHER){
					Teacher::process();
				}else if(role == Global::STUDENT){
					Student::process();
				}	
			}
		} 
			
			
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
