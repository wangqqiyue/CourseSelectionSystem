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
	}

	//�洢��Ϣ���ⲿ�ļ�
	storeInfo();
	 
	return 0;
}
