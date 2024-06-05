#ifndef INCLUDE_COURSE_RESOURCE
#include "courseResource.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


vector<Course> g_courseList;
vector<Classroom> g_roomList;

/*-----------------CourseSelectionTable ����ʵ��-------------------------------------*/ 

OrderTable CourseSelectionTable::paidOrder;
OrderTable CourseSelectionTable::unpaidOrder;

//��� 
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

/*-----------------Classroom ����ʵ��-------------------------------------*/ 

//�ȿ����ں��������У�Ҳ�����ں�������������ȱʡ�����������ܼ��ں������������ں���������ͬʱ����ȱʡ������
bool Classroom::recordToStream(ostream& out){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_WIDTH)<<"���ұ��" << setw(Global::PRINT_LONG_WIDTH) << "��������" << setw(Global::PRINT_WIDTH) << "��������"<< endl;
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

/*-----------------Course ����ʵ��-------------------------------------*/ 

bool Course::printTitleToStream(ostream& out){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	out << setw(Global::PRINT_WIDTH)<<"�γ̱���" << setw(Global::PRINT_LONG_WIDTH) << "�γ���" << setw(Global::PRINT_WIDTH) << "ѡ������"<< setw(Global::PRINT_WIDTH) << "�γ̼۸�"<< setw(Global::PRINT_WIDTH) << "�ο���ʦ"<< setw(Global::PRINT_WIDTH) << "����" << setw(Global::PRINT_WIDTH) <<  "�����޶�" <<endl;	
	return true;
}

//���������󣬵�����, �Ƿ�ֻ��ӡһ����¼ 
bool Course::recordToStream(ostream& out, vector<Course>::iterator firstRecord, bool onlyOne){ 
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
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

