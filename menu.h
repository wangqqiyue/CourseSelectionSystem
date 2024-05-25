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
	int role = -1;
	clear(); 
	cout << "-----主菜单-----"<< endl;
	cout << "欢迎使用" << titleStr << endl;

	role = getChoice("您的身份是：",roleStr,ROLE_MAX);
	return (Role)role;
}

//信息加载 
void loadInfo(){
	ifstream in;
	string temp;
	string account,password;
	int teacherId;
	string teacherName,teacherPassword;
	
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
		ss >> teacherId;
		ss >> teacherName;
		ss >> teacherPassword;
		Teacher t(teacherId,teacherName,teacherPassword);
		g_teacherList.push_back(t);
	}
	
	in.close();
}


//信息存储
void storeInfo(){
	ofstream out;

	//加载管理员账号密码
	out.open("administrator.txt",ios::out);
	out << setw(PRINT_WIDTH)<<"账号" << setw(PRINT_WIDTH) << "密码" << endl;
	out << setw(PRINT_WIDTH)<<g_admin.adminAccount << setw(PRINT_WIDTH) << g_admin.password << endl;
	out.close();
	
	//存储教师信息 
	out.open("teachersInfo.txt",ios::out);
	//一行行读取信息，并分割赋值 
	out << setw(PRINT_WIDTH)<<"教师编号" << setw(PRINT_LONG_WIDTH) << "教师姓名" << setw(PRINT_LONG_WIDTH) << "密码"<< endl;
	for(vector<Teacher>::iterator i=g_teacherList.begin();i!=g_teacherList.end();i++){
		out <<  setw(PRINT_WIDTH)<<i->teacherId << setw(PRINT_LONG_WIDTH) <<	i->name << setw(PRINT_LONG_WIDTH)  << i->password << endl;
	}
	
	
	out.close();
}


