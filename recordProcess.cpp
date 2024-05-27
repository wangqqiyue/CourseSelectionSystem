#ifndef INCLUDE_RECORD_PROCESS
#include "recordProcess.h" 
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


#ifndef INCLUDE_SSTREAM
#include <sstream>
#define INCLUDE_SSTREAM
#endif

#ifndef INCLUDE_FSTREAM
#include <fstream>
#define INCLUDE_FSTREAM
#endif


#ifndef INCLUDE_COURSE_RESOURCE
#include "courseResource.h"
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
	
	//加载教室信息
	in.open("classroomsInfo.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		int roomId,capacity;
		string roomName;
		
		stringstream ss(temp);
		ss >> roomId;
		ss >> roomName;
		ss >> capacity;
		
		Classroom cr(roomId,roomName,capacity);
		g_roomList.push_back(cr);
	}
	in.close();
}


//信息存储
void storeInfo(){
	ofstream out;

	//加载管理员账号密码
	out.open("administrator.txt",ios::out);
	Administrator::recordToStream(out);
	out.close();
	
	//存储教师信息 
	out.open("teachersInfo.txt",ios::out);
	Teacher::recordToStream(out);
	out.close();
	
	//存储课程信息 
	out.open("coursesInfo.txt",ios::out);
	Course::recordToStream(out);
	out.close();
	
	//存储教室信息 
	out.open("classroomsInfo.txt",ios::out);
	Classroom::recordToStream(out);
	out.close();
}


/*----------------管理教师数据 -------------------*/


bool teacherMgmt(){
	int opChoice = -1;
	while(Global::OP_MAX != opChoice){
		opChoice = -1; 
		clear();
		cout << "------教师信息管理-----"  << endl;
		opChoice = getChoice("选择操作:", Global::operationStr, Global::OP_MAX);
		if(Global::RETRIEVE == opChoice){
			return teacherInfoRetrieve();
		}else if(Global::CREATE == opChoice){
			return teacherInfoCreate();
		}
	}
	return false;
}


//查询教师信息 
bool teacherInfoRetrieve(){
	clear();
	cout << "------教师信息查询-----"	<< endl;
	Teacher::recordToStream(cout);
	cout << "按任意键返回上一级" << endl;
	cin.ignore();
	getchar();
	return true;
	
}

/*新增教师数据 
需要判断新增数据是否有重复,新增后不超过教师总数上限 
*/
bool teacherInfoCreate(){
	int id;
	string name;
	string passwd;
	char comfirm = 'y';
	clear();
	cout << "------新增教师信息-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(g_teacherList.size() >= Global::TEACHER_NUMBER_MAX){
			cout << "教师数量已达上限("<< Global::TEACHER_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "请输入信息" << endl;
		cout<<"教师编号:";
		cin >> id;
		if(!isInputOk()){
			continue;
		}
		
		vector<Teacher>::iterator i;
		for(i=g_teacherList.begin();i!=g_teacherList.end();++i){
			if(i->teacherId == id){
				cout << "该编号已存在！请重新选择" << endl;
				break;
			}
		}
		if(i != g_teacherList.end()){
			cout << "是否继续?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "教师姓名:" ;
		cin >> name;
		
		cout << "密码;";
		cin >> passwd;
		
		Teacher t(id,name,passwd);
		g_teacherList.push_back(t);
		
		cout << "已新增数据如下" << endl;
		cout << setw(Global::PRINT_WIDTH)<<"教师编号" << setw(Global::PRINT_LONG_WIDTH) << "教师姓名" << setw(Global::PRINT_LONG_WIDTH) << "密码"<< endl;
		cout <<  setw(Global::PRINT_WIDTH)<<id << setw(Global::PRINT_LONG_WIDTH) <<	name << setw(Global::PRINT_LONG_WIDTH)  << passwd << endl;
		
		
		cout << "是否继续?Y/N" << endl;
		cin >> comfirm;
	}
	
	cout << "按任意键返回上一级" << endl;
	cin.ignore();
	getchar();
	return true;
	
}


/*--------------------------------教室信息管理 ----------------------------------------*/
bool classroomMgmt(){
	int opChoice = -1;
	while(Global::OP_MAX != opChoice){
		opChoice = -1; 
		clear();
		cout << "------教室信息管理-----"  << endl;
		opChoice = getChoice("选择操作:", Global::operationStr, Global::OP_MAX);
		if(Global::RETRIEVE == opChoice){
			return roomInfoRetrieve();
		}else if(Global::CREATE == opChoice){
			return roomInfoCreate();
		}
	}
	return false;
}

//查询教室数据 
bool roomInfoRetrieve(){
	clear();
	cout << "------教室信息查询-----"	<< endl;
	Classroom::recordToStream(cout);
	cout << "按任意键返回上一级" << endl;
	cin.ignore();
	getchar();
	return true;
	
}


