#ifndef INCLUDE_COURSE_RESOURCE
#include "courseResource.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


vector<Course> g_courseList;
vector<Classroom> g_roomList;

//既可以在函数声明中，也可以在函数定义中声明缺省参数，但不能既在函数声明中又在函数定义中同时声明缺省参数。
bool Classroom::recordToStream(ostream& out){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_WIDTH)<<"教室编号" << setw(Global::PRINT_LONG_WIDTH) << "教室名称" << setw(Global::PRINT_LONG_WIDTH) << "教室容量"<< endl;
	for(vector<Classroom>::iterator i=g_roomList.begin();i!=g_roomList.end();i++){
		out <<  setw(Global::PRINT_WIDTH)<<i->roomId << setw(Global::PRINT_LONG_WIDTH) <<	i->roomName << setw(Global::PRINT_LONG_WIDTH)  << i->capacity << endl;
	}
	return true;
}

bool Classroom::checkExist(int id, vector<Classroom>::iterator &i){
	for(i=g_roomList.begin();i!=g_roomList.end();i++){
		if(i->roomId == id){
			return true;
		}
	}
	return false;
}

//传入流对象，迭代器, 是否只打印一条记录 
bool Course::recordToStream(ostream& out, vector<Course>::iterator firstRecord, bool onlyOne){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}

	out << setw(Global::PRINT_WIDTH)<<"课程编码" << setw(Global::PRINT_LONG_WIDTH) << "课程名" << setw(Global::PRINT_LONG_WIDTH) << "选课人数"<< setw(Global::PRINT_LONG_WIDTH) << "课程价格"<< setw(Global::PRINT_LONG_WIDTH) << "任课老师编号"<< setw(Global::PRINT_LONG_WIDTH) << "教室编号" << setw(Global::PRINT_LONG_WIDTH) <<  "课程人数限额" <<endl;
	

	for(vector<Course>::iterator i = g_courseList.begin();i!=g_courseList.end();i++){
		if(onlyOne){
			i=firstRecord;
		}
		out <<  setw(Global::PRINT_WIDTH)<<i->courseId << setw(Global::PRINT_LONG_WIDTH) <<	i->courseName << setw(Global::PRINT_LONG_WIDTH)  << i->studentNumber << setw(Global::PRINT_LONG_WIDTH) << fixed << setprecision(2) << i->price << setw(Global::PRINT_LONG_WIDTH)  << i->teacherAccount << setw(Global::PRINT_LONG_WIDTH)  << i->roomId << setw(Global::PRINT_LONG_WIDTH)  << i->capacity << endl;
		if(onlyOne){
			break;
		}		
	}
	return true;
}

