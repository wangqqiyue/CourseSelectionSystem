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
	int classroomId;
	int capacity;//教室学生容量 
	string classroomName;
};


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
	float price;
	int teacherId;
	int classroomId;

	Course(int id,string name,int num,float p,int tId,int cId):courseId(id),courseName(name),studentNumber(num),price(p),teacherId(tId),classroomId(cId){}
	void setCourseId(int courseId);
	void setCourseName(string name); 
	void setStudentNumber(int number);
	void setPrice(float price);
	void setTeacher(int teacherId);
	void setClassroom(int classroom);
	void showCourseInfo();
};
extern vector<Course> g_courseList;
#endif
