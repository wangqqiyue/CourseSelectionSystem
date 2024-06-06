#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_COURSE_RESOURCE
#include "courseResource.h"
#endif

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

vector<Teacher> teacherList;

//函数指针数组的初始化 
bool (*Teacher::teacherFuncs[Global::TEACHER_FUNC_MAX])() = {Teacher::showTeacherCourse,Teacher::showRoster};
string Teacher::login_account = "";//当前登陆账号 

//学生基本操作流程 
void Teacher::process(){
	while(login(Global::TEACHER)){
		int funcChoice = -1;
		while(Global::TEACHER_FUNC_MAX != funcChoice){
			clear();
			cout << "--------教师功能菜单---------" << endl;
			funcChoice = getChoice("选择功能:", Global::teacherFuncStr, Global::TEACHER_FUNC_MAX);
			if(Global::TEACHER_FUNC_MAX != funcChoice){
				//不断执行操作，直到返回错误退出 
				teacherFuncs[funcChoice]();
			}
		}

	}
}


bool Teacher::checkAccountExist(string account){
	for(vector<Teacher>::iterator  i=teacherList.begin();i!=teacherList.end();++i){
		if(i->account == account){
			return true;
		}
	}
	return false;
}

bool Teacher::checkAccountExist(string account, vector<Teacher>::iterator &i){
	for(i=teacherList.begin();i!=teacherList.end();++i){
		if(i->account == account){
			return true;
		}
	}
	return false;
}

bool Teacher::recordToStream(ostream& out, vector<Teacher>::iterator firstRecord, bool onlyOne){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_WIDTH)<<"教师帐号" << setw(Global::PRINT_LONG_WIDTH) << "教师姓名" << setw(Global::PRINT_LONG_WIDTH) << "密码"<< endl;
	for(vector<Teacher>::iterator i=teacherList.begin();i!=teacherList.end();i++){
		if(onlyOne){
			i=firstRecord;
		}
		out <<  setw(Global::PRINT_WIDTH)<<i->account << setw(Global::PRINT_LONG_WIDTH) <<	i->name << setw(Global::PRINT_LONG_WIDTH)  << i->password << endl;
		if(onlyOne){
			break;
		}
	}
	return true;
} 

//根据教师账号返回教师元素的指针 
Teacher* Teacher::getElementByAccount(string account){
		for(vector<Teacher>::iterator i=teacherList.begin();i!=teacherList.end();i++){
		if(i->account == account){
			return const_cast<Teacher*>(&(*i));
		}
	}
}

//打印当前教师名下的课程 
bool Teacher::showTeacherCourse(){
	bool result = true;

	clear();
	cout <<"-------------您名下的课程 -------------------------" << endl;
	Teacher *teacher=getElementByAccount(login_account);
	if(!teacher){
		cerr<<"账号为" << login_account << "的教师不存在" << endl;
		result = false;
	}
	
	cout << setw(Global::PRINT_LONG_WIDTH) << "课程名" << setw(Global::PRINT_WIDTH) << "选课人数" << setw(Global::PRINT_LONG_WIDTH) << "教室" << endl;
	for(vector<Course>::iterator i=g_courseList.begin();i!=g_courseList.end();i++){
		Classroom* room;
		if(i->teacherAccount == login_account){
			room = Classroom::getElementById(i->roomId);
			if(!room){
				cerr << "编号为" << i->roomId << "的教室不存在" << endl;
				result = false;
			}
			cout << setw(Global::PRINT_LONG_WIDTH) << i->courseName <<  setw(Global::PRINT_WIDTH) << i->studentNumber <<  setw(Global::PRINT_LONG_WIDTH) << room->roomName << endl;
		}
	}
	goPrevious();
	return result;
}

//打印学生花名册
bool Teacher::showRoster(){
	bool result = true;

	clear();
	cout <<"-------------您名下的课程的学生花名册 -------------------------" << endl;
	
	Teacher *teacher=getElementByAccount(login_account);
	if(!teacher){
		cerr<<"账号为" << login_account << "的教师不存在" << endl;
		result = false;
	}
	
	cout << setw(Global::PRINT_LONG_WIDTH) << "课程名" << setw(Global::PRINT_WIDTH) << "选课人数" << setw(Global::PRINT_LONG_WIDTH) << "教室" << endl;
	for(vector<Course>::iterator i=g_courseList.begin();i!=g_courseList.end();i++){
		Classroom* room;
		if(i->teacherAccount == login_account){
			room = Classroom::getElementById(i->roomId);
			if(!room){
				cerr << "编号为" << i->roomId << "的教室不存在" << endl;
				result = false;
			}
			cout << setw(Global::PRINT_LONG_WIDTH) << i->courseName <<  setw(Global::PRINT_WIDTH) << i->studentNumber <<  setw(Global::PRINT_LONG_WIDTH) << room->roomName << endl;
			if(0 == i->studentNumber){
				cout << "暂无学生选此门课程" << endl;
				continue;
			}
			
			cout <<"-------花名册-----" << endl;
			vector<string> studentList = CourseSelectionTable::paidOrder.getStudentByCourse(i->courseId);
			int  rosterNumber = 1;//花名单序号 
			for(vector<string>::iterator j=studentList.begin();j!=studentList.end();j++,rosterNumber++){
				Student* student = Student::getElementByAccount(*j);\
				if(!student){
					cerr << "账号为" << *j <<"的学生不存在" << endl;
					result = false;
				}
				cout << rosterNumber << ". " << student->name << endl;
			}
			cout << endl;
		}
	}
	goPrevious();
	return result;
} 
