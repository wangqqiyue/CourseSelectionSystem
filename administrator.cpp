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
			return Teacher::retrieve();
		}else if(Global::CREATE == opChoice){
			return Teacher::create();
		}else if(Global::DEL == opChoice){
			return Teacher::del();
		}
	}
	return false;
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
			return Classroom::retrieve();
		}else if(Global::CREATE == opChoice){
			return Classroom::create();
		}else if(Global::DEL == opChoice){
			return Classroom::del();
		}
	}
	return false;
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
			return Course::retrieve();
		}else if(Global::CREATE == opChoice){
			return Course::create();
		}else if(Global::DEL == opChoice){
			return Course::del();
		}
	}
	return false;
}




