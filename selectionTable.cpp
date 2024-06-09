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


/*-----------------CourseSelectionTable ����ʵ��-------------------------------------*/ 

OrderTable CourseSelectionTable::paidOrder;
OrderTable CourseSelectionTable::unpaidOrder;

//��� 
template<typename K,typename V>
bool OrderTable::checkExist(multimap<K,V>& map, const K& key, const V& val, bool needDelete){
	int count = 0;

    for (typename multimap<K, V>::iterator it = map.begin(); it != map.end(); ) {
        if (it->first == key && it->second == val) {
            count++;
            if(needDelete){
            	map.erase(it++);// erase֮���ǰ������ָ�����̡����������ʧЧ,�ᱨ�� 
            	continue;
			}
        }
        it++; 
    }
    
    return count != 0;
}

//��multimap�в�����Ӧ��,����ֵ���� 
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
    	cerr << "����ʧ�ܣ��ظ�����Ŀ<" << id << "," << account <<"> �Ѵ���" << endl;
    	result= false;
	}else{
		courseKeyMap.insert(make_pair(id,account));
	}
	

    if(checkExist(studentKeyMap,account,id)){
    	cerr << "����ʧ�ܣ��ظ�����Ŀ<" << account << "," << id <<"> �Ѵ���" << endl;
    	result=  false;
	}else{
		studentKeyMap.insert(make_pair(account,id));
	}
    
	return 	result;
}

bool OrderTable::deleteEntry(int id, string account){
	bool result=true;
    if(!checkExist(courseKeyMap,id,account,true)){
    	cerr << "ɾ��ʧ�ܣ���Ŀ<" << id << "," << account <<"> ������" << endl;
    	result=  false;
	}
	
    if(!checkExist(studentKeyMap,account,id,true)){
    	cerr << "ɾ��ʧ�ܣ���Ŀ<" << account << "," << id <<"> ������" << endl;
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
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_WIDTH)<<"�γ̱��" << setw(Global::PRINT_LONG_WIDTH) << "ѧ���˺�"<< endl;
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

	//д��ǰ�����ļ�����Ϊ��ͨ 
	SetFileAttributes(paidOrderFile, FILE_ATTRIBUTE_NORMAL);
	
	out.open(paidOrderFile,ios::out);
	if(!paidOrder.recordToStream(out)){
		result= false;
	}
	out.close();
	//д��������ļ�����Ϊֻ��,��ֹ�����޸� 
	SetFileAttributes(paidOrderFile, FILE_ATTRIBUTE_READONLY);
	
	//д��ǰ�����ļ�����Ϊ��ͨ 
	SetFileAttributes(unpaidOrderFile, FILE_ATTRIBUTE_NORMAL);
	out.open(unpaidOrderFile,ios::out);
	if(!unpaidOrder.recordToStream(out)){
		result= false;
	}
	out.close(); 
	//д��������ļ�����Ϊֻ��,��ֹ�����޸� 
	SetFileAttributes(unpaidOrderFile, FILE_ATTRIBUTE_READONLY);
	
	return result;
}

bool CourseSelectionTable::loadInfo(){
	ifstream in;
	string temp;
	
	//����ѡ�α� 
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
	
	//���ض����� 
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


