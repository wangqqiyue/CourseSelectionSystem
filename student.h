#ifndef INCLUDE_STUDENT
#define INCLUDE_STUDENT

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_VECTOR
#include <vector>
#define INCLUDE_VECTOR
#endif

//ѧ�� ������ ���֤�� �ֻ��� ���� 
/*
���ܣ���½/ע�� 
		¼����Ϣ������Ϣ 
		�鿴��ѡ�γ�
		����
		��ȡѡ�ε����������ֻ��š��γ̡���ʦ�����ң� 
		----------�����Ǹ߼����� 
		��ѡ 
		�ɷ�
*/ 
class Student{
public: 
	string account;
	string idCardNumber;//18 ������ 6λ������-8λ��������-3������-1λ����λ(0-x) 
	string name;
	string telphone;
	string password;
	Student(string a,string id,string name,string tel,string p):account(a),idCardNumber(id),name(name),telphone(tel),password(p){}
	static void createAccount();
	static bool recordToStream(ostream& out, vector<Student>::iterator firstRecord,bool onlyOne=false);
	static void process();
	static bool checkAccountExist(string account);
	static bool checkAccountExist(string account,vector<Student>::iterator &i);
	static bool (*stuFuncs[Global::STU_FUNC_MAX])();//ѧ�����ܵĺ���ָ������ 
};

extern vector<Student> studentList;

#endif
