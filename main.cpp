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


int main(int argc, char** argv) {
	bool exitSystem = false; 
	
	//���ñ��� 
	setTitle(); 

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
			if(login(Global::TEACHER)){
				cout << "��½�ɹ�" << endl;
				system("pause");
			}
			
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
