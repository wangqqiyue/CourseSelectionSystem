/*�γ̶���ͷ�ļ�*/ 
#include "role.h"

/*
�γ��пγ����ơ���Ӧ���ҡ���ʦ��ѡ������ ���۸�� 
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
	string classroom;

	void setCourseId(int courseId);
	void setCourseName(string name); 
	void setStudentNumber(int number);
	void setPrice(float price);
	void setTeacher(int teacherId);
	void setClassroom(string classroom);
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
void Course::setClassroom(string classroom){
	this->classroom=classroom;
}

//��ӡ�γ�������Ϣ 
void Course::showCourseInfo(){
	//���ô�ӡ��� 
	setw(PRINT_WIDTH);
	cout << "�γ̱���" << "�γ���" << "ѡ������" <<  "�γ̼۸�" << "�ο���ʦ" << "����" << endl;
	cout << courseId  << courseName << studentNumber << price << teacherId << classroom << endl;
}
