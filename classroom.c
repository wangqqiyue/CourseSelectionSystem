#ifndef INCLUDE_CLASSROOM
#include "classroom.h"
#endif

#ifndef INCLUDE_COURSE
#include "course.h"
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


#ifndef INCLUDE_CONIO
#include <conio.h>
#define INCLUDE_CONIO
#endif


#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif 


/*-----------------Classroom ����ʵ��-------------------------------------*/ 

vector<Classroom> Classroom::roomList;


bool Classroom::printTitleToStream(ostream& out){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	out << setw(Global::PRINT_WIDTH)<<"���ұ��" << setw(Global::PRINT_LONG_WIDTH) << "��������" << setw(Global::PRINT_WIDTH) << "��������"<< endl;
	return true;
}

//�ȿ����ں��������У�Ҳ�����ں�������������ȱʡ�����������ܼ��ں������������ں���������ͬʱ����ȱʡ������
//���������󣬵�����, �Ƿ�ֻ��ӡһ����¼ 
bool Classroom::recordToStream(ostream& out, vector<Classroom>::iterator firstRecord, bool onlyOne){ 
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}

	if(!onlyOne){
		printTitleToStream(out);	
	}		
	
	for(vector<Classroom>::iterator i=Classroom::roomList.begin();i!=Classroom::roomList.end();i++){
		if(onlyOne){
			i=firstRecord;
		}
		out <<  setw(Global::PRINT_WIDTH)<<i->roomId << setw(Global::PRINT_LONG_WIDTH) <<	i->roomName << setw(Global::PRINT_WIDTH)  << i->capacity << endl;
		if(onlyOne){
			break;
		}	
	}

	return true;
}


//����id��ȡ�������� 
Classroom* Classroom::getElementById(int id){
	for(vector<Classroom>::iterator i=Classroom::roomList.begin();i!=Classroom::roomList.end();i++){
		if(i->roomId == id){
			return const_cast<Classroom*>(&(*i));
		}
	}
}


const char* Classroom::dataFile = "classroomsInfo.txt"; 

bool Classroom::storeInfo(){
	bool result = true;
	ofstream out;
	//���ع���Ա�˺�����
	out.open(dataFile,ios::out);
	if(!Classroom::recordToStream(out,roomList.begin())){
		result= false;
	}

	out.close();
	return result;
}

bool Classroom::loadInfo(){
	ifstream in;
	string temp;
	
	//���ع���Ա�˺�����
	in.open(dataFile,ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		int roomId,capacity;
		string roomName;
		
		stringstream ss(temp);
		ss >> roomId;
		ss >> roomName;
		ss >> capacity;
		
		Classroom cr(roomId,roomName,capacity);
		Classroom::roomList.push_back(cr);
	}		
	in.close();
}

bool Classroom::checkIdExist(int id,vector<Classroom>::iterator &i){
	for(i=Classroom::roomList.begin();i!=roomList.end();i++){
		if(i->roomId == id){
			return true;
		}
	}
	return false;
}


//ѡ��˵�  idList��һ���γ�id������ , selectList ��ѡ���, classroomTotal �ǿ�ѡ������, isInclusion��ʾ�ǰ���idList�еĿγ̣��������� 
bool Classroom::getSelection(const vector<int>& idList, int* selectList, const int& classroomTotal,bool isInclusion){
		
	static bool firstPrint = true;
	int currentLine = 0;
	int line = 0;
	vector<Classroom>::iterator i;
	int selectTotal = 0;
	
	while (true) {
        if (_kbhit()|| firstPrint) {

	
        	clear();
        	//����͹���˵�� 
			cout << "----------------ɾ������ʹ�õĽ���----------------" << endl;
			
			//��ʾ��ǰ״̬ 
			float priceTotal = 0;
			cout << "ѡ��״̬" << endl;
			cout << "��ѡ��������:" << selectTotal << "(";

            for(i=roomList.begin(),line=0;i!=roomList.end();i++){
            	
            	if(isInclusion){//������idList�����Ŀ 
            		if(!checkExist(idList,i->roomId)){
						continue;
					}
				}else{//����idList�����Ŀ 
					if(checkExist(idList,i->roomId)){
						continue;
					}
				}
				
				if(1 == selectList[line]){
					cout << i->roomName << " ";
				} 
				line++;
			}
			
			cout << ")" << endl;

			//��ȡ���� 
			if(!firstPrint){
	            char ch = _getch();
	            if (ch == 72) { // �ϼ�ͷ��
	                currentLine--;
	                if (currentLine < 0) {
	                    currentLine += classroomTotal;
	                }
					
	            } else if (ch == 80) { // �¼�ͷ��
	                currentLine++;
	                currentLine%=classroomTotal;
	            } else if(ch == 13) {//�س��� 
	            		selectList[currentLine] += 1;
	            		selectList[currentLine] %= 2;	            		
	        	}else if(ch == 'y'){
	        		firstPrint = true;
	        		return true;
				}else if(ch == 'q'){
					firstPrint = true;
	        		return false;
				}
			}

			Classroom::printTitleToStream(cout);
			//�������пγ��� 
            for(i=roomList.begin(),line=0,selectTotal=0;i!=roomList.end();i++){
            	            	
            	if(isInclusion){//������idList�����Ŀ 
            		if(!checkExist(idList,i->roomId)){
						continue;
					}
				}else{//����idList�����Ŀ 
					if(checkExist(idList,i->roomId)){
						continue;
					}
				}
				
            	//��ǰ�и��� 
            	if(line == currentLine){
            		setConsoleColor(FOREGROUND_GREEN |  FOREGROUND_INTENSITY | BACKGROUND_INTENSITY); // ����ǰ��ɫΪ��ɫ
				}

				//�����ǰ�γ̱�ѡ�У������ 
				if(1 == selectList[line]){
            		setConsoleColor(BACKGROUND_GREEN |  FOREGROUND_INTENSITY | BACKGROUND_INTENSITY); // ���ñ���ɫΪ��ɫ
            		selectTotal++;
				}
				
            	recordToStream(cout,i,true);
            	setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // �ָ�Ĭ����ɫ
            	line++;
			}
			firstPrint = false;
			
			cout <<"������ʾ�� ����ѡ��, �س���ѡ��, [y]��ȷ��, [q] ���˳�" << endl;
        }
        
    }
} 

