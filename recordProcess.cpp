#ifndef INCLUDE_RECORD_PROCESS
#include "recordProcess.h" 
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


#ifndef INCLUDE_SSTREAM
#include <sstream>
#define INCLUDE_SSTREAM
#endif

#ifndef INCLUDE_FSTREAM
#include <fstream>
#define INCLUDE_FSTREAM
#endif


#ifndef INCLUDE_COURSE_RESOURCE
#include "courseResource.h"
#endif

#ifndef INCLUDE_ADMINISTATOR
#include "administrator.h"
#endif 

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif


//��Ϣ���� 
void loadInfo(){
	ifstream in;
	string temp;
	
	//���ع���Ա�˺�����
	in.open("administrator.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		string account,password;
		stringstream ss(temp);
		ss >> account;
		ss >> password;
		Administrator::adminAccount=account;
		Administrator::password=password;
		Administrator::hasAccount=true;
	}
	in.close();
	
	//���ؽ�ʦ��Ϣ 
	in.open("teachersInfo.txt",ios::in);
	//һ���ж�ȡ��Ϣ�����ָֵ 
	getline(in,temp);
	while(getline(in,temp)){
		int teacherId;
		string teacherName,teacherPassword;
		stringstream ss(temp);
		ss >> teacherId;
		ss >> teacherName;
		ss >> teacherPassword;
		Teacher t(teacherId,teacherName,teacherPassword);
		g_teacherList.push_back(t);
	}
	in.close();
	
	//���ؿγ���Ϣ
	in.open("coursesInfo.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		int courseId,number,teacherId,classroomId;
		float price;
		string courseName;
		
		stringstream ss(temp);
		ss >> courseId;
		ss >> courseName;
		ss >> number;
		ss >> price;
		ss >> teacherId;
		ss >> classroomId;
		
		Course c(courseId,courseName,number,price,teacherId,classroomId);
		g_courseList.push_back(c);
	}
	in.close();
	
	//���ؽ�����Ϣ
	in.open("classroomsInfo.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		int roomId,capacity;
		string roomName;
		
		stringstream ss(temp);
		ss >> roomId;
		ss >> roomName;
		ss >> capacity;
		
		Classroom cr(roomId,roomName,capacity);
		g_roomList.push_back(cr);
	}
	in.close();
}


//��Ϣ�洢
void storeInfo(){
	ofstream out;

	//���ع���Ա�˺�����
	out.open("administrator.txt",ios::out);
	Administrator::recordToStream(out);
	out.close();
	
	//�洢��ʦ��Ϣ 
	out.open("teachersInfo.txt",ios::out);
	Teacher::recordToStream(out);
	out.close();
	
	//�洢�γ���Ϣ 
	out.open("coursesInfo.txt",ios::out);
	Course::recordToStream(out);
	out.close();
	
	//�洢������Ϣ 
	out.open("classroomsInfo.txt",ios::out);
	Classroom::recordToStream(out);
	out.close();
}


/*----------------�����ʦ���� -------------------*/


bool teacherMgmt(){
	int opChoice = -1;
	while(Global::OP_MAX != opChoice){
		opChoice = -1; 
		clear();
		cout << "------��ʦ��Ϣ����-----"  << endl;
		opChoice = getChoice("ѡ�����:", Global::operationStr, Global::OP_MAX);
		if(Global::RETRIEVE == opChoice){
			return teacherInfoRetrieve();
		}else if(Global::CREATE == opChoice){
			return teacherInfoCreate();
		}
	}
	return false;
}


//��ѯ��ʦ��Ϣ 
bool teacherInfoRetrieve(){
	clear();
	cout << "------��ʦ��Ϣ��ѯ-----"	<< endl;
	Teacher::recordToStream(cout);
	cout << "�������������һ��" << endl;
	cin.ignore();
	getchar();
	return true;
	
}

