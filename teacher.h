#ifndef INCLUDE_TEACHER
#define INCLUDE_TEACHER

#ifndef INCLUDE_ROLE
#include "role.h"
#endif

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
	static bool login();
};
vector<Teacher> g_teacherList;


Teacher::Teacher(int id,string name,string passwd){
	this->teacherId=id;
	this->name=name;
	this->password=passwd;
}
//��̬�����Ķ��� 
bool Teacher::login(){
	int id;
	string inputPasswd;
	//�ڽ�ʦ��������ұ��ΪinpuAccount��Ԫ��
	vector<Teacher>::iterator i;
	
	clear();
	cout << "------��ʦ��½-----" << endl;
	int loginChoice = getChoice("", loginStr, LOGIN_MAX);
	if(LOGIN_MAX == loginChoice){
		return false;
	} 
	
	
	for(int j=0;j<Global::LOGIN_RETRY_MAX;j++){

		cout << "�������ʦ�ʺţ�����ʦ��ţ�:" ;
		cin >> id;
		if(!isInputOk()){
			continue;
		}
		
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
	
	cout << "��½��������" << Global::LOGIN_RETRY_MAX << endl; 
	cout << "���˳�" << endl;
	return false;
}



#endif 
