#ifndef INCLUDE_COURSE_RESOURCE
#include "courseResource.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


vector<Course> g_courseList;
vector<Classroom> g_roomList;

/*-----------------CourseSelectionTable 定义实现-------------------------------------*/ 

OrderTable CourseSelectionTable::paidOrder;
OrderTable CourseSelectionTable::unpaidOrder;

//检查 
template<typename K,typename V>
bool OrderTable::checkExist(multimap<K,V>& map, const K& key, const V& val, bool needDelete){
	int count = 0;

    for (typename multimap<K, V>::iterator it = map.begin(); it != map.end(); ++it) {
        if (it->first == key && it->second == val) {
            count++;
            if(needDelete){
            	map.erase(it);
			}
        }
    }
    
    return count != 0;
}

//在multimap中查找相应键,返回值向量 
template<typename K,typename V>
vector<V> getElementByKey(multimap<K,V>& map, const K& key){
	vector<V> result;
	pair<typename multimap<K, V>::iterator, typename multimap<K, V>::iterator> range = map.equal_range(key);
	for (typename multimap<K, V>::iterator it = range.first; it != range.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

bool OrderTable::addEntry(int id, string account){
	bool result=true;
	
    if(checkExist(courseKeyMap,id,account)){
    	cerr << "新增失败！重复的项目<" << id << "," << account <<"> 已存在" << endl;
    	result= false;
	}else{
		courseKeyMap.insert(make_pair(id,account));
	}
	

    if(checkExist(studentKeyMap,account,id)){
    	cerr << "新增失败！重复的项目<" << account << "," << id <<"> 已存在" << endl;
    	result=  false;
	}else{
		studentKeyMap.insert(make_pair(account,id));
	}
    
	return 	result;
}

bool OrderTable::deleteEntry(int id, string account){
	bool result=true;
    if(!checkExist(courseKeyMap,id,account,true)){
    	cerr << "删除失败！项目<" << id << "," << account <<"> 不存在" << endl;
    	result=  false;
	}
	
    if(!checkExist(studentKeyMap,account,id,true)){
    	cerr << "删除失败！项目<" << account << "," << id <<"> 不存在" << endl;
    	result=  false;
	}
    
	
	return 	result;
}

vector<string> OrderTable::getStudentByCourse(int id){
	return getElementByKey(courseKeyMap,id);
}

vector<int> OrderTable::getCourseByStudent(string account){
	return getElementByKey(studentKeyMap,account);
}

bool OrderTable::recordToStream(ostream& out){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_WIDTH)<<"课程编号" << setw(Global::PRINT_LONG_WIDTH) << "学生账号"<< endl;
	for(multimap<int,string>::iterator i=courseKeyMap.begin();i!=courseKeyMap.end();i++){
		out <<  setw(Global::PRINT_WIDTH) << i->first << setw(Global::PRINT_LONG_WIDTH) << i->second << endl;
	}
	return true;
}

/*-----------------Classroom 定义实现-------------------------------------*/ 

//既可以在函数声明中，也可以在函数定义中声明缺省参数，但不能既在函数声明中又在函数定义中同时声明缺省参数。
bool Classroom::recordToStream(ostream& out){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_WIDTH)<<"教室编号" << setw(Global::PRINT_LONG_WIDTH) << "教室名称" << setw(Global::PRINT_WIDTH) << "教室容量"<< endl;
	for(vector<Classroom>::iterator i=g_roomList.begin();i!=g_roomList.end();i++){
		out <<  setw(Global::PRINT_WIDTH)<<i->roomId << setw(Global::PRINT_LONG_WIDTH) <<	i->roomName << setw(Global::PRINT_WIDTH)  << i->capacity << endl;
	}
	return true;
}

bool Classroom::checkExist(int id, vector<Classroom>::iterator &i){
	for(i=g_roomList.begin();i!=g_roomList.end();i++){
		if(i->roomId == id){
			return true;
		}
	}
	return false;
}

/*-----------------Course 定义实现-------------------------------------*/ 

bool Course::printTitleToStream(ostream& out){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	out << setw(Global::PRINT_WIDTH)<<"课程编码" << setw(Global::PRINT_LONG_WIDTH) << "课程名" << setw(Global::PRINT_WIDTH) << "选课人数"<< setw(Global::PRINT_WIDTH) << "课程价格"<< setw(Global::PRINT_WIDTH) << "任课老师"<< setw(Global::PRINT_WIDTH) << "教室" << setw(Global::PRINT_WIDTH) <<  "人数限额" <<endl;	
	return true;
}

//传入流对象，迭代器, 是否只打印一条记录 
bool Course::recordToStream(ostream& out, vector<Course>::iterator firstRecord, bool onlyOne){ 
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}

	if(!onlyOne){
		printTitleToStream(out);	
	}		
	
	for(vector<Course>::iterator i = g_courseList.begin();i!=g_courseList.end();i++){
		if(onlyOne){
			i=firstRecord;
		}
		out <<  setw(Global::PRINT_WIDTH)<<i->courseId << setw(Global::PRINT_LONG_WIDTH) <<	i->courseName << setw(Global::PRINT_WIDTH)  << i->studentNumber << setw(Global::PRINT_WIDTH) << fixed << setprecision(2) << i->price << setw(Global::PRINT_WIDTH)  << i->teacherAccount << setw(Global::PRINT_WIDTH)  << i->roomId << setw(Global::PRINT_WIDTH)  << i->capacity << endl;
		if(onlyOne){
			break;
		}		
	}
	return true;
}

