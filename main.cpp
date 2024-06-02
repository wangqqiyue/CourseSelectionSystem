#ifndef INCLUDE_RECORD_PROCESS
#include "recordProcess.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_ADMINISTATOR
#include "administrator.h"
#endif

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif


int main(int argc, char** argv) {
	bool exitSystem = false; 
	
	//设置标题 
	setTitle(); 

	//加载系统信息
	loadInfo();
	 
	while(!exitSystem){
		Global::Role role = Global::ROLE_MAX;
		//获取用户身份 
		role = greeting();
	
		
		//确认身份并根据身份不同登陆不同的界面 
		if(role == Global::ADMINISTRATOR){
			Administrator::process();
		}else if(role == Global::TEACHER){
			if(login(Global::TEACHER)){
				cout << "登陆成功" << endl;
				system("pause");
			}
			
		}else if(role == Global::STUDENT){
			Student::process();
		}else{
			exitSystem = true;
		}	
	} 
	
	//存储信息到外部文件
	storeInfo();
	return 0;
}
