#ifndef INCLUDE_SELECTION_TABLE
#define INCLUDE_SELECTION_TABLE

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_MAP
#include <map>
#define INCLUDE_MAP
#endif


using std::multimap;
/*---------------------�γ�ѧ����ϵ��-----------------------*/
//������ �ڲ��� 
class OrderTable{
public:
	multimap<int,string> courseKeyMap;
	multimap<string,int> studentKeyMap;
	bool addEntry(int id, string account);
	bool deleteEntry(int courseId, string account);
	vector<string> getStudentByCourse(int id);
	vector<int> getCourseByStudent(string account);
	bool recordToStream(ostream& os);
	template<typename K,typename V>
	bool checkExist(multimap<K,V>& map, const K& key, const V& val, bool needDelete = false);
	

};
	
class CourseSelectionTable{
public:
	//��֧���Ŀγ� 
	static  OrderTable paidOrder;
	//δ֧���Ŀγ̶���
	static OrderTable unpaidOrder; 
	
	const static  char* paidOrderFile;//���ݴ洢�ļ�
	const static  char* unpaidOrderFile;//���ݴ洢�ļ�
	static bool storeInfo(); 
	static bool loadInfo();
	
};
#endif
