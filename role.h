#ifndef INCLUDE_ROLE
#define INCLUDE_ROLE

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

/*用户角色定义头文件*/
enum Role{
	ADMINISTRATOR=0,
	STUDENT,
	TEACHER,
	ROLE_MAX,
};

const char *roleStr[]={"管理员","学生","老师","退出"};

enum LoginChoice{
	LOGIN=0,
	LOGIN_MAX,
};

const char *loginStr[]={"登陆","返回上一级"};

//数据操作枚举 
enum OPERATION{
	CREATE=0,//增 
	DEL,//删 
	UPDATE,//改 
	RETRIEVE,//查 
	OP_MAX,
};

//管理功能字符串 
const char *operationStr[]={"新增","删除","修改","查询","返回上一级"};

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
}; 

int Global::LOGIN_RETRY_MAX=5;
int Global::PRINT_WIDTH=8;
int Global::PRINT_LONG_WIDTH=16;
int Global::TEACHER_NUMBER_MAX=100;

//清空控制台
void clear(){
	system("cls");
}

int getChoice(const char* promptStr, const char **choiceStr, const int choiceMax){
	int choice = -1;
	//含choiceMax，用户可以选择退出/返回到上一级 
	while(choice > choiceMax || choice < 0){
		cout << promptStr <<endl;
		for(int i=0;i<=choiceMax;i++){
			cout << i << ". " << choiceStr[i] << endl;
		}
		cin >> choice;
		
		//当我们在输入的时候，如果是整形变量int，我们输入char类型的字符，此时failbit的值会由0变为1
		if(cin.fail()==true){
			//输入的字符会卡在输入缓冲区导致后面无法进行输入操作
			cout << "请输入合法字符!" << endl;
			
			//我们首先使用cin>>clear()将falibit置为0让输入流可以正常工作，然后使ignore()取出缓冲区的字符，让下一次的输入可以正常运行。
			cin.clear();
			cin.ignore();
			choice = -1;
		}
	}
	
	return choice;
}

#endif
