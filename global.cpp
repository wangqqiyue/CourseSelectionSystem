#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif


int Global::LOGIN_RETRY_MAX=5;
int Global::PRINT_WIDTH=10;
int Global::PRINT_LONG_WIDTH=16;

int Global::TEACHER_NUMBER_MAX=100;
int Global::ROOM_NUMBER_MAX=100;
int Global::COURSE_NUMBER_MAX=100;
int Global::COURSE_PRICE_MAX=3000;
int Global::COURSE_CAPACITY_MAX=200;
int Global::COURSE_CAPACITY_MIN=20;

const char *Global::roleStr[]={"����Ա","ѧ��","��ʦ","�˳�"};
const char *Global::loginStr[]={"��½","������һ��"};
const char *Global::operationStr[]={"����","ɾ��","�޸�","��ѯ","������һ��"};
const char *Global::mgmtStr[]={"�����ʦ��Ϣ","���������Ϣ","����γ���Ϣ","������һ��"};
const char *Global::titleStr="��ѵ���Ĺ���ϵͳ";

//��տ���̨
void clear(){
	system("cls");
}

//���ÿ���̨���� 
void setTitle() {
	SetConsoleTitle(Global::titleStr);
}

//ͳһ�Ļ�ӭ����,��ȡ�û���� 
Global::Role greeting(){
	int role = -1;
	clear(); 
	cout << "-----���˵�-----"<< endl;
	cout << "��ӭʹ��" << Global::titleStr << endl;

	role = getChoice("��������ǣ�",Global::roleStr,Global::ROLE_MAX);
	return (Global::Role)role;
}


//��������Ƿ�Ϲ� 
bool isInputOk(){
	//�������������ʱ����������α���int����������char���͵��ַ�����ʱfailbit��ֵ����0��Ϊ1
	if(cin.fail()){
		//������ַ��Ῠ�����뻺�������º����޷������������
		cout << "������Ϸ��ַ�!" << endl;
		
		//��������ʹ��cin>>clear()��falibit��Ϊ0����������������������Ȼ��ʹignore()ȡ�����������ַ�������һ�ε���������������С�
		cin.clear();
		cin.ignore();
		return false;
	}
	return true;
}

//��ȡ�û������ѡ�� 
int getChoice(const char* promptStr, const char **choiceStr, const int choiceMax){
	int choice = -1;
	//��choiceMax���û�����ѡ���˳�/���ص���һ�� 
	while(choice > choiceMax || choice < 0){
		choice = -1;
		cout << promptStr <<endl;
		for(int i=0;i<=choiceMax;i++){
			cout << i << ". " << choiceStr[i] << endl;
		}
		cin >> choice;
		
		if(!isInputOk()){
			choice = -1;
		}
	}
	
	return choice;
}
