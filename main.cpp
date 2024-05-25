#ifndef INCLUDE_MENU
#include "menu.h"
#endif

int main(int argc, char** argv) {
	bool exitSystem = false; 
	
	//设置标题 
	setTitle(); 

	//加载系统信息
	loadInfo();
	 
	while(!exitSystem){
		Role role = ROLE_MAX;
		//获取用户身份 
		role = greeting();
	
		
		//确认身份并根据身份不同登陆不同的界面 
		if(role == ADMINISTRATOR){
			g_admin.process();
		}else if(role == TEACHER){
			if(!g_teacherList.empty()){
				if(g_teacherList[0].login()){
					cout << "登陆成功" << endl;
				}
			}
		}else{
			exitSystem = true;
		}
	
		//存储信息到外部文件
		storeInfo();
		
	} 
	return 0;
}
