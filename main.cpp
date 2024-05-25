#ifndef INCLUDE_MENU
#include "menu.h"
#endif

int main(int argc, char** argv) {
	bool exitSystem = false; 
	
	//���ñ��� 
	setTitle(); 

	//����ϵͳ��Ϣ
	loadInfo();
	 
	while(!exitSystem){
		Role role = ROLE_MAX;
		//��ȡ�û���� 
		role = greeting();
	
		
		//ȷ����ݲ�������ݲ�ͬ��½��ͬ�Ľ��� 
		if(role == ADMINISTRATOR){
			g_admin.process();
		}else if(role == TEACHER){
			if(!g_teacherList.empty()){
				if(g_teacherList[0].login()){
					cout << "��½�ɹ�" << endl;
				}
			}
		}else{
			exitSystem = true;
		}
	
		//�洢��Ϣ���ⲿ�ļ�
		storeInfo();
		
	} 
	return 0;
}
