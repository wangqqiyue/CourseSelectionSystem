/*�γ̶���ͷ�ļ�
���ҡ��γ̶��ǿγ������������Դ 
��˷���ͬһ��ͷ�ļ������һ��������� 
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
	int capacity;//����ѧ������ 
	
	Classroom(int id,string name,int cap):roomId(id),roomName(name),capacity(cap){}
	static bool recordToStream(ostream& os);
};

extern vector<Classroom> g_roomList;

/*
�γ��пγ����ơ���Ӧ���ҡ���ʦ��ѡ������ ���۸�� 
Ĭ��ÿ�ſ�ֻ��һ����ʦ 
���ܣ�
	�޸Ŀγ�����
	�޸Ŀγ�����
	�޸Ŀγ̼۸�
	�޸���ʦ
	�޸Ľ���  
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
	static bool recordToStream(ostream& os);
};
extern vector<Course> g_courseList;
#endif
