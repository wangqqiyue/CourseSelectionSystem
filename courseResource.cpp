#ifndef INCLUDE_COURSE_RESOURCE
#include "courseResource.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


vector<Course> g_courseList;
vector<Classroom> g_roomList;

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

bool Course::recordToStream(ostream& out){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_WIDTH)<<"课程编码" << setw(Global::PRINT_LONG_WIDTH) << "课程名" << setw(Global::PRINT_LONG_WIDTH) << "选课人数"<< setw(Global::PRINT_LONG_WIDTH) << "课程价格"<< setw(Global::PRINT_LONG_WIDTH) << "任课老师编号"<< setw(Global::PRINT_LONG_WIDTH) << "教室编号"<<endl;
	for(vector<Course>::iterator i=g_courseList.begin();i!=g_courseList.end();i++){
		out <<  setw(Global::PRINT_WIDTH)<<i->courseId << setw(Global::PRINT_LONG_WIDTH) <<	i->courseName << setw(Global::PRINT_LONG_WIDTH)  << i->studentNumber << setw(Global::PRINT_LONG_WIDTH) << fixed << setprecision(2) << i->price << setw(Global::PRINT_LONG_WIDTH)  << i->teacherId << setw(Global::PRINT_LONG_WIDTH)  << i->roomId << endl;
	}
	return true;
}

