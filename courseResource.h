/*课程定义头文件
教室、课程都是课程所需的物理资源 
因此放在同一个头文件里，看作一个整体组件 
*/ 

#ifndef INCLUDE_COURSE_RESOURCE 
#define INCLUDE_COURSE_RESOURCE

#ifndef INCLUDE_VECTOR
#include <vector>
#define INCLUDE_VECTOR
#endif


#ifndef INCLUDE_STRING
#include <string>
#define INCLUDE_STRING
#endif

using namespace std;


class Classroom{
public:
	int roomId;
	string roomName;
	int capacity;//教室学生容量 
	
	Classroom(int id,string name,int cap):roomId(id),roomName(name),capacity(cap){}
	static bool recordToStream(ostream& os, bool tailOnly = false);
};

extern vector<Classroom> g_roomList;

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
	int teacherId;
	int roomId;

	Course(int id,string name,int num,float p,int tId,int rId,int c):courseId(id),courseName(name),studentNumber(num),price(p),teacherId(tId),roomId(rId),capacity(c){}
	
	static bool recordToStream(ostream& os, bool tailOnly = false);
};
extern vector<Course> g_courseList;
#endif
