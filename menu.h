/*菜单和界面格式头文件*/
#include <windows.h>
#include <iostream>

#include "users.h"
#include "courses.h"


using namespace std;
const char *titleStr="培训中心管理系统";


//设置控制台标题 
void setTitle() {
	SetConsoleTitle(titleStr);
}

//清空控制台
void clear(){
	system("cls");
}

//统一的欢迎界面,获取用户身份 
Role greeting(){
	int role = ROLE_MAX;
	cout << "欢迎使用" << titleStr << endl;
	cout << endl;
	while(role >= ROLE_MAX || role < 0){
		cout << "您的身份是：" << endl;
		for(int i=0;i<ROLE_MAX;i++){
			cout << i << ". " << roleStr[i] << endl;
		}
		cin >> role;
	}
	return (Role)role;
}



