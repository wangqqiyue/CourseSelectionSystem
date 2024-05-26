#ifndef INCLUDE_MENU
#define INCLUDE_MENU
/*�˵��ͽ����ʽͷ�ļ�*/

#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif

#ifndef INCLUDE_SSTREAM
#include <sstream>
#define INCLUDE_SSTREAM
#endif

#ifndef INCLUDE_FSTREAM
#include <fstream>
#define INCLUDE_FSTREAM
#endif


#ifndef INCLUDE_COURSE
#include "course.h"
#endif

#ifndef INCLUDE_ADMINISTATOR
#include "administrator.h"
#endif 

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif


const char *titleStr="��ѵ���Ĺ���ϵͳ";


//���ÿ���̨���� 
void setTitle() {
	SetConsoleTitle(titleStr);
}

//ͳһ�Ļ�ӭ����,��ȡ�û���� 
Role greeting(){
	int role = -1;
	clear(); 
	cout << "-----���˵�-----"<< endl;
	cout << "��ӭʹ��" << titleStr << endl;

	role = getChoice("��������ǣ�",roleStr,ROLE_MAX);
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
		Administrator::adminAccount=account;
		Administrator::password=password;
		Administrator::hasAccount=true;
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
	out << setw(PRINT_WIDTH)<<Administrator::adminAccount << setw(PRINT_WIDTH) << Administrator::password << endl;
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

#endif