/*新增教室数据 
需要判断新增数据是否有重复,新增后不超过教室总数上限 
*/
bool roomInfoCreate(){
	int id,capacity;
	string name;

	char comfirm = 'y';
	clear();
	cout << "------新增教室信息-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(g_roomList.size() >= Global::ROOM_NUMBER_MAX){
			cout << "教室数量已达上限("<< Global::ROOM_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "请输入信息" << endl;
		cout<<"教室编号:";
		cin >> id;
		if(!isInputOk()){
			continue;
		}
		
		vector<Classroom>::iterator i;
		for(i=g_roomList.begin();i!=g_roomList.end();++i){
			if(i->roomId == id){
				cout << "该编号已存在！请重新选择" << endl;
				break;
			}
		}
		if(i != g_roomList.end()){
			cout << "是否继续?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "教室名称:" ;
		cin >> name;
		for(i=g_roomList.begin();i!=g_roomList.end();++i){
			if(i->roomName == name){
				cout << "该名称已存在！请重新选择" << endl;
				break;
			}
		}
		if(i != g_roomList.end()){
			cout << "是否继续?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "教室容量";
		cin >> capacity;
		
		Classroom cr(id,name,capacity);
		g_roomList.push_back(cr);
		
		cout << "已新增数据如下" << endl;
		cout << setw(Global::PRINT_WIDTH)<<"教室编号" << setw(Global::PRINT_LONG_WIDTH) << "教室名称" << setw(Global::PRINT_LONG_WIDTH) << "教室容量"<< endl;
		cout <<  setw(Global::PRINT_WIDTH)<<id << setw(Global::PRINT_LONG_WIDTH) <<	name << setw(Global::PRINT_LONG_WIDTH)  << capacity << endl;
		
		
		cout << "是否继续?Y/N" << endl;
		cin >> comfirm;
	}
	
	cout << "按任意键返回上一级" << endl;
	cin.ignore();
	getchar();
	return true;
	
}

/*--------------------------------课程信息管理--------------------------------------------*/
bool courseMgmt(){
	int opChoice = -1;
	while(Global::OP_MAX != opChoice){
		opChoice = -1; 
		clear();
		cout << "------课程信息管理-----"  << endl;
		opChoice = getChoice("选择操作:", Global::operationStr, Global::OP_MAX);
		if(Global::RETRIEVE == opChoice){
			return courseInfoRetrieve();
		}else if(Global::CREATE == opChoice){
			return courseInfoCreate();
		}
	}
	return false;
}

//查询课程数据 
bool courseInfoRetrieve(){
	clear();
	cout << "------教室信息查询-----"	<< endl;
	Course::recordToStream(cout);
	cout << "按任意键返回上一级" << endl;
	cin.ignore();
	getchar();
	return true;
	
}

/*新增课程数据 
需要判断新增数据是否有重复,新增后不超过课程总数上限 
*/
bool courseInfoCreate(){
	int id,teacherId,roomId;
	float price;
	string name;

	char comfirm = 'y';
	clear();
	cout << "------新增课程信息-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(g_courseList.size() >= Global::COURSE_NUMBER_MAX){
			cout << "课程数量已达上限("<< Global::COURSE_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "请输入信息" << endl;
		cout<<"课程编号:";
		cin >> id;
		if(!isInputOk()){
			continue;
		}
		
		vector<Course>::iterator i;
		for(i=g_courseList.begin();i!=g_courseList.end();++i){
			if(i->courseId == id){
				cout << "该编号已存在！请重新选择" << endl;
				break;
			}
		}
		if(i != g_courseList.end()){
			cout << "是否继续?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		
		cout << "课程名称:" ;
		cin >> name;
		for(i=g_courseList.begin();i!=g_courseList.end();++i){
			if(i->courseName == name){
				cout << "该名称已存在！请重新选择" << endl;
				break;
			}
		}
		if(i != g_courseList.end()){
			cout << "是否继续?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "课程价格";
		cin >> price;
		while(price < 0 || price > Global::COURSE_PRICE_MAX){
			cout << "课程价格需要在合理范围(0--"<< Global::COURSE_PRICE_MAX <<")，请重新输入:" << endl;
			cin >> price;
		}
		
		
		while(true) 
		{
			cout<<"教师编号:";
			cin >> teacherId;
			if(!isInputOk()){
				continue;
			}
			vector<Teacher>::iterator i;
			for(i=g_teacherList.begin();i!=g_teacherList.end();++i){
				if(i->teacherId == teacherId){
					break;
				}
			}
			if(i == g_teacherList.end()){
				cout << "该编号不存在！请重新选择" << endl;
			}else{
				break;
			}
		}

		while(true) 
		{
			cout<<"教室编号:";
			cin >> roomId;
			if(!isInputOk()){
				continue;
			}
			vector<Classroom>::iterator i;
			for(i=g_roomList.begin();i!=g_roomList.end();++i){
				if(i->roomId == roomId){
					break;
				}
			}
			if(i == g_roomList.end()){
				cout << "该编号不存在！请重新选择" << endl;
			}else{
				break;
			}
		}
				
		
		Course c(id,name,0,price,teacherId,roomId);
		g_courseList.push_back(c);
		
		cout << "已新增数据如下" << endl;
		cout << setw(Global::PRINT_WIDTH)<<"课程编码" << setw(Global::PRINT_LONG_WIDTH) << "课程名" << setw(Global::PRINT_LONG_WIDTH) << "选课人数"<< setw(Global::PRINT_LONG_WIDTH) << "课程价格"<< setw(Global::PRINT_LONG_WIDTH) << "任课老师编号"<< setw(Global::PRINT_LONG_WIDTH) << "教室编号"<<endl;
		cout <<  setw(Global::PRINT_WIDTH)<<id << setw(Global::PRINT_LONG_WIDTH) <<	name << setw(Global::PRINT_LONG_WIDTH)  << 0 << setw(Global::PRINT_LONG_WIDTH) << fixed << setprecision(2) << price << setw(Global::PRINT_LONG_WIDTH)  << teacherId << setw(Global::PRINT_LONG_WIDTH)  << roomId << endl;
	
		
		cout << "是否继续?Y/N" << endl;
		cin >> comfirm;
	}
	
	cout << "按任意键返回上一级" << endl;
	cin.ignore();
	getchar();
	return true;
	
}
