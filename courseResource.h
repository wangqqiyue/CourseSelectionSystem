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

#ifndef INCLUDE_MAP
#include <map>
#define INCLUDE_MAP
#endif

using namespace std;

class Classroom{
public:
	int roomId;
	string roomName;
	int capacity;//����ѧ������ 
	
	Classroom(int id,string name,int cap):roomId(id),roomName(name),capacity(cap){}
	static bool recordToStream(ostream& os);
	static bool checkExist(int id, vector<Classroom>::iterator &i);
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
	string teacherAccount;
	int roomId;

	Course(int id,string name,int num,float p,string tAcc,int rId,int c):courseId(id),courseName(name),studentNumber(num),price(p),teacherAccount(tAcc),roomId(rId),capacity(c){}
	
	static bool recordToStream(ostream& os, vector<Course>::iterator firstRecord,bool onlyOne=false);
	static bool printTitleToStream(ostream& out);
};
extern vector<Course> g_courseList;

/*---------------------�γ�ѧ����ϵ��-----------------------*/
class CourseSelectionTable{
private:
	static  multimap<int,string> courseKeyMap;
	static multimap<string,int> studentKeyMap;
public:
	static bool addEntry(int id, string account);
	static bool deleteEntry(int courseId, string account);
	static vector<string> getStudentByCourse(int id);
	static vector<int> getCourseByStudent(string account);
	static bool recordToStream(ostream& os);
	template<typename K,typename V>
	static bool checkExist(multimap<K,V>& map, const K& key, const V& val, bool needDelete = false);
	
};
#endif
