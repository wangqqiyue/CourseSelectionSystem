#ifndef INCLUDE_RECORD_PROCESS
#include "recordProcess.h" 
#endif

#ifndef INCLUDE_COURSE
#include "course.h"
#endif

#ifndef INCLUDE_ADMINISTATOR
#include "administrator.h"
#endif 

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif


#ifndef INCLUDE_SELECTION_TABLE
#include "selectionTable.h"
#endif

#ifndef INCLUDE_CLASSROOM
#include "classroom.h"
#endif


//信息加载 
void loadInfo(){
	cout << "系统数据加载中..." << endl;
	
	//加载管理员信息	
	Administrator::loadInfo();
	
	//加载教师信息 
	Teacher::loadInfo();
	
	//加载课程信息
	Course::loadInfo();
	
	//加载教室信息
	Classroom::loadInfo();
	
	//加载学生信息
	Student::loadInfo();
	
	//加载选课表 
	CourseSelectionTable::loadInfo();
	
	cout << "系统数据加载完毕" << endl;
}


//信息存储
void storeInfo(){
	cout << "系统数据存储中..." << endl;

	//存储管理员信息 
	Administrator::storeInfo();
	
	//存储教师信息 
	Teacher::storeInfo();
	
	//存储课程信息 
	Course::storeInfo();
	
	//存储教室信息 
	Classroom::storeInfo();
	
	//存储教室信息 
	Student::storeInfo();
	
	//存储选课表信息 
	CourseSelectionTable::storeInfo();
	
	cout << "系统数据存储完毕" << endl;
}

void mainLoop(){
	static bool firstRun = true;
	if(firstRun){
		//设置标题 
		setTitle(); 		
		firstRun = false;
	}

	
	while(greeting()){		 
		int role = -1;
		//持续获取用户身份 
		while(Global::ROLE_MAX != role){
			role = getRole();
	
			//确认身份并根据身份不同登陆不同的界面 
			if(role == Global::ADMINISTRATOR){
				Administrator::process();
			}else if(role == Global::TEACHER){
				Teacher::process();
			}else if(role == Global::STUDENT){
				Student::process();
			}	
		}
	}
}

//系统信号钩子
BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
        // CTRL-CLOSE: 关闭窗口时存储当前信息到外部文件,再退出系统 
	    case CTRL_CLOSE_EVENT:
	        Beep(600, 200);
	        
	        //存储信息到外部文件
			storeInfo();
			Sleep(1000);
	        return TRUE;
	
	    default:
	        return FALSE;
    }
}


//设置控制台标题 
void setTitle() {
	SetConsoleTitle(Global::titleStr);
}

//统一的欢迎界面,获取用户身份 
bool greeting(){
	int choice  = -1;
	clear(); 
	cout << "欢迎使用" << Global::titleStr << endl;
	choice = getChoice("请选择",Global::greetingStr,Global::GREETING_MAX);
	clear();
	if(Global::GREETING_CONTINUE == choice){
		return true;
	}else if(Global::GREETING_ABOUT == choice){
		printAboutInfo();
		goContinue();
		return true;
	}else if(Global::GREETING_MAX == choice){
		return false;
	}	
}

//打印帮助信息 
bool printAboutInfo(){
	ifstream in;
	string line;
	
	//加载关于信息 
	in.open(Global::aboutInfoFile,ios::in);
	if(!in){
		return false;
	}

	while(getline(in,line)){
		cout << line << endl;
	}		
	in.close();	
	
	return true;
}

//统一的欢迎界面,获取用户身份 
Global::Role getRole(){
	int role = -1;
	clear(); 
	cout << "---------------访客身份选择-----------------" << endl;
	role = getChoice("您的身份是：",Global::roleStr,Global::ROLE_MAX);
	return (Global::Role)role;
}

