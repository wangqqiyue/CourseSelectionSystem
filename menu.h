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

vector<Course> g_courseList;


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
	
	//���ع���Ա�˺�����
	in.open("administrator.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		string account,password;
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
		int teacherId;
		string teacherName,teacherPassword;
		stringstream ss(temp);
		ss >> teacherId;
		ss >> teacherName;
		ss >> teacherPassword;
		Teacher t(teacherId,teacherName,teacherPassword);
		g_teacherList.push_back(t);
	}
	in.close();
	
	//���ؿγ���Ϣ
	in.open("coursesInfo.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		int courseId,number,teacherId,classroomId;
		float price;
		string courseName;
		
		stringstream ss(temp);
		ss >> courseId;
		ss >> courseName;
		ss >> number;
		ss >> price;
		ss >> teacherId;
		ss >> classroomId;
		
		Course c(courseId,courseName,number,price,teacherId,classroomId);
		g_courseList.push_back(c);
	}
	
	in.close();
}


//��Ϣ�洢
void storeInfo(){
	ofstream out;

	//���ع���Ա�˺�����
	out.open("administrator.txt",ios::out);
	out << setw(Global::PRINT_WIDTH)<<"�˺�" << setw(Global::PRINT_WIDTH) << "����" << endl;
	out << setw(Global::PRINT_WIDTH)<<Administrator::adminAccount << setw(Global::PRINT_WIDTH) << Administrator::password << endl;
	out.close();
	
	//�洢��ʦ��Ϣ 
	out.open("teachersInfo.txt",ios::out);
	//һ���ж�ȡ��Ϣ�����ָֵ 
	out << setw(Global::PRINT_WIDTH)<<"��ʦ���" << setw(Global::PRINT_LONG_WIDTH) << "��ʦ����" << setw(Global::PRINT_LONG_WIDTH) << "����"<< endl;
	for(vector<Teacher>::iterator i=g_teacherList.begin();i!=g_teacherList.end();i++){
		out <<  setw(Global::PRINT_WIDTH)<<i->teacherId << setw(Global::PRINT_LONG_WIDTH) <<	i->name << setw(Global::PRINT_LONG_WIDTH)  << i->password << endl;
	}
	out.close();
	
	//�洢�γ���Ϣ 
	out.open("coursesInfo.txt",ios::out);
	//һ���ж�ȡ��Ϣ�����ָֵ 
	out << setw(Global::PRINT_WIDTH)<<"�γ̱���" << setw(Global::PRINT_WIDTH) << "�γ���" << setw(Global::PRINT_LONG_WIDTH) << "ѡ������"<< setw(Global::PRINT_LONG_WIDTH) << "�γ̼۸�"<< setw(Global::PRINT_LONG_WIDTH) << "�ο���ʦ���"<< setw(Global::PRINT_LONG_WIDTH) << "���ұ��"<<endl;
	for(vector<Course>::iterator i=g_courseList.begin();i!=g_courseList.end();i++){
		out <<  setw(Global::PRINT_WIDTH)<<i->courseId << setw(Global::PRINT_WIDTH) <<	i->courseName << setw(Global::PRINT_LONG_WIDTH)  << i->studentNumber << setw(Global::PRINT_LONG_WIDTH)  << i->price << setw(Global::PRINT_LONG_WIDTH)  << i->teacherId << setw(Global::PRINT_LONG_WIDTH)  << i->classroomId << endl;
	}
	out.close();
}

#endif
