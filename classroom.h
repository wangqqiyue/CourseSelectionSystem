#ifndef INCLUDE_CLASSROOM
#define INCLUDE_CLASSROOM

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

class Classroom{
public:
	int roomId;
	string roomName;
	int capacity;//教室学生容量 
	
	Classroom(int id,string name,int cap):roomId(id),roomName(name),capacity(cap){}
	static bool recordToStream(ostream& os, vector<Classroom>::iterator firstRecord,bool onlyOne=false);
	bool recordToStream(ostream& os);
	static bool printTitleToStream(ostream& out);
	static Classroom* getElementById(int id);
	static vector<Classroom> roomList;
	static bool checkIdExist(int id,vector<Classroom>::iterator &i);
	static bool checkIdExist(int id);
	static bool checkNameExist(string name);
	const static  char* dataFile;//数据存储文件
	static bool storeInfo(); 
	static bool loadInfo();
	static bool getSelection(const string prompt, const vector<int>& idList, int* selectList, const int& classroomTotal,bool isInclusion=true,bool onlyOne=false);
	static bool del();
	static bool update();
	static bool retrieve();
	static bool create();
	static bool changeInfo(vector<Classroom>::iterator& i);
};

#endif
