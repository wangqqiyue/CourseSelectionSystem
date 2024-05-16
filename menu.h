/*菜单和界面格式头文件*/
#include <windows.h>
#include "course.h"
#include "administrator.h"
#include "student.h"
#include "teacher.h"
#include <sstream>
#include <fstream>

const char *titleStr="培训中心管理系统";


//设置控制台标题 
void setTitle() {
	SetConsoleTitle(titleStr);
}

//统一的欢迎界面,获取用户身份 
Role greeting(){
	int role = ROLE_MAX;
	cout << "----欢迎使用----" << titleStr << endl;
	cout << endl;
	while(role >= ROLE_MAX || role < 0){
		cout << "您的身份是：";
		for(int i=0;i<ROLE_MAX;i++){
			cout << i << ". " << roleStr[i] << endl;
		}
		cin >> role;
	}
	return (Role)role;
}

//信息加载 
void loadInfo(){
	ifstream in;
	string temp;
	string account,password;
	
	int i=0;
	
	//加载管理员账号密码
	in.open("administrator.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		stringstream ss(temp);
		ss >> account;
		ss >> password;
		g_admin.loadAccount(account,password);
	}
	in.close();
	
	//加载教师信息 
	in.open("teachersInfo.txt",ios::in);
	//一行行读取信息，并分割赋值 
	getline(in,temp);
	while(getline(in,temp)){
		stringstream ss(temp);
		ss >> g_teacherList[i].teacherId;
		ss >> g_teacherList[i].name;
		ss >> g_teacherList[i].password;
		i++;
		if(i>=TEACHER_NUMBER_MAX){
			cout << "读取的教师信息已达到上限" << TEACHER_NUMBER_MAX << "条，停止加载." << endl;
			break;
		}
	}
	
	in.close();
}


//信息加载 
void storeInfo(){
	ofstream out;

	//加载管理员账号密码
	out.open("administrator.txt",ios::out);
	out << "账号" << setw(PRINT_WIDTH) << "密码" << endl;
	out << g_admin.adminAccount << setw(PRINT_WIDTH) << g_admin.password << endl;
	out.close();
	
}


