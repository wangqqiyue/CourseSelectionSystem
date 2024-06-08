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
	int capacity;//����ѧ������ 
	
	Classroom(int id,string name,int cap):roomId(id),roomName(name),capacity(cap){}
	static bool recordToStream(ostream& os);
	static bool checkExist(int id, vector<Classroom>::iterator &i);
	static Classroom* getElementById(int id);
	static vector<Classroom> roomList;
	
	const static  char* dataFile;//���ݴ洢�ļ�
	static bool storeInfo(); 
	static bool loadInfo();
};

#endif
