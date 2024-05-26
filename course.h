#ifndef INCLUDE_COURSE
#define INCLUDE_COURSE

#ifndef INCLUDE_ROLE
/*�γ̶���ͷ�ļ�*/ 
#include "role.h"
#endif

class Classroom{
	int classroomId;
	int capacity;//����ѧ������ 
	string classroomName;
};


/*
�γ��пγ����ơ���Ӧ���ҡ���ʦ��ѡ������ ���۸�� 
Ĭ��ÿ�ſ�ֻ��һ����ʦ 
���ܣ�
	�޸Ŀγ�����
	�޸Ŀγ�����
	�޸Ŀγ̼۸�
	�޸���ʦ
	�޸Ľ���  
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

//��ӡ�γ�������Ϣ 
void Course::showCourseInfo(){
	//���ô�ӡ��� 
	setw(Global::PRINT_WIDTH);
	cout << "�γ̱���" << "�γ���" << "ѡ������" <<  "�γ̼۸�" << "�ο���ʦ���" << "���ұ��" << endl;
	cout << courseId  << courseName << studentNumber << price << teacherId << classroomId << endl;
}

#endif
