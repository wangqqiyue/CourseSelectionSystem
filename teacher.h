#ifndef _TEACHER_H
#define _TEACHER_H

#include "role.h"

//教师 有账号密码 
/*
功能：查看自己的课程信息和学员名单
		 

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
