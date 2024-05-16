#include "menu.h"

int main(int argc, char** argv) {
	Role role = ROLE_MAX;
	
	//设置标题 
	setTitle(); 

	//加载系统信息
	loadInfo();
	 
	//获取用户身份 
	role = greeting();
	
	//确认身份并根据身份不同登陆不同的界面 
	clear();
	if(role == ADMINISTRATOR){
		g_admin.process();
	}

	//存储信息到外部文件
	storeInfo();
	 
	return 0;
}
