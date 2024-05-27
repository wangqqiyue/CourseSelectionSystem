#ifndef INCLUDE_COURSE_RESOURCE
#include "courseResource.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


vector<Course> g_courseList;
vector<Classroom> g_roomList;

//既可以在函数声明中，也可以在函数定义中声明缺省参数，但不能既在函数声明中又在函数定义中同时声明缺省参数。
bool Classroom::recordToStream(ostream& out, bool tailOnly){
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

//当tailOnly为真时，仅打印尾元素 
bool Course::recordToStream(ostream& out, bool tailOnly){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}

	out << setw(Global::PRINT_WIDTH)<<"课程编码" << setw(Global::PRINT_LONG_WIDTH) << "课程名" << setw(Global::PRINT_LONG_WIDTH) << "选课人数"<< setw(Global::PRINT_LONG_WIDTH) << "课程价格"<< setw(Global::PRINT_LONG_WIDTH) << "任课老师编号"<< setw(Global::PRINT_LONG_WIDTH) << "教室编号" << setw(Global::PRINT_LONG_WIDTH) <<  "课程人数限额" <<endl;
	
	for(vector<Course>::iterator i = g_courseList.begin();i!=g_courseList.end();i++){
		if(tailOnly){
			i = g_courseList.end();
			--i;//获取向量最后一个元素 
		}
		out <<  setw(Global::PRINT_WIDTH)<<i->courseId << setw(Global::PRINT_LONG_WIDTH) <<	i->courseName << setw(Global::PRINT_LONG_WIDTH)  << i->studentNumber << setw(Global::PRINT_LONG_WIDTH) << fixed << setprecision(2) << i->price << setw(Global::PRINT_LONG_WIDTH)  << i->teacherId << setw(Global::PRINT_LONG_WIDTH)  << i->roomId << setw(Global::PRINT_LONG_WIDTH)  << i->capacity << endl;
	}
	return true;
}

