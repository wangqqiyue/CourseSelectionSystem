#ifndef INCLUDE_ADMINISTATOR
#include "administrator.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_RECORD_PROCESS
#include "recordProcess.h" 
#endif

#ifndef INCLUDE_FSTREAM
#include <fstream>
#define INCLUDE_FSTREAM
#endif


#ifndef INCLUDE_SSTREAM
#include <sstream>
#define INCLUDE_SSTREAM
#endif

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

#ifndef INCLUDE_COURSE
#include "course.h"
#endif

#ifndef INCLUDE_CLASSROOM
#include "classroom.h"
#endif


//静态成员变量需要在类外定义 
bool Administrator::hasAccount=false;
bool Administrator::hasLoaded=false;
string Administrator::adminAccount;
string Administrator::password;
//函数指针数组的初始化 
bool (*Administrator::mgmtFuncs[Global::MGMT_MAX])() = {teacherMgmt,classroomMgmt,courseMgmt};


const char* Administrator::dataFile = "administrator.txt"; 

bool Administrator::storeInfo(){
	bool result = true;
	ofstream out;
	//加载管理员账号密码
	out.open(dataFile,ios::out);
	if(!Administrator::recordToStream(out)){
		result= false;
	}
	out.close();
	return result;
}

bool Administrator::loadInfo(){
	ifstream in;
	string temp;
	
	//加载管理员账号密码
	in.open(dataFile,ios::in);
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
}

//管理员基本操作流程 
void Administrator::process(){
	if(!hasAccount){
		createAdmin();
	}
	while(login(Global::ADMINISTRATOR)){
		int mgmtChoice=-1; 	
		/*打印菜单选项 
		教师信息
			增 删 改  查 
		教室信息
			增 删 改  查 
		课程信息 
			增 删 改  查 
		*/
		while(Global::MGMT_MAX != mgmtChoice){
			clear();
			cout << "------管理员菜单-------" << endl;
			mgmtChoice = getChoice("选择功能:", Global::mgmtStr, Global::MGMT_MAX);
			if(Global::MGMT_MAX != mgmtChoice){
				//不断执行管理操作，直到返回错误退出 
				while(mgmtFuncs[mgmtChoice]());
			}
		}
	}
	
}

//创建管理员账号 
void Administrator::createAdmin(){
	clear();
	cout << "------创建管理员账号-----" << endl;
	cout << "请输入管理员账号名称:" ;
	cin >> adminAccount;
	
	Administrator::password = setPassword();
}

bool Administrator::recordToStream(ostream& out){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_WIDTH)<<"账号" << setw(Global::PRINT_WIDTH) << "密码" << endl;
	out << setw(Global::PRINT_WIDTH)<<Administrator::adminAccount << setw(Global::PRINT_WIDTH) << Administrator::password << endl;
	return true;
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
	Teacher::recordToStream(cout, teacherList.begin());
	goPrevious(); 
	return true;
	
}

