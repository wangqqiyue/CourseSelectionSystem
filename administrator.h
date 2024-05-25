#ifndef _ADMINISTATOR_H 
#define _ADMINISTATOR_H

#include "role.h"
#include "teacher.h"

#include<map>

//管理员 有账号和密码 
/*
功能：录入课程信息、教室信息 
		分配教师账号密码 
		---------------------以下是高级功能 
		查询统计课程信息 
		查询每个老师名下课程的选课情况
		查询每个教室的上课信息
		查询学生的选课情况和缴费信息
		--------------------以下是亮点功能
		删除无人选课的课程
		修改课程名称和教室
		热门课程推荐
		所有添加删除修改过的数据均以文件形式保存，系统重启后能根据修改后的数据完成各种功能 
*/ 

//教室: 教室编号-教室名称 如 1101-第一教学楼101室 
typedef pair<int,string> Classroom;

//management 管理枚举 
enum MGMT{
	TEACHER_MGMT=0,
	CLASSROOM_MGMT,
	COURSE_MGMT,
	MGMT_MAX,
};

//管理功能字符串 
const char *mgmtStr[]={"管理教师信息","管理教室信息","管理课程信息","返回上一级"};

class Administrator{
private:
	bool hasAccount=false;
	bool hasLoaded=false;
	map<int,string> rooms; //教室 
	void createAdmin();
	bool login(); 
	
public:
	string adminAccount;//管理员账号 
	string password;//管理员密码
	void loadAccount(string account,string password); 
	void process();

}; 

void Administrator::loadAccount(string account,string password){
	this->adminAccount=account;
	this->password=password;
	hasAccount=true;
}

//管理员基本操作流程 
void Administrator::process(){
	int mgmtChoice=MGMT_MAX; 
	if(!hasAccount){
		createAdmin();
	}
	while(login()){
		clear();
		cout << "------管理员菜单-------" << endl;
		/*打印菜单选项 
		教师信息
			增 删 改  查 
		教室信息
			增 删 改  查 
		课程信息 
			增 删 改  查 
		*/
		mgmtChoice = getChoice("选择功能:", mgmtStr, MGMT_MAX);
		if(MGMT_MAX == mgmtChoice){
			continue;
		}
		//todo 实现具体功能 
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
	loginChoice = getChoice("", loginStr, LOGIN_MAX);
	if(LOGIN_MAX == loginChoice){
			return false;
	} 
	
	for(int i=0;i<LOGIN_RETRY_MAX;i++){
		cout << "请输入管理员账号名称:" ;
		cin >> inputAccount;
		if(inputAccount != adminAccount){
			cout << "账号不存在!请重新输入"  << endl;
			continue;
		}

		cout << "请输入管理员密码:" ;
		cin >> inputPasswd;
		if(inputPasswd != password){
			cout << "密码错误!请重新输入"  << endl;
			continue;
		}
		
		cout << "登陆成功" << endl;
		return true;
	}
	
	cout << "登陆次数超过" << LOGIN_RETRY_MAX << endl; 
	cout << "已退出" << endl;
	return false;
}

Administrator g_admin;

#endif
