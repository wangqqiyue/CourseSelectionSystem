#ifndef _ROLE_H
#define _ROLE_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/*�û���ɫ����ͷ�ļ�*/
enum Role{
	ADMINISTRATOR=0,
	STUDENT,
	TEACHER,
	ROLE_MAX,
};

const char *roleStr[]={"����Ա","ѧ��","��ʦ"};

//��½��ೢ�Դ��� 
#define LOGIN_RETRY_MAX  5

//��ӡ�ַ���� 
#define PRINT_WIDTH  		8

//�����ʦ����
#define TEACHER_NUMBER_MAX  100 

//��տ���̨
void clear(){
	system("cls");
}


#endif
