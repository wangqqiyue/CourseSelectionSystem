#ifndef INCLUDE_COURSE
#include "course.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_FSTREAM
#include <fstream>
#define INCLUDE_FSTREAM
#endif

#ifndef INCLUDE_SSTREAM
#include <sstream>
#define INCLUDE_SSTREAM
#endif

/*-----------------Course ����ʵ��-------------------------------------*/ 
vector<Course> Course::courseList;

const char* Course::dataFile = "coursesInfo.txt"; 

bool Course::storeInfo(){
	bool result = true;
	ofstream out;
	//���ع���Ա�˺�����
	out.open(dataFile,ios::out);
	if(!Course::recordToStream(out,Course::courseList.begin())){
		result= false;
	}

	out.close();
	return result;
}

bool Course::loadInfo(){
	ifstream in;
	string temp;
	
	//���ع���Ա�˺�����
	in.open(dataFile,ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		int courseId,number,classroomId,capacity;
		float price;
		string courseName,teacherAccount;
		
		stringstream ss(temp);
		ss >> courseId;
		ss >> courseName;
		ss >> number;
		ss >> price;
		ss >> teacherAccount;
		ss >> classroomId;
		ss >> capacity;
		
		Course c(courseId,courseName,number,price,teacherAccount,classroomId,capacity);
		Course::courseList.push_back(c);
	}
	in.close();
}

bool Course::printTitleToStream(ostream& out){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	out << setw(Global::PRINT_WIDTH)<<"�γ̱���" << setw(Global::PRINT_LONG_WIDTH) << "�γ���" << setw(Global::PRINT_WIDTH) << "ѡ������"<< setw(Global::PRINT_WIDTH) << "�γ̼۸�"<< setw(Global::PRINT_WIDTH) << "�ο���ʦ"<< setw(Global::PRINT_WIDTH) << "����" << setw(Global::PRINT_WIDTH) <<  "�����޶�" <<endl;	
	return true;
}

//���������󣬵�����, �Ƿ�ֻ��ӡһ����¼ 
bool Course::recordToStream(ostream& out, vector<Course>::iterator firstRecord, bool onlyOne){ 
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}

	if(!onlyOne){
		printTitleToStream(out);	
	}		
	
	for(vector<Course>::iterator i = Course::courseList.begin();i!=Course::courseList.end();i++){
		if(onlyOne){
			i=firstRecord;
		}
		out <<  setw(Global::PRINT_WIDTH)<<i->courseId << setw(Global::PRINT_LONG_WIDTH) <<	i->courseName << setw(Global::PRINT_WIDTH)  << i->studentNumber << setw(Global::PRINT_WIDTH) << fixed << setprecision(2) << i->price << setw(Global::PRINT_WIDTH)  << i->teacherAccount << setw(Global::PRINT_WIDTH)  << i->roomId << setw(Global::PRINT_WIDTH)  << i->capacity << endl;
		if(onlyOne){
			break;
		}		
	}
	return true;
}

Course* Course::getElementById(int id){
		for(vector<Course>::iterator i=Course::courseList.begin();i!=Course::courseList.end();i++){
		if(i->courseId == id){
			return const_cast<Course*>(&(*i));
		}
	}
}