/*新增教师数据 
需要判断新增数据是否有重复,新增后不超过教师总数上限 
*/
bool teacherInfoCreate(){
	string account,name,passwd;
	char comfirm = 'y';
	clear();
	cout << "------新增教师信息-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(teacherList.size() >= Global::TEACHER_NUMBER_MAX){
			cout << "教师数量已达上限("<< Global::TEACHER_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "请输入信息" << endl;
		cout<<"教师账号:";
		cin >> account;

		if(Teacher::checkAccountExist(account)){
			cout << "是否继续?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "教师姓名:" ;
		cin >> name;
		
		cout << "密码;";
		cin >> passwd;
		
		Teacher t(account,name,passwd);
		teacherList.push_back(t);
		
		cout << "已新增数据如下" << endl;
		Teacher::recordToStream(cout, teacherList.end()-1, true);

		cout << "是否继续?Y/N" << endl;
		cin >> comfirm;
	}
	
	goPrevious();
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
	goPrevious();
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
		if(Classroom::roomList.size() >= Global::ROOM_NUMBER_MAX){
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
		for(i=Classroom::roomList.begin();i!=Classroom::roomList.end();++i){
			if(i->roomId == id){
				cout << "该编号已存在！请重新选择" << endl;
				break;
			}
		}
		if(i != Classroom::roomList.end()){
			cout << "是否继续?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "教室名称:" ;
		cin >> name;
		for(i=Classroom::roomList.begin();i!=Classroom::roomList.end();++i){
			if(i->roomName == name){
				cout << "该名称已存在！请重新选择" << endl;
				break;
			}
		}
		if(i != Classroom::roomList.end()){
			cout << "是否继续?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "教室容量";
		cin >> capacity;
		
		Classroom cr(id,name,capacity);
		Classroom::roomList.push_back(cr);
		
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



/*新增课程数据 
需要判断新增数据是否有重复,新增后不超过课程总数上限 
*/
bool courseInfoCreate(){
	int id,roomId,capacity;
	float price;
	string name,teacherAccount;

	char comfirm = 'y';
	clear();
	cout << "------新增课程信息-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(Course::courseList.size() >= Global::COURSE_NUMBER_MAX){
			cout << "课程数量已达上限("<< Global::COURSE_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "请输入信息" << endl;
		
		while('y' == comfirm || 'Y' == comfirm){
			cout<<"课程编号:";
			cin >> id;
			if(!isInputOk()){
				continue;
			}
			
			vector<Course>::iterator i;
			for(i=Course::courseList.begin();i!=Course::courseList.end();++i){
				if(i->courseId == id){
					cout << "该编号已存在！请重新选择" << endl;
					break;
				}
			}
			if(i != Course::courseList.end()){
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
		
		
		while('y' == comfirm || 'Y' == comfirm){
			cout << "课程名称:" ;
			cin >> name;
			
			vector<Course>::iterator i;
			for(i=Course::courseList.begin();i!=Course::courseList.end();++i){
				if(i->courseName == name){
					cout << "该名称已存在！请重新选择" << endl;
					break;
				}
			}
			if(i != Course::courseList.end()){
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
		
		while('y' == comfirm || 'Y' == comfirm){
			cout << "课程价格";
			cin >> price;
			if(price < 0 || price > Global::COURSE_PRICE_MAX){
				cout << "课程价格需要在合理范围(0--"<< Global::COURSE_PRICE_MAX <<")，请重新输入:" << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
		
		while('y' == comfirm || 'Y' == comfirm){
			cout<<"教师帐号:";
			cin >> teacherAccount;

			if(Teacher::checkAccountExist(teacherAccount)){
				cout << "该编号不存在！请重新选择" << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}

		while('y' == comfirm || 'Y' == comfirm){
			cout << "课程人数限额";
			cin >> capacity;
			if(capacity < Global::COURSE_CAPACITY_MIN || capacity > Global::COURSE_CAPACITY_MAX){
				cout << "课程人数限额需要在合理范围("<< Global::COURSE_CAPACITY_MIN <<"--"<< Global::COURSE_CAPACITY_MAX <<")"<<endl;
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
		
		while('y' == comfirm || 'Y' == comfirm){
			cout<<"教室编号:";
			cin >> roomId;
			if(!isInputOk()){
				continue;
			}
			vector<Classroom>::iterator i;
			if(!Classroom::checkExist(roomId,i)){
				cout << "该编号不存在！请重新选择" << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else if(i->capacity < capacity){
				cout << "该教室仅能容纳" << i->capacity << "人, 请重新选择！" << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
				
		//新建课程对象，并添加到向量尾部 
		Course c(id,name,0,price,teacherAccount,roomId,capacity);
		Course::courseList.push_back(c);
		
		//打印新增数据 
		cout << "已新增数据如下" << endl;
		Course::recordToStream(cout,Course::courseList.end() - 1,true);
		
		cout << "是否继续?Y/N" << endl;
		cin >> comfirm;
	}
	
	goPrevious();
	return true;
	
}
