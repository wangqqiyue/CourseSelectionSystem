#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_COURSE_RESOURCE
#include "courseResource.h"
#endif

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

vector<Teacher> teacherList;

//����ָ������ĳ�ʼ�� 
bool (*Teacher::teacherFuncs[Global::TEACHER_FUNC_MAX])() = {Teacher::showTeacherCourse,Teacher::showRoster};
string Teacher::login_account = "";//��ǰ��½�˺� 

//ѧ�������������� 
void Teacher::process(){
	while(login(Global::TEACHER)){
		int funcChoice = -1;
		while(Global::TEACHER_FUNC_MAX != funcChoice){
			clear();
			cout << "--------��ʦ���ܲ˵�---------" << endl;
			funcChoice = getChoice("ѡ����:", Global::teacherFuncStr, Global::TEACHER_FUNC_MAX);
			if(Global::TEACHER_FUNC_MAX != funcChoice){
				//����ִ�в�����ֱ�����ش����˳� 
				teacherFuncs[funcChoice]();
			}
		}

	}
}


bool Teacher::checkAccountExist(string account){
	for(vector<Teacher>::iterator  i=teacherList.begin();i!=teacherList.end();++i){
		if(i->account == account){
			return true;
		}
	}
	return false;
}

bool Teacher::checkAccountExist(string account, vector<Teacher>::iterator &i){
	for(i=teacherList.begin();i!=teacherList.end();++i){
		if(i->account == account){
			return true;
		}
	}
	return false;
}

bool Teacher::recordToStream(ostream& out, vector<Teacher>::iterator firstRecord, bool onlyOne){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_WIDTH)<<"��ʦ�ʺ�" << setw(Global::PRINT_LONG_WIDTH) << "��ʦ����" << setw(Global::PRINT_LONG_WIDTH) << "����"<< endl;
	for(vector<Teacher>::iterator i=teacherList.begin();i!=teacherList.end();i++){
		if(onlyOne){
			i=firstRecord;
		}
		out <<  setw(Global::PRINT_WIDTH)<<i->account << setw(Global::PRINT_LONG_WIDTH) <<	i->name << setw(Global::PRINT_LONG_WIDTH)  << i->password << endl;
		if(onlyOne){
			break;
		}
	}
	return true;
} 

//���ݽ�ʦ�˺ŷ��ؽ�ʦԪ�ص�ָ�� 
Teacher* Teacher::getElementByAccount(string account){
		for(vector<Teacher>::iterator i=teacherList.begin();i!=teacherList.end();i++){
		if(i->account == account){
			return const_cast<Teacher*>(&(*i));
		}
	}
}

//��ӡ��ǰ��ʦ���µĿγ� 
bool Teacher::showTeacherCourse(){
	bool result = true;

	clear();
	cout <<"-------------�����µĿγ� -------------------------" << endl;
	Teacher *teacher=getElementByAccount(login_account);
	if(!teacher){
		cerr<<"�˺�Ϊ" << login_account << "�Ľ�ʦ������" << endl;
		result = false;
	}
	
	cout << setw(Global::PRINT_LONG_WIDTH) << "�γ���" << setw(Global::PRINT_WIDTH) << "ѡ������" << setw(Global::PRINT_LONG_WIDTH) << "����" << endl;
	for(vector<Course>::iterator i=g_courseList.begin();i!=g_courseList.end();i++){
		Classroom* room;
		if(i->teacherAccount == login_account){
			room = Classroom::getElementById(i->roomId);
			if(!room){
				cerr << "���Ϊ" << i->roomId << "�Ľ��Ҳ�����" << endl;
				result = false;
			}
			cout << setw(Global::PRINT_LONG_WIDTH) << i->courseName <<  setw(Global::PRINT_WIDTH) << i->studentNumber <<  setw(Global::PRINT_LONG_WIDTH) << room->roomName << endl;
		}
	}
	goPrevious();
	return result;
}

//��ӡѧ��������
bool Teacher::showRoster(){
	bool result = true;

	clear();
	cout <<"-------------�����µĿγ̵�ѧ�������� -------------------------" << endl;
	
	Teacher *teacher=getElementByAccount(login_account);
	if(!teacher){
		cerr<<"�˺�Ϊ" << login_account << "�Ľ�ʦ������" << endl;
		result = false;
	}
	
	cout << setw(Global::PRINT_LONG_WIDTH) << "�γ���" << setw(Global::PRINT_WIDTH) << "ѡ������" << setw(Global::PRINT_LONG_WIDTH) << "����" << endl;
	for(vector<Course>::iterator i=g_courseList.begin();i!=g_courseList.end();i++){
		Classroom* room;
		if(i->teacherAccount == login_account){
			room = Classroom::getElementById(i->roomId);
			if(!room){
				cerr << "���Ϊ" << i->roomId << "�Ľ��Ҳ�����" << endl;
				result = false;
			}
			cout << setw(Global::PRINT_LONG_WIDTH) << i->courseName <<  setw(Global::PRINT_WIDTH) << i->studentNumber <<  setw(Global::PRINT_LONG_WIDTH) << room->roomName << endl;
			if(0 == i->studentNumber){
				cout << "����ѧ��ѡ���ſγ�" << endl;
				continue;
			}
			
			cout <<"-------������-----" << endl;
			vector<string> studentList = CourseSelectionTable::paidOrder.getStudentByCourse(i->courseId);
			int  rosterNumber = 1;//��������� 
			for(vector<string>::iterator j=studentList.begin();j!=studentList.end();j++,rosterNumber++){
				Student* student = Student::getElementByAccount(*j);\
				if(!student){
					cerr << "�˺�Ϊ" << *j <<"��ѧ��������" << endl;
					result = false;
				}
				cout << rosterNumber << ". " << student->name << endl;
			}
			cout << endl;
		}
	}
	goPrevious();
	return result;
} 
