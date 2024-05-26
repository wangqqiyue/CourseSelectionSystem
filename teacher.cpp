#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


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
	int loginChoice = getChoice("", Global::loginStr, Global::LOGIN_MAX);
	if(Global::LOGIN_MAX == loginChoice){
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

bool Teacher::recordToStream(ostream& out){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_WIDTH)<<"��ʦ���" << setw(Global::PRINT_LONG_WIDTH) << "��ʦ����" << setw(Global::PRINT_LONG_WIDTH) << "����"<< endl;
	for(vector<Teacher>::iterator i=g_teacherList.begin();i!=g_teacherList.end();i++){
		out <<  setw(Global::PRINT_WIDTH)<<i->teacherId << setw(Global::PRINT_LONG_WIDTH) <<	i->name << setw(Global::PRINT_LONG_WIDTH)  << i->password << endl;
	}
	return true;
} 