bool Classroom::del(){
	int *selectList;//��ѡ��Ŀγ��б�, ���ѡ����Ϊ1 
	int classroomTotal;//��ѡ�γ�������
	int line=0;//���±� 
	vector<Course>::iterator i;//�γ̱��������� 
    
    //��ʼ�� 
    vector<int> undeletableList;//����ɾ�γ��б�
    for(i=Course::courseList.begin();i!=Course::courseList.end();i++){
    	//����γ�������Ϊ0���Ҹý���δ���뵽����ɾ���б������ 
    	if(0 != i->studentNumber){
    		if(!checkExist(undeletableList,i->roomId)){
    			undeletableList.push_back(i->roomId);
			}
		}
	}
    
	classroomTotal = roomList.size() - undeletableList.size();//��ɾ�����ҵ�������
	if(0 == classroomTotal){
		clear();
		cout << "Ŀǰû�п���ɾ���Ľ���" << endl;
		goPrevious(); 
		return false;
	}

	selectList = new int[classroomTotal];
    for(int i=0;i<classroomTotal;i++){
    	selectList[i] = 0;
	}
	
	if(!getSelection(undeletableList,selectList,classroomTotal,false)){
		free(selectList);
		return false;
	}
	
	
	if(checkAllZero(selectList,classroomTotal)){
		cout << "��δ��ѡ��" << endl;
		goPrevious();
		return false;
	}
	
    //ȷ��ѡ�ν����ɾ�� 
    cout << "���½�����ɾ��"  << endl;
    printTitleToStream(cout);
    vector<Classroom>::iterator it;
    for(it=roomList.begin(),line=0;it!=roomList.end();it++){
    	//���������˵Ŀγ� 
		if(checkExist(undeletableList,it->roomId)){
			continue;
		}
		if(1 == selectList[line]){
			recordToStream(cout,it,true);
			it = roomList.erase(it);// erase֮���ǰ������ָ�����̡����������ʧЧ,�ᱨ��
			it--;
		}
    	line++;
	}

    free(selectList);
	goPrevious(); 
	return true;
}

//��ѯ�������� 
bool Classroom::retrieve(){
	clear();
	cout << "------������Ϣ��ѯ-----"	<< endl;
	recordToStream(cout,Classroom::roomList.begin());
	goPrevious();
	return true;
	
}

/*������������ 
��Ҫ�ж����������Ƿ����ظ�,�����󲻳��������������� 
*/
bool Classroom::create(){
	int id,capacity;
	string name;

	char comfirm = 'y';
	clear();
	cout << "------����������Ϣ-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(Classroom::roomList.size() >= Global::ROOM_NUMBER_MAX){
			cout << "���������Ѵ�����("<< Global::ROOM_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "��������Ϣ" << endl;
		cout<<"���ұ��:";
		cin >> id;
		if(!isInputOk()){
			continue;
		}
		
		vector<Classroom>::iterator i;
		for(i=Classroom::roomList.begin();i!=Classroom::roomList.end();++i){
			if(i->roomId == id){
				cout << "�ñ���Ѵ��ڣ�������ѡ��" << endl;
				break;
			}
		}
		if(i != Classroom::roomList.end()){
			cout << "�Ƿ����?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "��������:" ;
		cin >> name;
		for(i=Classroom::roomList.begin();i!=Classroom::roomList.end();++i){
			if(i->roomName == name){
				cout << "�������Ѵ��ڣ�������ѡ��" << endl;
				break;
			}
		}
		if(i != Classroom::roomList.end()){
			cout << "�Ƿ����?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "��������";
		cin >> capacity;
		
		Classroom cr(id,name,capacity);
		Classroom::roomList.push_back(cr);
		
		cout << "��������������" << endl;
		cout << setw(Global::PRINT_WIDTH)<<"���ұ��" << setw(Global::PRINT_LONG_WIDTH) << "��������" << setw(Global::PRINT_LONG_WIDTH) << "��������"<< endl;
		cout <<  setw(Global::PRINT_WIDTH)<<id << setw(Global::PRINT_LONG_WIDTH) <<	name << setw(Global::PRINT_LONG_WIDTH)  << capacity << endl;
		
		
		cout << "�Ƿ����?Y/N" << endl;
		cin >> comfirm;
	}
	
	cout << "�������������һ��" << endl;
	cin.ignore();
	getchar();
	return true;
	
}
