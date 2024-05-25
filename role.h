#ifndef _ROLE_H
#define _ROLE_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

/*�û���ɫ����ͷ�ļ�*/
enum Role{
	ADMINISTRATOR=0,
	STUDENT,
	TEACHER,
	ROLE_MAX,
};

const char *roleStr[]={"����Ա","ѧ��","��ʦ","�˳�"};

enum LoginChoice{
	LOGIN=0,
	LOGIN_MAX,
};

const char *loginStr[]={"��½","������һ��"};

//���ݲ���ö�� 
enum OPERATION{
	CREATE=0,//�� 
	DEL,//ɾ 
	UPDATE,//�� 
	RETRIEVE,//�� 
	OP_MAX,
};

//�������ַ��� 
const char *operationStr[]={"����","ɾ��","�޸�","��ѯ","������һ��"};

//��½��ೢ�Դ��� 
#define LOGIN_RETRY_MAX  5

//��ӡ�ַ���� 
#define PRINT_WIDTH  		8
#define PRINT_LONG_WIDTH  		16

//�����ʦ����
#define TEACHER_NUMBER_MAX  100 

//��տ���̨
void clear(){
	system("cls");
}

int getChoice(const char* promptStr, const char **choiceStr, const int choiceMax){
	int choice = -1;
	//��choiceMax���û�����ѡ���˳�/���ص���һ�� 
	while(choice > choiceMax || choice < 0){
		cout << promptStr <<endl;
		for(int i=0;i<=choiceMax;i++){
			cout << i << ". " << choiceStr[i] << endl;
		}
		cin >> choice;
		
		//�������������ʱ����������α���int����������char���͵��ַ�����ʱfailbit��ֵ����0��Ϊ1
		if(cin.fail()==true){
			//������ַ��Ῠ�����뻺�������º����޷������������
			cout << "������Ϸ��ַ�!" << endl;
			
			//��������ʹ��cin>>clear()��falibit��Ϊ0����������������������Ȼ��ʹignore()ȡ�����������ַ�������һ�ε���������������С�
			cin.clear();
			cin.ignore();
			choice = -1;
		}
	}
	
	return choice;
}

#endif
