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
	bool login();
};
vector<Teacher> g_teacherList;


Teacher::Teacher(int id,string name,string passwd){
	this->teacherId=id;
	this->name=name;
	this->password=passwd;
}

bool Teacher::login(){
	int id;
	string inputPasswd;
	clear();
	cout << "------教师登陆-----" << endl;
	for(int j=0;j<LOGIN_RETRY_MAX;j++){
		cout << "请输入教师帐号（即教师编号）:" ;
		cin >> id;
		
		//在教师向量里查找编号为inpuAccount的元素
		vector<Teacher>::iterator i;

		for(i=g_teacherList.begin();i!=g_teacherList.end();++i){
			if(i->teacherId == id){
				break;
			}
		}
		if(i == g_teacherList.end()){
			cout << "账号不存在!请重新输入"  << endl;
			continue;
		}
		
		cout << "请输入密码:" ;
		cin >> inputPasswd;

		if(inputPasswd != i->password){
			cout << "密码错误!请重新输入"  << endl;
			continue;
		}
		return true;
	}
	
	cout << "登陆次数超过" << LOGIN_RETRY_MAX << endl; 
	cout << "已退出" << endl;
	return false;
}



#endif 
