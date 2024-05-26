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
	while(login()){
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
	string comfirmPasswd;
	clear();
	cout << "------创建管理员账号-----" << endl;
	cout << "请输入管理员账号名称:" ;
	cin >> adminAccount;
	
	do{
		cout << "请输入管理员密码:" ;
		cin >> password;
		
		cout << "请再次输入以确认密码:" ;
		cin >> comfirmPasswd;	
		
		if(password != comfirmPasswd){
			cout << "两次密码不一致，请重新输入!" << endl;
		}
	}while(password != comfirmPasswd);
}

bool Administrator::login(){
	string inputAccount;
	string inputPasswd;
	int loginChoice = -1;
	
	clear();
	cout << "------管理员登陆-----" << endl;
	loginChoice = getChoice("", Global::loginStr, Global::LOGIN_MAX);
	if(Global::LOGIN_MAX == loginChoice){
			return false;
	} 
	
	for(int i=0;i<Global::LOGIN_RETRY_MAX;i++){
		cout << "请输入管理员账号名称:" ;
		cin >> inputAccount;
		if(inputAccount != adminAccount){
			cout << "账号不存在!请重新输入"  << endl;
			continue;
		}

		cout << "请输入管理员密码:" ;
		cin >> inputPasswd;
		if(inputPasswd != Administrator::password){
		
			cout << "密码错误!请重新输入"  << endl;
			cout <<"password="<<password<<endl;
		system("pause");
			continue;
		}
		
		cout << "登陆成功" << endl;
		return true;
	}
	
	cout << "登陆次数超过" << Global::LOGIN_RETRY_MAX << endl; 
	cout << "已退出" << endl;
	return false;
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

