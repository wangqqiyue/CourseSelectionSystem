#ifndef INCLUDE_COURSE 
#define INCLUDE_COURSE

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

/*
课程有课程名称、对应教室、老师、选课人数 、价格等 
默认每门课只有一个老师 
功能：
	修改课程名称
	修改课程人数
	修改课程价格
	修改老师
	修改教室  
*/
class Course{
public:
	int courseId;
	string courseName;
	int studentNumber;
	//上课时间是早上6点到晚上10点 ,6-8,8-10,10-12,12-14,14-16,16-18,18-20,20-22 一共8个时间段 ,新增的课程只能在这8个时间段里选择
	int courseHourIndex; //上课时段下标 ,0代表6-8,1代表8-10，以此类推 
	int capacity;//课程人数限额 
	float price;
	string teacherAccount;
	int roomId;

	Course(int id,string name,int num,float p,string tAcc,int rId,int c,int index):courseId(id),courseName(name),studentNumber(num),price(p),teacherAccount(tAcc),roomId(rId),capacity(c),courseHourIndex(index){}
		
	static bool recordToStream(ostream& os, vector<Course>::iterator firstRecord,bool onlyOne=false);
	bool recordToStream(ostream& os);
	static bool printTitleToStream(ostream& out);
	static Course* getElementById(int id);
	static vector<Course> courseList;
	const static  char* dataFile;//数据存储文件
	static bool storeInfo(); 
	static bool loadInfo();
	static bool create();
	static bool del();
	static bool retrieve();
	static bool update();
	static bool changeInfo(vector<Course>::iterator& it);
	static bool getSelection(const string prompt, const vector<int>& idList, int* selectList, const int& courseTotal,bool isInclusion=true, bool onlyOne = false);
	static int courseHourTable[8];
};


#endif
