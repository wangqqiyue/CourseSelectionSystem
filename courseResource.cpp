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

//��ӡ�γ�������Ϣ 
void Course::showCourseInfo(){
	//���ô�ӡ��� 
	setw(Global::PRINT_WIDTH);
	cout << "�γ̱���" << "�γ���" << "ѡ������" <<  "�γ̼۸�" << "�ο���ʦ���" << "���ұ��" << endl;
	cout << courseId  << courseName << studentNumber << price << teacherId << classroomId << endl;
}


