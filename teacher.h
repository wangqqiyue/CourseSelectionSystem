#ifndef _TEACHER_H
#define _TEACHER_H

#include "role.h"

//��ʦ ���˺����� 
/*
���ܣ��鿴�Լ��Ŀγ���Ϣ��ѧԱ����
		 

*/ 
class Teacher{
public:
	int teacherId;
	string name;
	string password;
	Teacher(int id,string name,string passwd);
	bool login();
};
vector<Teacher> g_teacherList;


Teacher::Teacher(int id,string name,string passwd){
	this->teacherId=id;
	this->name=name;
	this->password=passwd;
}

bool Teacher::login(){
	int id;
	string inputPasswd;
	clear();
	cout << "------��ʦ��½-----" << endl;
	for(int j=0;j<LOGIN_RETRY_MAX;j++){
		cout << "�������ʦ�ʺţ�����ʦ��ţ�:" ;
		cin >> id;
		
		//�ڽ�ʦ��������ұ��ΪinpuAccount��Ԫ��
		vector<Teacher>::iterator i;

		for(i=g_teacherList.begin();i!=g_teacherList.end();++i){
			if(i->teacherId == id){
				break;
			}
		}
		if(i == g_teacherList.end()){
			cout << "�˺Ų�����!����������"  << endl;
			continue;
		}
		
		cout << "����������:" ;
		cin >> inputPasswd;

		if(inputPasswd != i->password){
			cout << "�������!����������"  << endl;
			continue;
		}
		return true;
	}
	
	cout << "��½��������" << LOGIN_RETRY_MAX << endl; 
	cout << "���˳�" << endl;
	return false;
}



#endif 
