#ifndef INCLUDE_TEACHER
#define INCLUDE_TEACHER

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif




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
	static bool login();
};
extern vector<Teacher> g_teacherList;


#endif 
