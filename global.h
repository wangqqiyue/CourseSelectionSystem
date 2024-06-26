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

#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif

#ifndef INCLUDE_CONIO
#include <conio.h>
#define INCLUDE_CONIO
#endif

#ifndef INCLUDE_VECTOR
#include <vector>
#define INCLUDE_VECTOR
#endif


#ifndef INCLUDE_FSTREAM
#include <fstream>
#define INCLUDE_FSTREAM
#endif

#ifndef INCLUDE_SSTREAM
#include <sstream>
#define INCLUDE_SSTREAM
#endif

#ifndef INCLUDE_STRING
#include <string>
#define INCLUDE_STRING
#endif

/*规范 Std 命名空间*/
using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::stringstream;
using std::vector;
using std::string;
using std::pair;
using std::fixed;
using std::setprecision;

//宏定义全局变量类 
class Global{
public:
	//登陆最多尝试次数 
	static const int LOGIN_RETRY_MAX;

	//打印字符宽度 
	static const int PRINT_WIDTH;
	static const int PRINT_LONG_WIDTH;

	//最多老师人数
	static const int TEACHER_NUMBER_MAX;
	//最大教室数量 
	static const int ROOM_NUMBER_MAX; 
	//最大课程数量 
	static const int COURSE_NUMBER_MAX; 
	//最大课程价格 
	static const int COURSE_PRICE_MAX;
	//最大课程人数限额 
	static const int COURSE_CAPACITY_MAX;
	//最小课程人数限额 
	static const int COURSE_CAPACITY_MIN;
	//最大课程人数限额 
	static const int ROOM_CAPACITY_MAX;
	//最小课程人数限额 
	static const int ROOM_CAPACITY_MIN;
	//身份证号长度 
	static const int ID_LENGTH;
	//手机号长度 
	static const int TEL_LENGTH;
	//可上课时间段 
	static const int COURSE_HOURS_LENGTH;
	
	//上课时段字符串 
	static const char *courseHourStr[];	
	
		
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

//设置控制台颜色 
void setConsoleColor(WORD color);

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
bool checkExist(const std::vector<T>& vec, const T& target){
	for(typename std::vector<T>::const_iterator i=vec.begin();i!=vec.end();i++){
		if(*i == target){
			return true;
		}
	}
	return false;
}

 bool checkAllZero(int *selectList, int total);
 
#endif
