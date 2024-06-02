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
	string account;
	string name;
	string password;
	Teacher(string acc,string n,string p):account(acc),name(n),password(p){}
	static bool recordToStream(ostream& out, vector<Teacher>::iterator firstRecord, bool onlyOne=false);
	static bool checkAccountExist(string account, vector<Teacher>::iterator &i); 
	static bool checkAccountExist(string account);

};
extern vector<Teacher> teacherList;


#endif 
