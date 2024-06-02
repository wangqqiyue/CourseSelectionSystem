#ifndef INCLUDE_ADMINISTATOR
#include "administrator.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_RECORD_PROCESS
#include "recordProcess.h" 
#endif


//静态成员变量需要在类外定义 
bool Administrator::hasAccount=false;
bool Administrator::hasLoaded=false;
string Administrator::adminAccount;
string Administrator::password;



//函数指针数组的初始化 
bool (*Administrator::mgmtFuncs[Global::MGMT_MAX])() = {teacherMgmt,classroomMgmt,courseMgmt};

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

