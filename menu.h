/*�˵��ͽ����ʽͷ�ļ�*/
#include <windows.h>
#include <iostream>

#include "users.h"
#include "courses.h"


using namespace std;
const char *titleStr="��ѵ���Ĺ���ϵͳ";


//���ÿ���̨���� 
void setTitle() {
	SetConsoleTitle(titleStr);
}

//��տ���̨
void clear(){
	system("cls");
}

//ͳһ�Ļ�ӭ����,��ȡ�û���� 
Role greeting(){
	int role = ROLE_MAX;
	cout << "��ӭʹ��" << titleStr << endl;
	cout << endl;
	while(role >= ROLE_MAX || role < 0){
		cout << "��������ǣ�" << endl;
		for(int i=0;i<ROLE_MAX;i++){
			cout << i << ". " << roleStr[i] << endl;
		}
		cin >> role;
	}
	return (Role)role;
}



