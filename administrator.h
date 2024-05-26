#ifndef INCLUDE_ADMINISTATOR
#define INCLUDE_ADMINISTATOR

#ifndef INCLUDE_ROLE
#include "role.h"
#endif

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif


#ifndef INCLUDE_MAP
#include<map>
#define INCLUDE_MAP
#endif

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

//查询教师数据 
bool teacherInfoRetrieve(){
	clear();
	cout << "------教师信息查询-----"	<< endl;
	cout << setw(PRINT_WIDTH)<<"教师编号" << setw(PRINT_LONG_WIDTH) << "教师姓名" << setw(PRINT_LONG_WIDTH) << "密码"<< endl;
	for(vector<Teacher>::iterator i=g_teacherList.begin();i!=g_teacherList.end();i++){
		cout <<  setw(PRINT_WIDTH)<<i->teacherId << setw(PRINT_LONG_WIDTH) <<	i->name << setw(PRINT_LONG_WIDTH)  << i->password << endl;
	}
	cout << "按任意键返回上一级" << endl;
	cin.ignore();
	getchar();
	return true;
	
}

//管理教师信息 
bool teacherMgmt(){
	int opChoice = -1;
	while(OP_MAX != opChoice){
		opChoice = -1; 
		clear();
		cout << "------教师信息管理-----"  << endl;
		opChoice = getChoice("选择操作:", operationStr, OP_MAX);
		if(RETRIEVE == opChoice){
			return teacherInfoRetrieve();
		}	
	}
	return false;
}


//todo 完善管理功能 
bool classroomMgmt(){return false;}
bool courseMgmt(){return false;}

//由于默认只有一个管理员，不需要被实例化，所以设为静态类 
class Administrator{
public:
	static bool hasAccount;
	static bool hasLoaded;
	static map<int,string> rooms; //教室 
	static void createAdmin();
	static bool login(); 
	static bool (*mgmtFuncs[MGMT_MAX])();
	static string adminAccount;//管理员账号 
	static string password;//管理员密码
	static void process();

}; 

//静态成员变量需要在类外定义 
bool Administrator::hasAccount=false;
bool Administrator::hasLoaded=false;
string Administrator::adminAccount;
string Administrator::password;

bool (*Administrator::mgmtFuncs[MGMT_MAX])() = {teacherMgmt,NULL,NULL};

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
		while(MGMT_MAX != mgmtChoice){
			clear();
			cout << "------管理员菜单-------" << endl;
			mgmtChoice = getChoice("选择功能:", mgmtStr, MGMT_MAX);
			if(MGMT_MAX != mgmtChoice){
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
		if(inputPasswd != Administrator::password){
		
			cout << "密码错误!请重新输入"  << endl;
			cout <<"password="<<password<<endl;
		system("pause");
			continue;
		}
		
		cout << "登陆成功" << endl;
		return true;
	}
	
	cout << "登陆次数超过" << LOGIN_RETRY_MAX << endl; 
	cout << "已退出" << endl;
	return false;
}


#endif
