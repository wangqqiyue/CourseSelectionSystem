#ifndef INCLUDE_CLASSROOM
#include "classroom.h"
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


/*-----------------Classroom 定义实现-------------------------------------*/ 

vector<Classroom> Classroom::roomList;

//既可以在函数声明中，也可以在函数定义中声明缺省参数，但不能既在函数声明中又在函数定义中同时声明缺省参数。
bool Classroom::recordToStream(ostream& out){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_WIDTH)<<"教室编号" << setw(Global::PRINT_LONG_WIDTH) << "教室名称" << setw(Global::PRINT_WIDTH) << "教室容量"<< endl;
	for(vector<Classroom>::iterator i=Classroom::roomList.begin();i!=Classroom::roomList.end();i++){
		out <<  setw(Global::PRINT_WIDTH)<<i->roomId << setw(Global::PRINT_LONG_WIDTH) <<	i->roomName << setw(Global::PRINT_WIDTH)  << i->capacity << endl;
	}
	return true;
}

bool Classroom::checkExist(int id, vector<Classroom>::iterator &i){
	for(i=Classroom::roomList.begin();i!=Classroom::roomList.end();i++){
		if(i->roomId == id){
			return true;
		}
	}
	return false;
}

//根据id获取教室名称 
Classroom* Classroom::getElementById(int id){
	for(vector<Classroom>::iterator i=Classroom::roomList.begin();i!=Classroom::roomList.end();i++){
		if(i->roomId == id){
			return const_cast<Classroom*>(&(*i));
		}
	}
}


const char* Classroom::dataFile = "classroomsInfo.txt"; 

bool Classroom::storeInfo(){
	bool result = true;
	ofstream out;
	//加载管理员账号密码
	out.open(dataFile,ios::out);
	if(!Classroom::recordToStream(out)){
		result= false;
	}

	out.close();
	return result;
}

bool Classroom::loadInfo(){
	ifstream in;
	string temp;
	
	//加载管理员账号密码
	in.open(dataFile,ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		int roomId,capacity;
		string roomName;
		
		stringstream ss(temp);
		ss >> roomId;
		ss >> roomName;
		ss >> capacity;
		
		Classroom cr(roomId,roomName,capacity);
		Classroom::roomList.push_back(cr);
	}		
	in.close();
}

