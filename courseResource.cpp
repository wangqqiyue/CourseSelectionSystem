#ifndef INCLUDE_COURSE_RESOURCE
#include "courseResource.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


vector<Course> g_courseList;

void Course::setCourseId(int courseId){
	this->courseId = courseId;
	
}
void Course::setCourseName(string name){
	courseName =name;
}

void Course::setStudentNumber(int number){
	studentNumber=number;
}

void Course::setPrice(float price){
	this->price=price;
}
void Course::setTeacher(int teacherId){
	this->teacherId=teacherId;
}
void Course::setClassroom(int classroom){
	this->classroomId=classroom;
}

//打印课程完整信息 
void Course::showCourseInfo(){
	//设置打印宽度 
	setw(Global::PRINT_WIDTH);
	cout << "课程编码" << "课程名" << "选课人数" <<  "课程价格" << "任课老师编号" << "教室编号" << endl;
	cout << courseId  << courseName << studentNumber << price << teacherId << classroomId << endl;
}


