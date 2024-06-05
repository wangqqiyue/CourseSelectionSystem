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


#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif

#ifndef INCLUDE_CONIO
#include <conio.h>
#define INCLUDE_CONIO
#endif

#ifndef INCLUDE_ALGORITHM
#include <algorithm>
#define INCLUDE_ALGORITHM
#endif

template<class T>
bool checkExist(const vector<T>& vec, const T& target){
	for(typename vector<T>::const_iterator i=vec.begin();i!=vec.end();i++){
		if(*i == target){
			return true;
		}
	}
	return false;
}

//���ص���studentList�е�һ���������������˺ŵ��ڴ������account���� Student����ĵ�ַ��
Student* getStudentByAccount(string account){
	for(vector<Student>::iterator i=studentList.begin();i!=studentList.end();i++){
		if(i->account == account){
			return &(*i);
		}
	}
	return NULL;
}

/*----------------------ѧ��ѡ��-------------------------*/
bool selectCourse(){
	int currentLine=0;//��ǰ��������� 
	int *selectList;//��ѡ��Ŀγ��б�, ���ѡ����Ϊ1 
	int selectTotal=0;//��ѡ������� 
	int courseTotal;//��ѡ�γ�������
	bool firstPrint = true;//�״δ�ӡ 
    
    //��ʼ�� 
	vector<int> paidList = CourseSelectionTable::paidOrder.getCourseByStudent(Student::login_account);//��֧���Ŀγ��б�
	courseTotal = g_courseList.size() - paidList.size();//��ѡ�γ�������

	selectList = new int[courseTotal];
    for(int i=0;i<courseTotal;i++){
    	selectList[i] = 0;
	}
	
	
	while (true) {
        if (_kbhit()|| firstPrint) {
    		int line=0;
			vector<Course>::iterator i;
	
        	clear();
        	//����͹���˵�� 
			cout << "----------------ѧ��ѡ��----------------" << endl;
			
			//��ʾ��ǰ״̬ 
			float priceTotal = 0;
			cout << "ѡ��״̬" << endl;
			cout << "��ѡ��γ�����:" << selectTotal << "(";

            for(i=g_courseList.begin(),line=0,selectTotal=0;i!=g_courseList.end();i++){
            	//������֧���Ŀγ� 
				if(checkExist(paidList,i->courseId)){
					continue;
				}
				if(1 == selectList[line]){
					priceTotal += i->price;
					cout << i->courseName << " ";
				}
            	line++;
			}
			
			cout << ")" << endl;
			cout << "�γ��ܼ۸�:" <<  fixed << setprecision(2)<< priceTotal  << endl;
			
			Course::printTitleToStream(cout);
			
			//��ȡ���� 
			if(!firstPrint){
	            char ch = _getch();
	            if (ch == 72) { // �ϼ�ͷ��
	                currentLine--;
	                if (currentLine < 0) {
	                    currentLine += courseTotal;
	                }
					
	            } else if (ch == 80) { // �¼�ͷ��
	                currentLine++;
	                currentLine%=courseTotal;
	            } else if(ch == 13) {//�س��� 
	            		selectList[currentLine] += 1;
	            		selectList[currentLine] %= 2;	            		
	        	}else if(ch == 'y'){
	        		break;
				}else if(ch == 'q'){
	        		return false;
				}
			}

			//�������пγ��� 
            for(i=g_courseList.begin(),line=0,selectTotal=0;i!=g_courseList.end();i++){
            	//������֧���Ŀγ� 
				if(checkExist(paidList,i->courseId)){
					continue;
				}
				
            	//��ǰ�и��� 
            	if(line == currentLine){
            		setConsoleColor(FOREGROUND_GREEN |  FOREGROUND_INTENSITY | BACKGROUND_INTENSITY); // ����ǰ��ɫΪ��ɫ
				}

				//�����ǰ�γ̱�ѡ�У������ 
				if(1 == selectList[line]){
            		setConsoleColor(BACKGROUND_GREEN |  FOREGROUND_INTENSITY | BACKGROUND_INTENSITY); // ���ñ���ɫΪ��ɫ
            		selectTotal++;
				}
				
            	Course::recordToStream(cout,i,true);
            	setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // �ָ�Ĭ����ɫ
            	line++;
			}
			firstPrint = false;
			
			cout <<"������ʾ�� ����ѡ��, �س���ѡ��, [y]��ȷ��, [q] ���˳�" << endl;
        }
        
    }
    //todo ȷ��ѡ�ν�����붩�� 
    
    
    free(selectList);
	
	return true;
}

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
		string teacherAccount,teacherName,teacherPassword;
		stringstream ss(temp);
		ss >> teacherAccount;
		ss >> teacherName;
		ss >> teacherPassword;
		Teacher t(teacherAccount,teacherName,teacherPassword);
		teacherList.push_back(t);
	}
	in.close();
	
	//���ؿγ���Ϣ
	in.open("coursesInfo.txt",ios::in);
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
	
	//����ѧ����Ϣ
	in.open("studentsInfo.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		string account,name,id,tel,password;
		
		stringstream ss(temp);
		ss >> account;
		ss >> name;
		ss >> id;
		ss >> tel;
		ss >> password;
		
		Student s = Student(account,id,name,tel,password);
		studentList.push_back(s);
	}
	in.close();
	
	//����ѡ�α� 
	in.open("courseSelectionTable.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		string account;
		int id;
		
		stringstream ss(temp);
		ss >> id;
		ss >> account;

		CourseSelectionTable::paidOrder.addEntry(id,account);
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
	Teacher::recordToStream(out, teacherList.begin());
	out.close();
	
	//�洢�γ���Ϣ 
	out.open("coursesInfo.txt",ios::out);
	Course::recordToStream(out,g_courseList.begin());
	out.close();
	
	//�洢������Ϣ 
	out.open("classroomsInfo.txt",ios::out);
	Classroom::recordToStream(out);
	out.close();
	
	//�洢������Ϣ 
	out.open("studentsInfo.txt",ios::out);
	Student::recordToStream(out,studentList.begin());
	out.close();
	
	//�洢ѡ�α���Ϣ 
	out.open("courseSelectionTable.txt",ios::out);
	CourseSelectionTable::paidOrder.recordToStream(out);
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
	Teacher::recordToStream(cout, teacherList.begin());
	cout << "�������������һ��" << endl;
	cin.ignore();
	getchar();
	return true;
	
}

