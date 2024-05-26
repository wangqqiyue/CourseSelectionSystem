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

//��ӡ�γ�������Ϣ 
void Course::showCourseInfo(){
	//���ô�ӡ��� 
	setw(Global::PRINT_WIDTH);
	cout << "�γ̱���" << "�γ���" << "ѡ������" <<  "�γ̼۸�" << "�ο���ʦ���" << "���ұ��" << endl;
	cout << courseId  << courseName << studentNumber << price << teacherId << classroomId << endl;
}


