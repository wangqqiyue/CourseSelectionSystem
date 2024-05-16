#ifndef _ROLE_H
#define _ROLE_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/*用户角色定义头文件*/
enum Role{
	ADMINISTRATOR=0,
	STUDENT,
	TEACHER,
	ROLE_MAX,
};

const char *roleStr[]={"管理员","学生","老师"};

//登陆最多尝试次数 
#define LOGIN_RETRY_MAX  5

//打印字符宽度 
#define PRINT_WIDTH  		8

//最多老师人数
#define TEACHER_NUMBER_MAX  100 

//清空控制台
void clear(){
	system("cls");
}


#endif
