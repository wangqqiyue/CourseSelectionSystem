#ifndef INCLUDE_ADMINISTATOR
#include "administrator.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_RECORD_PROCESS
#include "recordProcess.h" 
#endif

#ifndef INCLUDE_FSTREAM
#include <fstream>
#define INCLUDE_FSTREAM
#endif


#ifndef INCLUDE_SSTREAM
#include <sstream>
#define INCLUDE_SSTREAM
#endif

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

#ifndef INCLUDE_COURSE
#include "course.h"
#endif

#ifndef INCLUDE_CLASSROOM
#include "classroom.h"
#endif


//��̬��Ա������Ҫ�����ⶨ�� 
bool Administrator::hasAccount=false;
bool Administrator::hasLoaded=false;
string Administrator::adminAccount;
string Administrator::password;
//����ָ������ĳ�ʼ�� 
bool (*Administrator::mgmtFuncs[Global::MGMT_MAX])() = {teacherMgmt,classroomMgmt,courseMgmt};


const char* Administrator::dataFile = "administrator.txt"; 

bool Administrator::storeInfo(){
	bool result = true;
	ofstream out;
	//���ع���Ա�˺�����
	out.open(dataFile,ios::out);
	if(!Administrator::recordToStream(out)){
		result= false;
	}
	out.close();
	return result;
}

bool Administrator::loadInfo(){
	ifstream in;
	string temp;
	
	//���ع���Ա�˺�����
	in.open(dataFile,ios::in);
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
}

//����Ա������������ 
void Administrator::process(){
	if(!hasAccount){
		createAdmin();
	}
	while(login(Global::ADMINISTRATOR)){
		int mgmtChoice=-1; 	
		/*��ӡ�˵�ѡ�� 
		��ʦ��Ϣ
			�� ɾ ��  �� 
		������Ϣ
			�� ɾ ��  �� 
		�γ���Ϣ 
			�� ɾ ��  �� 
		*/
		while(Global::MGMT_MAX != mgmtChoice){
			clear();
			cout << "------����Ա�˵�-------" << endl;
			mgmtChoice = getChoice("ѡ����:", Global::mgmtStr, Global::MGMT_MAX);
			if(Global::MGMT_MAX != mgmtChoice){
				//����ִ�й��������ֱ�����ش����˳� 
				while(mgmtFuncs[mgmtChoice]());
			}
		}
	}
	
}

//��������Ա�˺� 
void Administrator::createAdmin(){
	clear();
	cout << "------��������Ա�˺�-----" << endl;
	cout << "���������Ա�˺�����:" ;
	cin >> adminAccount;
	
	Administrator::password = setPassword();
}

bool Administrator::recordToStream(ostream& out){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_WIDTH)<<"�˺�" << setw(Global::PRINT_WIDTH) << "����" << endl;
	out << setw(Global::PRINT_WIDTH)<<Administrator::adminAccount << setw(Global::PRINT_WIDTH) << Administrator::password << endl;
	return true;
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
			return Teacher::retrieve();
		}else if(Global::CREATE == opChoice){
			return Teacher::create();
		}else if(Global::DEL == opChoice){
			return Teacher::del();
		}
	}
	return false;
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
			return Classroom::retrieve();
		}else if(Global::CREATE == opChoice){
			return Classroom::create();
		}else if(Global::DEL == opChoice){
			return Classroom::del();
		}
	}
	return false;
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
			return Course::retrieve();
		}else if(Global::CREATE == opChoice){
			return Course::create();
		}else if(Global::DEL == opChoice){
			return Course::del();
		}
	}
	return false;
}




