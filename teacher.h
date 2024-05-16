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
};

Teacher g_teacherList[TEACHER_NUMBER_MAX]={0};

#endif 
