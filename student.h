#ifndef INCLUDE_STUDENT
#define INCLUDE_STUDENT

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_VECTOR
#include <vector>
#define INCLUDE_VECTOR
#endif

//学生 有姓名 身份证号 手机号 密码 
/*
功能：登陆/注册 
		录入信息、绑定信息 
		查看可选课程
		报名
		获取选课单（姓名、手机号、课程、教师、教室） 
		----------以下是高级功能 
		退选 
		缴费
*/ 
class Student{
public: 
	static string login_account;
	string account;
	string idCardNumber;//18 个数字 6位地区号-8位出生日期-3个数字-1位检验位(0-x) 
	string name;
	string telphone;
	string password;
	Student(string a,string id,string name,string tel,string p):account(a),idCardNumber(id),name(name),telphone(tel),password(p){}
	static bool createAccount();
	static bool printTitleToStream(ostream& out);
	static bool recordToStream(ostream& out, vector<Student>::iterator firstRecord,bool onlyOne=false);
	bool recordToStream(ostream& out);
	static void process();
	static bool checkAccountExist(string account);
	static bool checkAccountExist(string account,vector<Student>::iterator &i);
	static bool (*stuFuncs[Global::STU_FUNC_MAX])();//学生功能的函数指针数组 
	static Student* getElementByAccount(string account);
	static vector<Student> studentList;
	static bool payOrder();
	static bool showSelectedCourse();
	static bool withdrawCourse();
	static bool selectCourse();
	static bool getSelection(const vector<int>& idList, int* selectList, const int& courseTotal,bool isInclusion=true);
	
	const static  char* dataFile;//数据存储文件
	static bool storeInfo(); 
	static bool loadInfo();
};


#endif
