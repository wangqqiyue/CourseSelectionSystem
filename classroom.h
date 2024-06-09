#ifndef INCLUDE_CLASSROOM
#define INCLUDE_CLASSROOM

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
	static bool recordToStream(ostream& os, vector<Classroom>::iterator firstRecord,bool onlyOne=false);
	static bool printTitleToStream(ostream& out);
	static Classroom* getElementById(int id);
	static vector<Classroom> roomList;
	static bool checkIdExist(int id,vector<Classroom>::iterator &i);
	const static  char* dataFile;//数据存储文件
	static bool storeInfo(); 
	static bool loadInfo();
	static bool getSelection(const vector<int>& idList, int* selectList, const int& classroomTotal,bool isInclusion=true);
	static bool del();
	static bool retrieve();
	static bool create();
};

#endif