/*������ʦ���� 
��Ҫ�ж����������Ƿ����ظ�,�����󲻳�����ʦ�������� 
*/
bool teacherInfoCreate(){
	int id;
	string name;
	string passwd;
	char comfirm = 'y';
	clear();
	cout << "------������ʦ��Ϣ-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(g_teacherList.size() >= Global::TEACHER_NUMBER_MAX){
			cout << "��ʦ�����Ѵ�����("<< Global::TEACHER_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "��������Ϣ" << endl;
		cout<<"��ʦ���:";
		cin >> id;
		if(!isInputOk()){
			continue;
		}
		
		vector<Teacher>::iterator i;
		for(i=g_teacherList.begin();i!=g_teacherList.end();++i){
			if(i->teacherId == id){
				cout << "�ñ���Ѵ��ڣ�������ѡ��" << endl;
				break;
			}
		}
		if(i != g_teacherList.end()){
			cout << "�Ƿ����?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "��ʦ����:" ;
		cin >> name;
		
		cout << "����;";
		cin >> passwd;
		
		Teacher t(id,name,passwd);
		g_teacherList.push_back(t);
		
		cout << "��������������" << endl;
		cout << setw(Global::PRINT_WIDTH)<<"��ʦ���" << setw(Global::PRINT_LONG_WIDTH) << "��ʦ����" << setw(Global::PRINT_LONG_WIDTH) << "����"<< endl;
		cout <<  setw(Global::PRINT_WIDTH)<<id << setw(Global::PRINT_LONG_WIDTH) <<	name << setw(Global::PRINT_LONG_WIDTH)  << passwd << endl;
		
		
		cout << "�Ƿ����?Y/N" << endl;
		cin >> comfirm;
	}
	
	cout << "�������������һ��" << endl;
	cin.ignore();
	getchar();
	return true;
	
}


/*--------------------------------������Ϣ���� ----------------------------------------*/
bool classroomMgmt(){
	int opChoice = -1;
	while(Global::OP_MAX != opChoice){
		opChoice = -1; 
		clear();
		cout << "------������Ϣ����-----"  << endl;
		opChoice = getChoice("ѡ�����:", Global::operationStr, Global::OP_MAX);
		if(Global::RETRIEVE == opChoice){
			return roomInfoRetrieve();
		}else if(Global::CREATE == opChoice){
			return roomInfoCreate();
		}
	}
	return false;
}

//��ѯ�������� 
bool roomInfoRetrieve(){
	clear();
	cout << "------������Ϣ��ѯ-----"	<< endl;
	Classroom::recordToStream(cout);
	cout << "�������������һ��" << endl;
	cin.ignore();
	getchar();
	return true;
	
}


