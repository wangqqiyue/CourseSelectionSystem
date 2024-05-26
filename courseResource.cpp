#ifndef INCLUDE_COURSE_RESOURCE
#include "courseResource.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


vector<Course> g_courseList;
vector<Classroom> g_roomList;

bool Classroom::recordToStream(ostream& out){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_WIDTH)<<"���ұ��" << setw(Global::PRINT_LONG_WIDTH) << "��������" << setw(Global::PRINT_LONG_WIDTH) << "��������"<< endl;
	for(vector<Classroom>::iterator i=g_roomList.begin();i!=g_roomList.end();i++){
		out <<  setw(Global::PRINT_WIDTH)<<i->roomId << setw(Global::PRINT_LONG_WIDTH) <<	i->roomName << setw(Global::PRINT_LONG_WIDTH)  << i->capacity << endl;
	}
	return true;
}

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

bool Course::recordToStream(ostream& out){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_WIDTH)<<"�γ̱���" << setw(Global::PRINT_WIDTH) << "�γ���" << setw(Global::PRINT_LONG_WIDTH) << "ѡ������"<< setw(Global::PRINT_LONG_WIDTH) << "�γ̼۸�"<< setw(Global::PRINT_LONG_WIDTH) << "�ο���ʦ���"<< setw(Global::PRINT_LONG_WIDTH) << "���ұ��"<<endl;
	for(vector<Course>::iterator i=g_courseList.begin();i!=g_courseList.end();i++){
		out <<  setw(Global::PRINT_WIDTH)<<i->courseId << setw(Global::PRINT_WIDTH) <<	i->courseName << setw(Global::PRINT_LONG_WIDTH)  << i->studentNumber << setw(Global::PRINT_LONG_WIDTH)  << i->price << setw(Global::PRINT_LONG_WIDTH)  << i->teacherId << setw(Global::PRINT_LONG_WIDTH)  << i->classroomId << endl;
	}
	return true;
}

