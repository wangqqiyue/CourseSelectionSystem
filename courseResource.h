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
	static bool recordToStream(ostream& os, bool tailOnly = false);
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
	int capacity;//�γ������޶� 
	float price;
	int teacherId;
	int roomId;

	Course(int id,string name,int num,float p,int tId,int rId,int c):courseId(id),courseName(name),studentNumber(num),price(p),teacherId(tId),roomId(rId),capacity(c){}
	
	static bool recordToStream(ostream& os, bool tailOnly = false);
};
extern vector<Course> g_courseList;
#endif
