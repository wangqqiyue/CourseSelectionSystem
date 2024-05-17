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
	cout << "��ӭʹ��" << titleStr << endl;
	cout << endl;
	while(role >= ROLE_MAX || role < 0){
		cout << "��������ǣ�"<<endl;
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
	int teacherId;
	string teacherName,teacherPassword;
	
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
		ss >> teacherId;
		ss >> teacherName;
		ss >> teacherPassword;
		Teacher t(teacherId,teacherName,teacherPassword);
		g_teacherList.push_back(t);
	}
	
	in.close();
}


//��Ϣ�洢
void storeInfo(){
	ofstream out;

	//���ع���Ա�˺�����
	out.open("administrator.txt",ios::out);
	out << setw(PRINT_WIDTH)<<"�˺�" << setw(PRINT_WIDTH) << "����" << endl;
	out << setw(PRINT_WIDTH)<<g_admin.adminAccount << setw(PRINT_WIDTH) << g_admin.password << endl;
	out.close();
	
	//�洢��ʦ��Ϣ 
	out.open("teachersInfo.txt",ios::out);
	//һ���ж�ȡ��Ϣ�����ָֵ 
	out << setw(PRINT_WIDTH)<<"��ʦ���" << setw(PRINT_LONG_WIDTH) << "��ʦ����" << setw(PRINT_LONG_WIDTH) << "����"<< endl;
	for(vector<Teacher>::iterator i=g_teacherList.begin();i!=g_teacherList.end();i++){
		out <<  setw(PRINT_WIDTH)<<i->teacherId << setw(PRINT_LONG_WIDTH) <<	i->name << setw(PRINT_LONG_WIDTH)  << i->password << endl;
	}
	
	
	out.close();
}


