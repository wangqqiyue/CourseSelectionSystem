#ifndef INCLUDE_SELECTION_TABLE
#include "selectionTable.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_FSTREAM
#include <fstream>
#define INCLUDE_FSTREAM
#endif

#ifndef INCLUDE_SSTREAM
#include <sstream>
#define INCLUDE_SSTREAM
#endif

#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif 


/*-----------------CourseSelectionTable 定义实现-------------------------------------*/ 

OrderTable CourseSelectionTable::paidOrder;
OrderTable CourseSelectionTable::unpaidOrder;

//检查 
template<typename K,typename V>
bool OrderTable::checkExist(multimap<K,V>& map, const K& key, const V& val, bool needDelete){
	int count = 0;

    for (typename multimap<K, V>::iterator it = map.begin(); it != map.end(); ) {
        if (it->first == key && it->second == val) {
            count++;
            if(needDelete){
            	map.erase(it++);// erase之后，令当前迭代器指向其后继。否则迭代器失效,会报错 
            	continue;
			}
        }
        it++; 
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


const char* CourseSelectionTable::paidOrderFile = "paidOrder.txt"; 
const char* CourseSelectionTable::unpaidOrderFile = "unpaidOrder.txt"; 

bool CourseSelectionTable::storeInfo(){
	bool result = true;
	ofstream out;

	//写入前设置文件属性为普通 
	SetFileAttributes(paidOrderFile, FILE_ATTRIBUTE_NORMAL);
	
	out.open(paidOrderFile,ios::out);
	if(!paidOrder.recordToStream(out)){
		result= false;
	}
	out.close();
	//写入后设置文件属性为只读,防止他人修改 
	SetFileAttributes(paidOrderFile, FILE_ATTRIBUTE_READONLY);
	
	//写入前设置文件属性为普通 
	SetFileAttributes(unpaidOrderFile, FILE_ATTRIBUTE_NORMAL);
	out.open(unpaidOrderFile,ios::out);
	if(!unpaidOrder.recordToStream(out)){
		result= false;
	}
	out.close(); 
	//写入后设置文件属性为只读,防止他人修改 
	SetFileAttributes(unpaidOrderFile, FILE_ATTRIBUTE_READONLY);
	
	return result;
}

bool CourseSelectionTable::loadInfo(){
	ifstream in;
	string temp;
	
	//加载选课表 
	in.open(paidOrderFile,ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		string account;
		int id;
		
		stringstream ss(temp);
		ss >> id;
		ss >> account;

		paidOrder.addEntry(id,account);
	}
	in.close();
	
	//加载订单表 
	in.open(unpaidOrderFile,ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		string account;
		int id;
		
		stringstream ss(temp);
		ss >> id;
		ss >> account;

		unpaidOrder.addEntry(id,account);
	}
	in.close();
}


