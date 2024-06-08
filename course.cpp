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

/*-----------------Course 定义实现-------------------------------------*/ 
vector<Course> Course::courseList;

const char* Course::dataFile = "coursesInfo.txt"; 

bool Course::storeInfo(){
	bool result = true;
	ofstream out;
	//加载管理员账号密码
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
	
	//加载管理员账号密码
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
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	out << setw(Global::PRINT_WIDTH)<<"课程编码" << setw(Global::PRINT_LONG_WIDTH) << "课程名" << setw(Global::PRINT_WIDTH) << "选课人数"<< setw(Global::PRINT_WIDTH) << "课程价格"<< setw(Global::PRINT_WIDTH) << "任课老师"<< setw(Global::PRINT_WIDTH) << "教室" << setw(Global::PRINT_WIDTH) <<  "人数限额" <<endl;	
	return true;
}

//传入流对象，迭代器, 是否只打印一条记录 
bool Course::recordToStream(ostream& out, vector<Course>::iterator firstRecord, bool onlyOne){ 
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
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
