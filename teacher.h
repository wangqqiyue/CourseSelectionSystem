#ifndef INCLUDE_TEACHER
#define INCLUDE_TEACHER

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_VECTOR
#include <vector>
#define INCLUDE_VECTOR
#endif


#ifndef INCLUDE_STRING
#include <string>
#define INCLUDE_STRING
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
	static bool recordToStream(ostream& out);
};
extern vector<Teacher> g_teacherList;


#endif 
