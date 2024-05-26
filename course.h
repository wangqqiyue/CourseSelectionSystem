#ifndef INCLUDE_COURSE
#define INCLUDE_COURSE

#ifndef INCLUDE_ROLE
/*课程定义头文件*/ 
#include "role.h"
#endif

class Classroom{
	int classroomId;
	int capacity;//教室学生容量 
	string classroomName;
};


/*
课程有课程名称、对应教室、老师、选课人数 、价格等 
默认每门课只有一个老师 
功能：
	修改课程名称
	修改课程人数
	修改课程价格
	修改老师
	修改教室  
*/
class Course{
public:
	int courseId;
	string courseName;
	int studentNumber;
	float price;
	int teacherId;
	int classroomId;

	Course(int id,string name,int num,float p,int tId,int cId):courseId(id),courseName(name),studentNumber(num),price(p),teacherId(tId),classroomId(cId){}
	void setCourseId(int courseId);
	void setCourseName(string name); 
	void setStudentNumber(int number);
	void setPrice(float price);
	void setTeacher(int teacherId);
	void setClassroom(int classroom);
	void showCourseInfo();
};

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

#endif
