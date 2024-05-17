#include "menu.h"

int main(int argc, char** argv) {
	Role role = ROLE_MAX;
	
	//���ñ��� 
	setTitle(); 

	//����ϵͳ��Ϣ
	loadInfo();
	 
	//��ȡ�û���� 
	role = greeting();
	
	//ȷ����ݲ�������ݲ�ͬ��½��ͬ�Ľ��� 
	clear();
	if(role == ADMINISTRATOR){
		g_admin.process();
	}else if(role == TEACHER){
		if(!g_teacherList.empty()){
			if(g_teacherList[0].login()){
				cout << "��½�ɹ�" << endl;
			}
		}
	}

	//�洢��Ϣ���ⲿ�ļ�
	storeInfo();
	 
	return 0;
}
