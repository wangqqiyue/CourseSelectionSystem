/*�˵��ͽ����ʽͷ�ļ�*/
#include <windows.h>
#include "course.h"
#include "administrator.h"
#include "student.h"
#include "teacher.h"
#include <sstream>
#include <fstream>

const char *titleStr="��ѵ���Ĺ���ϵͳ";


//���ÿ���̨���� 
void setTitle() {
	SetConsoleTitle(titleStr);
}

//ͳһ�Ļ�ӭ����,��ȡ�û���� 
Role greeting(){
	int role = ROLE_MAX;
	cout << "----��ӭʹ��----" << titleStr << endl;
	cout << endl;
	while(role >= ROLE_MAX || role < 0){
		cout << "��������ǣ�";
		for(int i=0;i<ROLE_MAX;i++){
			cout << i << ". " << roleStr[i] << endl;
		}
		cin >> role;
	}
	return (Role)role;
}

//��Ϣ���� 
void loadInfo(){
	ifstream in;
	string temp;
	string account,password;
	
	int i=0;
	
	//���ع���Ա�˺�����
	in.open("administrator.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		stringstream ss(temp);
		ss >> account;
		ss >> password;
		g_admin.loadAccount(account,password);
	}
	in.close();
	
	//���ؽ�ʦ��Ϣ 
	in.open("teachersInfo.txt",ios::in);
	//һ���ж�ȡ��Ϣ�����ָֵ 
	getline(in,temp);
	while(getline(in,temp)){
		stringstream ss(temp);
		ss >> g_teacherList[i].teacherId;
		ss >> g_teacherList[i].name;
		ss >> g_teacherList[i].password;
		i++;
		if(i>=TEACHER_NUMBER_MAX){
			cout << "��ȡ�Ľ�ʦ��Ϣ�Ѵﵽ����" << TEACHER_NUMBER_MAX << "����ֹͣ����." << endl;
			break;
		}
	}
	
	in.close();
}


//��Ϣ���� 
void storeInfo(){
	ofstream out;

	//���ع���Ա�˺�����
	out.open("administrator.txt",ios::out);
	out << "�˺�" << setw(PRINT_WIDTH) << "����" << endl;
	out << g_admin.adminAccount << setw(PRINT_WIDTH) << g_admin.password << endl;
	out.close();
	
}


