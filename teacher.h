#ifndef INCLUDE_TEACHER
#define INCLUDE_TEACHER

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_VECTOR
#include <vector>
#define INCLUDE_VECTOR
#endif


#ifndef INCLUDE_STRING
#include <string>
#define INCLUDE_STRING
#endif

//��ʦ ���˺����� 
/*
���ܣ��鿴�Լ��Ŀγ���Ϣ��ѧԱ����
		 

*/ 
class Teacher{
public:
	static string login_account;//��ǰ��½�˺� 
	string account;
	string name;
	string password;
	Teacher(string acc,string n,string p):account(acc),name(n),password(p){}
	static bool printTitleToStream(ostream& out);
	static bool recordToStream(ostream& out, vector<Teacher>::iterator firstRecord, bool onlyOne=false);
	static bool checkAccountExist(string account, vector<Teacher>::iterator &i); 
	static bool checkAccountExist(string account);
	static Teacher* getElementByAccount(string account);
	static bool (*teacherFuncs[Global::TEACHER_FUNC_MAX])();//��ʦ���ܵĺ���ָ������ 
	static void process();
	static bool showTeacherCourse();
	static bool showRoster();
	const static  char* dataFile;//���ݴ洢�ļ�
	static bool storeInfo(); 
	static bool loadInfo();
	static bool create();
	static bool retrieve();
	static bool del();
	static bool update();
	static bool getSelection(const string prompt, const vector<string>& idList, int* selectList, const int& teacherTotal,bool isInclusion=true,bool onlyOne=false);
	static bool changeInfo(const vector<string> &unchangableAccounts, vector<Teacher>::iterator &it);
};
extern vector<Teacher> teacherList;


#endif 