/*������ʦ���� 
��Ҫ�ж����������Ƿ����ظ�,�����󲻳�����ʦ�������� 
*/
bool teacherInfoCreate(){
	string account,name,passwd;
	char comfirm = 'y';
	clear();
	cout << "------������ʦ��Ϣ-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(teacherList.size() >= Global::TEACHER_NUMBER_MAX){
			cout << "��ʦ�����Ѵ�����("<< Global::TEACHER_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "��������Ϣ" << endl;
		cout<<"��ʦ�˺�:";
		cin >> account;

		if(Teacher::checkAccountExist(account)){
			cout << "�Ƿ����?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "��ʦ����:" ;
		cin >> name;
		
		cout << "����;";
		cin >> passwd;
		
		Teacher t(account,name,passwd);
		teacherList.push_back(t);
		
		cout << "��������������" << endl;
		Teacher::recordToStream(cout, teacherList.end()-1, true);

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
	cout << "------�γ���Ϣ��ѯ-----"	<< endl;
	Course::recordToStream(cout,g_courseList.begin());
	cout << "�������������һ��" << endl;
	cin.ignore();
	getchar();
	return true;
	
}

/*�����γ����� 
��Ҫ�ж����������Ƿ����ظ�,�����󲻳����γ��������� 
*/
bool courseInfoCreate(){
	int id,roomId,capacity;
	float price;
	string name,teacherAccount;

	char comfirm = 'y';
	clear();
	cout << "------�����γ���Ϣ-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(g_courseList.size() >= Global::COURSE_NUMBER_MAX){
			cout << "�γ������Ѵ�����("<< Global::COURSE_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "��������Ϣ" << endl;
		
		while('y' == comfirm || 'Y' == comfirm){
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
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
		
		
		while('y' == comfirm || 'Y' == comfirm){
			cout << "�γ�����:" ;
			cin >> name;
			
			vector<Course>::iterator i;
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
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
		
		while('y' == comfirm || 'Y' == comfirm){
			cout << "�γ̼۸�";
			cin >> price;
			if(price < 0 || price > Global::COURSE_PRICE_MAX){
				cout << "�γ̼۸���Ҫ�ں���Χ(0--"<< Global::COURSE_PRICE_MAX <<")������������:" << endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
		
		while('y' == comfirm || 'Y' == comfirm){
			cout<<"��ʦ�ʺ�:";
			cin >> teacherAccount;

			if(Teacher::checkAccountExist(teacherAccount)){
				cout << "�ñ�Ų����ڣ�������ѡ��" << endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}

		while('y' == comfirm || 'Y' == comfirm){
			cout << "�γ������޶�";
			cin >> capacity;
			if(capacity < Global::COURSE_CAPACITY_MIN || capacity > Global::COURSE_CAPACITY_MAX){
				cout << "�γ������޶���Ҫ�ں���Χ("<< Global::COURSE_CAPACITY_MIN <<"--"<< Global::COURSE_CAPACITY_MAX <<")"<<endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
		
		while('y' == comfirm || 'Y' == comfirm){
			cout<<"���ұ��:";
			cin >> roomId;
			if(!isInputOk()){
				continue;
			}
			vector<Classroom>::iterator i;
			if(!Classroom::checkExist(roomId,i)){
				cout << "�ñ�Ų����ڣ�������ѡ��" << endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else if(i->capacity < capacity){
				cout << "�ý��ҽ�������" << i->capacity << "��, ������ѡ��" << endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
				
		//�½��γ̶��󣬲���ӵ�����β�� 
		Course c(id,name,0,price,teacherAccount,roomId,capacity);
		g_courseList.push_back(c);
		
		//��ӡ�������� 
		cout << "��������������" << endl;
		Course::recordToStream(cout,g_courseList.end() - 1,true);
		
		cout << "�Ƿ����?Y/N" << endl;
		cin >> comfirm;
	}
	
	cout << "�������������һ��" << endl;
	cin.ignore();
	getchar();
	return true;
	
}
