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
};

Teacher::Teacher(int id,string name,string passwd){
	this->teacherId=id;
	this->name=name;
	this->password=passwd;
}

vector<Teacher> g_teacherList;

#endif 
