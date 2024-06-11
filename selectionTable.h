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
/*---------------------课程学生关系表-----------------------*/
//订单表 内部类 
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
	//已支付的课程 
	static  OrderTable paidOrder;
	//未支付的课程订单
	static OrderTable unpaidOrder; 
	
	const static  char* paidOrderFile;//数据存储文件
	const static  char* unpaidOrderFile;//数据存储文件
	static bool storeInfo(); 
	static bool loadInfo();
	
};
#endif
