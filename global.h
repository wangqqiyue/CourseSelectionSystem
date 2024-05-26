#ifndef INCLUDE_GLOBAL
#define INCLUDE_GLOBAL


#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif

#ifndef INCLUDE_IOSTREAM
#include <iostream>
#define INCLUDE_IOSTREAM
#endif 

#ifndef INCLUDE_STRING
#include <string>
#define INCLUDE_STRING
#endif

#ifndef INCLUDE_IOMANIP
#include <iomanip>
#define INCLUDE_IOMANIP
#endif

#ifndef INCLUDE_VECTOR
#include <vector>
#define INCLUDE_VECTOR
#endif

#ifndef INCLUDE_ALGORITHM
#include <algorithm>
#define INCLUDE_ALGORITHM
#endif

#ifndef INCLUDE_FUNCTIONAL
#include <functional>
#define INCLUDE_FUNCTIONAL
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
	
	//程序标题字符串 
	static const char *titleStr;
}; 


//清空控制台
void clear();

//设置控制台标题 
void setTitle();

//统一的欢迎界面,获取用户身份 
Global::Role greeting();

//检查输入是否合规 
bool isInputOk();

//获取用户输入的选项 
int getChoice(const char* promptStr, const char **choiceStr, const int choiceMax);

#endif
