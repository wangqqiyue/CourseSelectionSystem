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

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
        // Handle the CTRL-C signal.
    case CTRL_C_EVENT:
        printf("Ctrl-C event\n\n");
        Beep(750, 300);
        return TRUE;

        // CTRL-CLOSE: confirm that the user wants to exit.
    case CTRL_CLOSE_EVENT:
        Beep(600, 200);
        printf("Ctrl-Close event\n\n");
        
        //�洢��Ϣ���ⲿ�ļ�
		storeInfo();
		Sleep(2000);
        return TRUE;

        // Pass other signals to the next handler.
    case CTRL_BREAK_EVENT:
        Beep(900, 200);
        printf("Ctrl-Break event\n\n");
        return FALSE;

    case CTRL_LOGOFF_EVENT:
        Beep(1000, 200);
        printf("Ctrl-Logoff event\n\n");
        return FALSE;

    case CTRL_SHUTDOWN_EVENT:
        Beep(750, 500);
        printf("Ctrl-Shutdown event\n\n");
        return FALSE;

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
		//����ϵͳ��Ϣ
		loadInfo();
        while(!exitSystem){
			Global::Role role = Global::ROLE_MAX;
			//��ȡ�û���� 
			role = greeting();

			//ȷ����ݲ�������ݲ�ͬ��½��ͬ�Ľ��� 
			if(role == Global::ADMINISTRATOR){
				Administrator::process();
			}else if(role == Global::TEACHER){
				Teacher::process();
			}else if(role == Global::STUDENT){
				Student::process();
			}else{
				exitSystem = true;
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
