#ifndef _ROLE_H
#define _ROLE_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

/*用户角色定义头文件*/
enum Role{
	ADMINISTRATOR=0,
	STUDENT,
	TEACHER,
	ROLE_MAX,
};

const char *roleStr[]={"管理员","学生","老师","退出"};

enum LoginChoice{
	LOGIN=0,
	LOGIN_MAX,
};

const char *loginStr[]={"登陆","返回上一级"};

//登陆最多尝试次数 
#define LOGIN_RETRY_MAX  5

//打印字符宽度 
#define PRINT_WIDTH  		8
#define PRINT_LONG_WIDTH  		16

//最多老师人数
#define TEACHER_NUMBER_MAX  100 

//清空控制台
void clear(){
	system("cls");
}

int getChoice(const char* promptStr, const char **choiceStr, const int choiceMax){
	int choice = -1;
	//含choiceMax，用户可以选择退出/返回到上一级 
	while(choice > choiceMax || choice < 0){
		cout << promptStr <<endl;
		for(int i=0;i<=choiceMax;i++){
			cout << i << ". " << choiceStr[i] << endl;
		}
		cin >> choice;
	}
	
	return choice;
}

#endif
