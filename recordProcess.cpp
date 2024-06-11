#ifndef INCLUDE_RECORD_PROCESS
#include "recordProcess.h" 
#endif

#ifndef INCLUDE_COURSE
#include "course.h"
#endif

#ifndef INCLUDE_ADMINISTATOR
#include "administrator.h"
#endif 

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif


#ifndef INCLUDE_SELECTION_TABLE
#include "selectionTable.h"
#endif

#ifndef INCLUDE_CLASSROOM
#include "classroom.h"
#endif


//��Ϣ���� 
void loadInfo(){
	cout << "ϵͳ���ݼ�����..." << endl;
	
	//���ع���Ա��Ϣ	
	Administrator::loadInfo();
	
	//���ؽ�ʦ��Ϣ 
	Teacher::loadInfo();
	
	//���ؿγ���Ϣ
	Course::loadInfo();
	
	//���ؽ�����Ϣ
	Classroom::loadInfo();
	
	//����ѧ����Ϣ
	Student::loadInfo();
	
	//����ѡ�α� 
	CourseSelectionTable::loadInfo();
	
	cout << "ϵͳ���ݼ������" << endl;
}


//��Ϣ�洢
void storeInfo(){
	cout << "ϵͳ���ݴ洢��..." << endl;

	//�洢����Ա��Ϣ 
	Administrator::storeInfo();
	
	//�洢��ʦ��Ϣ 
	Teacher::storeInfo();
	
	//�洢�γ���Ϣ 
	Course::storeInfo();
	
	//�洢������Ϣ 
	Classroom::storeInfo();
	
	//�洢������Ϣ 
	Student::storeInfo();
	
	//�洢ѡ�α���Ϣ 
	CourseSelectionTable::storeInfo();
	
	cout << "ϵͳ���ݴ洢���" << endl;
}

void mainLoop(){
	static bool firstRun = true;
	if(firstRun){
		//���ñ��� 
		setTitle(); 		
		firstRun = false;
	}

	
	while(greeting()){		 
		int role = -1;
		//������ȡ�û���� 
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
}

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


//���ÿ���̨���� 
void setTitle() {
	SetConsoleTitle(Global::titleStr);
}

//ͳһ�Ļ�ӭ����,��ȡ�û���� 
bool greeting(){
	int choice  = -1;
	clear(); 
	cout << "��ӭʹ��" << Global::titleStr << endl;
	choice = getChoice("��ѡ��",Global::greetingStr,Global::GREETING_MAX);
	clear();
	if(Global::GREETING_CONTINUE == choice){
		return true;
	}else if(Global::GREETING_ABOUT == choice){
		printAboutInfo();
		goContinue();
		return true;
	}else if(Global::GREETING_MAX == choice){
		return false;
	}	
}

//��ӡ������Ϣ 
bool printAboutInfo(){
	ifstream in;
	string line;
	
	//���ع�����Ϣ 
	in.open(Global::aboutInfoFile,ios::in);
	if(!in){
		return false;
	}

	while(getline(in,line)){
		cout << line << endl;
	}		
	in.close();	
	
	return true;
}

//ͳһ�Ļ�ӭ����,��ȡ�û���� 
Global::Role getRole(){
	int role = -1;
	clear(); 
	cout << "---------------�ÿ����ѡ��-----------------" << endl;
	role = getChoice("��������ǣ�",Global::roleStr,Global::ROLE_MAX);
	return (Global::Role)role;
}

