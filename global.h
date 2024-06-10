/*
所有文件需要的库头文件 
*/

#ifndef INCLUDE_GLOBAL
#define INCLUDE_GLOBAL

#ifndef INCLUDE_IOMANIP
#include <iomanip>
#define INCLUDE_IOMANIP
#endif

#ifndef INCLUDE_IOSTREAM
#include <iostream>
#define INCLUDE_IOSTREAM
#endif 

#ifndef INCLUDE_MINWINDEF
#include <minwindef.h>
#define INCLUDE_MINWINDEF
#endif 


#ifndef INCLUDE_VECTOR
#include <vector>
#define INCLUDE_VECTOR
#endif


using namespace std;

//宏定义全局变量类 
class Global{
public:
	//登陆最多尝试次数 
	static int LOGIN_RETRY_MAX;

	//打印字符宽度 
	static int PRINT_WIDTH;
	static int PRINT_LONG_WIDTH;

	//最多老师人数
	static int TEACHER_NUMBER_MAX;
	//最大教室数量 
	static int ROOM_NUMBER_MAX; 
	//最大课程数量 
	static int COURSE_NUMBER_MAX; 
	//最大课程价格 
	static int COURSE_PRICE_MAX;
	//最大课程人数限额 
	static int COURSE_CAPACITY_MAX;
	//最小课程人数限额 
	static int COURSE_CAPACITY_MIN;
	//最大课程人数限额 
	static int ROOM_CAPACITY_MAX;
	//最小课程人数限额 
	static int ROOM_CAPACITY_MIN;
	//身份证号长度 
	static int ID_LENGTH;
	//手机号长度 
	static int TEL_LENGTH;
	
		
	/*用户角色定义头文件*/
	enum Role{
		ADMINISTRATOR=0,
		STUDENT,
		TEACHER,
		ROLE_MAX,
	};
	
	static const char *roleStr[];
	
	enum LoginChoice{
		LOGIN=0,
		LOGIN_MAX,
	};
	
	static const char *loginStr[];

	enum StuLoginChoice{
		STU_SIGNUP=0,
		STU_LOGIN,
		STU_LOGIN_MAX,
	};
	
	static const char *stuLoginStr[];

	enum greetingChoice{
		GREETING_CONTINUE=0,
		GREETING_ABOUT,
		GREETING_MAX,
	};
	
	static const char *greetingStr[];

	static const char *aboutInfoFile;

	//数据操作枚举 
	enum OPERATION{
		CREATE=0,//增 
		DEL,//删 
		UPDATE,//改 
		RETRIEVE,//查 
		OP_MAX,
	};
	
	//管理功能字符串 
	static const char *operationStr[];
	
	//management 管理枚举 
	enum MGMT{
		TEACHER_MGMT=0,
		CLASSROOM_MGMT,
		COURSE_MGMT,
		MGMT_MAX,
	};
	
	//管理功能字符串 
	static const char *mgmtStr[];
	
	//学生功能枚举 
	enum STU_FUNC{
		LIST_SELECTED_COURSE=0,//查看已选课程 
		SHOW_ALL_COURSE,//查看所有课程 
		SELECT_COURSE,//选课
		WITHDRAW_COURSE,//退课
		PAY_ORDER,//付款 
		STU_FUNC_MAX,
	};
	
	//教师功能字符串 
	static const char *teacherFuncStr[];
	
	//教师功能枚举 
	enum TEACHER_FUNC{
		SHOW_TEACHER_COURSE=0,//查看已选课程 
		SHOW_ROSTER,//查看学生名单 
		TEACHER_FUNC_MAX,
	};
	
	//学生功能字符串 
	static const char *stuFuncStr[];	
	
	//程序标题字符串 
	static const char *titleStr;
}; 


//清空控制台
void clear();

//设置控制台标题 
void setTitle();

//设置控制台颜色 
void setConsoleColor(WORD color);

//统一的欢迎界面
bool greeting();

//打印帮助信息 
bool printAboutInfo();

 //获取用户身份
Global::Role getRole();

//检查输入是否合规 
bool isInputOk();

//获取用户输入的选项 
int getChoice(const char* promptStr, const char **choiceStr, const int choiceMax);

//设置密码
string setPassword();

//登陆
bool login(Global::Role role);

//返回上一级
void goPrevious();

//任意键继续 
void goContinue();

//检查是否存在id 
template<class T>
bool checkExist(const vector<T>& vec, const T& target){
	for(typename vector<T>::const_iterator i=vec.begin();i!=vec.end();i++){
		if(*i == target){
			return true;
		}
	}
	return false;
}

 bool checkAllZero(int *selectList, int total);
 
#endif
