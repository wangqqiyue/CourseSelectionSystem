#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif


int Global::LOGIN_RETRY_MAX=5;
int Global::PRINT_WIDTH=10;
int Global::PRINT_LONG_WIDTH=16;

int Global::TEACHER_NUMBER_MAX=100;
int Global::ROOM_NUMBER_MAX=100;
int Global::COURSE_NUMBER_MAX=100;
int Global::COURSE_PRICE_MAX=3000;
int Global::COURSE_CAPACITY_MAX=200;
int Global::COURSE_CAPACITY_MIN=20;

const char *Global::roleStr[]={"管理员","学生","老师","退出"};
const char *Global::loginStr[]={"登陆","返回上一级"};
const char *Global::operationStr[]={"新增","删除","修改","查询","返回上一级"};
const char *Global::mgmtStr[]={"管理教师信息","管理教室信息","管理课程信息","返回上一级"};
const char *Global::titleStr="培训中心管理系统";

//清空控制台
void clear(){
	system("cls");
}

//设置控制台标题 
void setTitle() {
	SetConsoleTitle(Global::titleStr);
}

//统一的欢迎界面,获取用户身份 
Global::Role greeting(){
	int role = -1;
	clear(); 
	cout << "-----主菜单-----"<< endl;
	cout << "欢迎使用" << Global::titleStr << endl;

	role = getChoice("您的身份是：",Global::roleStr,Global::ROLE_MAX);
	return (Global::Role)role;
}


//检查输入是否合规 
bool isInputOk(){
	//当我们在输入的时候，如果是整形变量int，我们输入char类型的字符，此时failbit的值会由0变为1
	if(cin.fail()){
		//输入的字符会卡在输入缓冲区导致后面无法进行输入操作
		cout << "请输入合法字符!" << endl;
		
		//我们首先使用cin>>clear()将falibit置为0让输入流可以正常工作，然后使ignore()取出缓冲区的字符，让下一次的输入可以正常运行。
		cin.clear();
		cin.ignore();
		return false;
	}
	return true;
}

//获取用户输入的选项 
int getChoice(const char* promptStr, const char **choiceStr, const int choiceMax){
	int choice = -1;
	//含choiceMax，用户可以选择退出/返回到上一级 
	while(choice > choiceMax || choice < 0){
		choice = -1;
		cout << promptStr <<endl;
		for(int i=0;i<=choiceMax;i++){
			cout << i << ". " << choiceStr[i] << endl;
		}
		cin >> choice;
		
		if(!isInputOk()){
			choice = -1;
		}
	}
	
	return choice;
}
