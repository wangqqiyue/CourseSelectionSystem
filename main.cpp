#include "menu.h"

int main(int argc, char** argv) {
	Role role = ROLE_MAX;
	
	//���ñ��� 
	setTitle(); 

	//��ȡ�û���� 
	role = greeting();
	
	//ȷ����ݲ�������ݲ�ͬ��½��ͬ�Ľ��� 
	clear();
	cout << roleStr[role] << endl;

	return 0;
}
