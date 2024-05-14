#include "menu.h"

int main(int argc, char** argv) {
	Role role = ROLE_MAX;
	
	//设置标题 
	setTitle(); 

	//获取用户身份 
	role = greeting();
	
	//确认身份并根据身份不同登陆不同的界面 
	clear();
	cout << roleStr[role] << endl;

	return 0;
}
