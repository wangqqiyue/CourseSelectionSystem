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
};

Teacher g_teacherList[TEACHER_NUMBER_MAX]={0};

#endif 
