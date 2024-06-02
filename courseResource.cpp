#ifndef INCLUDE_COURSE_RESOURCE
#include "courseResource.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


vector<Course> g_courseList;
vector<Classroom> g_roomList;

//�ȿ����ں��������У�Ҳ�����ں�������������ȱʡ�����������ܼ��ں������������ں���������ͬʱ����ȱʡ������
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

bool Classroom::checkExist(int id, vector<Classroom>::iterator &i){
	for(i=g_roomList.begin();i!=g_roomList.end();i++){
		if(i->roomId == id){
			return true;
		}
	}
	return false;
}

//���������󣬵�����, �Ƿ�ֻ��ӡһ����¼ 
bool Course::recordToStream(ostream& out, vector<Course>::iterator firstRecord, bool onlyOne){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}

	out << setw(Global::PRINT_WIDTH)<<"�γ̱���" << setw(Global::PRINT_LONG_WIDTH) << "�γ���" << setw(Global::PRINT_LONG_WIDTH) << "ѡ������"<< setw(Global::PRINT_LONG_WIDTH) << "�γ̼۸�"<< setw(Global::PRINT_LONG_WIDTH) << "�ο���ʦ���"<< setw(Global::PRINT_LONG_WIDTH) << "���ұ��" << setw(Global::PRINT_LONG_WIDTH) <<  "�γ������޶�" <<endl;
	

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

