/*课程定义头文件
教室、课程都是课程所需的物理资源 
因此放在同一个头文件里，看作一个整体组件 
*/ 

#ifndef INCLUDE_COURSE 
#define INCLUDE_COURSE

#ifndef INCLUDE_VECTOR
#include <vector>
#define INCLUDE_VECTOR
#endif


#ifndef INCLUDE_STRING
#include <string>
#define INCLUDE_STRING
#endif

using namespace std;


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
	int capacity;//课程人数限额 
	float price;
	string teacherAccount;
	int roomId;

	Course(int id,string name,int num,float p,string tAcc,int rId,int c):courseId(id),courseName(name),studentNumber(num),price(p),teacherAccount(tAcc),roomId(rId),capacity(c){}
	
	static bool recordToStream(ostream& os, vector<Course>::iterator firstRecord,bool onlyOne=false);
	static bool printTitleToStream(ostream& out);
	static Course* getElementById(int id);
	static vector<Course> courseList;
	const static  char* dataFile;//数据存储文件
	static bool storeInfo(); 
	static bool loadInfo();
	static bool create();
	static bool del();
	static bool retrieve();
	static bool getSelection(const vector<int>& idList, int* selectList, const int& courseTotal,bool isInclusion=true);
};


#endif