/*������������ 
��Ҫ�ж����������Ƿ����ظ�,�����󲻳��������������� 
*/
bool roomInfoCreate(){
	int id,capacity;
	string name;

	char comfirm = 'y';
	clear();
	cout << "------����������Ϣ-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(g_roomList.size() >= Global::ROOM_NUMBER_MAX){
			cout << "���������Ѵ�����("<< Global::ROOM_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "��������Ϣ" << endl;
		cout<<"���ұ��:";
		cin >> id;
		if(!isInputOk()){
			continue;
		}
		
		vector<Classroom>::iterator i;
		for(i=g_roomList.begin();i!=g_roomList.end();++i){
			if(i->roomId == id){
				cout << "�ñ���Ѵ��ڣ�������ѡ��" << endl;
				break;
			}
		}
		if(i != g_roomList.end()){
			cout << "�Ƿ����?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "��������:" ;
		cin >> name;
		for(i=g_roomList.begin();i!=g_roomList.end();++i){
			if(i->roomName == name){
				cout << "�������Ѵ��ڣ�������ѡ��" << endl;
				break;
			}
		}
		if(i != g_roomList.end()){
			cout << "�Ƿ����?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "��������";
		cin >> capacity;
		
		Classroom cr(id,name,capacity);
		g_roomList.push_back(cr);
		
		cout << "��������������" << endl;
		cout << setw(Global::PRINT_WIDTH)<<"���ұ��" << setw(Global::PRINT_LONG_WIDTH) << "��������" << setw(Global::PRINT_LONG_WIDTH) << "��������"<< endl;
		cout <<  setw(Global::PRINT_WIDTH)<<id << setw(Global::PRINT_LONG_WIDTH) <<	name << setw(Global::PRINT_LONG_WIDTH)  << capacity << endl;
		
		
		cout << "�Ƿ����?Y/N" << endl;
		cin >> comfirm;
	}
	
	cout << "�������������һ��" << endl;
	cin.ignore();
	getchar();
	return true;
	
}

/*--------------------------------�γ���Ϣ����--------------------------------------------*/
bool courseMgmt(){
	int opChoice = -1;
	while(Global::OP_MAX != opChoice){
		opChoice = -1; 
		clear();
		cout << "------�γ���Ϣ����-----"  << endl;
		opChoice = getChoice("ѡ�����:", Global::operationStr, Global::OP_MAX);
		if(Global::RETRIEVE == opChoice){
			return courseInfoRetrieve();
		}else if(Global::CREATE == opChoice){
			return courseInfoCreate();
		}
	}
	return false;
}

//��ѯ�γ����� 
bool courseInfoRetrieve(){
	clear();
	cout << "------������Ϣ��ѯ-----"	<< endl;
	Course::recordToStream(cout);
	cout << "�������������һ��" << endl;
	cin.ignore();
	getchar();
	return true;
	
}

/*�����γ����� 
��Ҫ�ж����������Ƿ����ظ�,�����󲻳����γ��������� 
*/
bool courseInfoCreate(){
	int id,teacherId,roomId;
	float price;
	string name;

	char comfirm = 'y';
	clear();
	cout << "------�����γ���Ϣ-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(g_courseList.size() >= Global::COURSE_NUMBER_MAX){
			cout << "�γ������Ѵ�����("<< Global::COURSE_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "��������Ϣ" << endl;
		cout<<"�γ̱��:";
		cin >> id;
		if(!isInputOk()){
			continue;
		}
		
		vector<Course>::iterator i;
		for(i=g_courseList.begin();i!=g_courseList.end();++i){
			if(i->courseId == id){
				cout << "�ñ���Ѵ��ڣ�������ѡ��" << endl;
				break;
			}
		}
		if(i != g_courseList.end()){
			cout << "�Ƿ����?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		
		cout << "�γ�����:" ;
		cin >> name;
		for(i=g_courseList.begin();i!=g_courseList.end();++i){
			if(i->courseName == name){
				cout << "�������Ѵ��ڣ�������ѡ��" << endl;
				break;
			}
		}
		if(i != g_courseList.end()){
			cout << "�Ƿ����?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "�γ̼۸�";
		cin >> price;
		while(price < 0 || price > Global::COURSE_PRICE_MAX){
			cout << "�γ̼۸���Ҫ�ں���Χ(0--"<< Global::COURSE_PRICE_MAX <<")������������:" << endl;
			cin >> price;
		}
		
		
		while(true) 
		{
			cout<<"��ʦ���:";
			cin >> teacherId;
			if(!isInputOk()){
				continue;
			}
			vector<Teacher>::iterator i;
			for(i=g_teacherList.begin();i!=g_teacherList.end();++i){
				if(i->teacherId == teacherId){
					break;
				}
			}
			if(i == g_teacherList.end()){
				cout << "�ñ�Ų����ڣ�������ѡ��" << endl;
			}else{
				break;
			}
		}

		while(true) 
		{
			cout<<"���ұ��:";
			cin >> roomId;
			if(!isInputOk()){
				continue;
			}
			vector<Classroom>::iterator i;
			for(i=g_roomList.begin();i!=g_roomList.end();++i){
				if(i->roomId == roomId){
					break;
				}
			}
			if(i == g_roomList.end()){
				cout << "�ñ�Ų����ڣ�������ѡ��" << endl;
			}else{
				break;
			}
		}
				
		
		Course c(id,name,0,price,teacherId,roomId);
		g_courseList.push_back(c);
		
		cout << "��������������" << endl;
		cout << setw(Global::PRINT_WIDTH)<<"�γ̱���" << setw(Global::PRINT_LONG_WIDTH) << "�γ���" << setw(Global::PRINT_LONG_WIDTH) << "ѡ������"<< setw(Global::PRINT_LONG_WIDTH) << "�γ̼۸�"<< setw(Global::PRINT_LONG_WIDTH) << "�ο���ʦ���"<< setw(Global::PRINT_LONG_WIDTH) << "���ұ��"<<endl;
		cout <<  setw(Global::PRINT_WIDTH)<<id << setw(Global::PRINT_LONG_WIDTH) <<	name << setw(Global::PRINT_LONG_WIDTH)  << 0 << setw(Global::PRINT_LONG_WIDTH) << fixed << setprecision(2) << price << setw(Global::PRINT_LONG_WIDTH)  << teacherId << setw(Global::PRINT_LONG_WIDTH)  << roomId << endl;
	
		
		cout << "�Ƿ����?Y/N" << endl;
		cin >> comfirm;
	}
	
	cout << "�������������һ��" << endl;
	cin.ignore();
	getchar();
	return true;
	
}
