#ifndef INCLUDE_MENU
#define INCLUDE_MENU
/*菜单和界面格式头文件*/

#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif

#ifndef INCLUDE_SSTREAM
#include <sstream>
#define INCLUDE_SSTREAM
#endif

#ifndef INCLUDE_FSTREAM
#include <fstream>
#define INCLUDE_FSTREAM
#endif


#ifndef INCLUDE_COURSE
#include "course.h"
#endif

#ifndef INCLUDE_ADMINISTATOR
#include "administrator.h"
#endif 

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif


const char *titleStr="培训中心管理系统";

vector<Course> g_courseList;


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
	
	//加载管理员账号密码
	in.open("administrator.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		string account,password;
		stringstream ss(temp);
		ss >> account;
		ss >> password;
		Administrator::adminAccount=account;
		Administrator::password=password;
		Administrator::hasAccount=true;
	}
	in.close();
	
	//加载教师信息 
	in.open("teachersInfo.txt",ios::in);
	//一行行读取信息，并分割赋值 
	getline(in,temp);
	while(getline(in,temp)){
		int teacherId;
		string teacherName,teacherPassword;
		stringstream ss(temp);
		ss >> teacherId;
		ss >> teacherName;
		ss >> teacherPassword;
		Teacher t(teacherId,teacherName,teacherPassword);
		g_teacherList.push_back(t);
	}
	in.close();
	
	//加载课程信息
	in.open("coursesInfo.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		int courseId,number,teacherId,classroomId;
		float price;
		string courseName;
		
		stringstream ss(temp);
		ss >> courseId;
		ss >> courseName;
		ss >> number;
		ss >> price;
		ss >> teacherId;
		ss >> classroomId;
		
		Course c(courseId,courseName,number,price,teacherId,classroomId);
		g_courseList.push_back(c);
	}
	
	in.close();
}


//信息存储
void storeInfo(){
	ofstream out;

	//加载管理员账号密码
	out.open("administrator.txt",ios::out);
	out << setw(Global::PRINT_WIDTH)<<"账号" << setw(Global::PRINT_WIDTH) << "密码" << endl;
	out << setw(Global::PRINT_WIDTH)<<Administrator::adminAccount << setw(Global::PRINT_WIDTH) << Administrator::password << endl;
	out.close();
	
	//存储教师信息 
	out.open("teachersInfo.txt",ios::out);
	//一行行读取信息，并分割赋值 
	out << setw(Global::PRINT_WIDTH)<<"教师编号" << setw(Global::PRINT_LONG_WIDTH) << "教师姓名" << setw(Global::PRINT_LONG_WIDTH) << "密码"<< endl;
	for(vector<Teacher>::iterator i=g_teacherList.begin();i!=g_teacherList.end();i++){
		out <<  setw(Global::PRINT_WIDTH)<<i->teacherId << setw(Global::PRINT_LONG_WIDTH) <<	i->name << setw(Global::PRINT_LONG_WIDTH)  << i->password << endl;
	}
	out.close();
	
	//存储课程信息 
	out.open("coursesInfo.txt",ios::out);
	//一行行读取信息，并分割赋值 
	out << setw(Global::PRINT_WIDTH)<<"课程编码" << setw(Global::PRINT_WIDTH) << "课程名" << setw(Global::PRINT_LONG_WIDTH) << "选课人数"<< setw(Global::PRINT_LONG_WIDTH) << "课程价格"<< setw(Global::PRINT_LONG_WIDTH) << "任课老师编号"<< setw(Global::PRINT_LONG_WIDTH) << "教室编号"<<endl;
	for(vector<Course>::iterator i=g_courseList.begin();i!=g_courseList.end();i++){
		out <<  setw(Global::PRINT_WIDTH)<<i->courseId << setw(Global::PRINT_WIDTH) <<	i->courseName << setw(Global::PRINT_LONG_WIDTH)  << i->studentNumber << setw(Global::PRINT_LONG_WIDTH)  << i->price << setw(Global::PRINT_LONG_WIDTH)  << i->teacherId << setw(Global::PRINT_LONG_WIDTH)  << i->classroomId << endl;
	}
	out.close();
}

#endif
