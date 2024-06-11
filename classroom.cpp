#ifndef INCLUDE_CLASSROOM
#include "classroom.h"
#endif

#ifndef INCLUDE_COURSE
#include "course.h"
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

bool Classroom::recordToStream(ostream& out){ 
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	
	out <<  setw(Global::PRINT_WIDTH)<< roomId << setw(Global::PRINT_LONG_WIDTH) <<	 roomName << setw(Global::PRINT_WIDTH)  <<  capacity << endl;

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
	//д��ǰ�����ļ�����Ϊ��ͨ 
	SetFileAttributes(dataFile, FILE_ATTRIBUTE_NORMAL);
	
	//���ع���Ա�˺�����
	out.open(dataFile,ios::out);
	if(!Classroom::recordToStream(out,roomList.begin())){
		result= false;
	}

	out.close();
	
	//д��������ļ�����Ϊֻ��,��ֹ�����޸� 
	SetFileAttributes(dataFile, FILE_ATTRIBUTE_READONLY);
	
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

bool Classroom::checkIdExist(int id){
	for(vector<Classroom>::iterator i=Classroom::roomList.begin();i!=roomList.end();i++){
		if(i->roomId == id){
			return true;
		}
	}
	return false;
}

bool Classroom::checkNameExist(string name){
	for(vector<Classroom>::iterator i=Classroom::roomList.begin();i!=roomList.end();i++){
		if(i->roomName == name){
			return true;
		}
	}
	return false;
}



//ѡ��˵�  idList��һ���γ�id������ , selectList ��ѡ���, classroomTotal �ǿ�ѡ������, isInclusion��ʾ�ǰ���idList�еĿγ̣��������� 
bool Classroom::getSelection(const string prompt, const vector<int>& idList, int* selectList, const int& classroomTotal,bool isInclusion,bool onlyOne){
		
	static bool firstPrint = true;
	int currentLine = 0;
	int line = 0;
	vector<Classroom>::iterator i;
	int selectTotal = 0;
	
	while (true) {
        if (_kbhit()|| firstPrint) {

	
        	clear();
        	//����͹���˵�� 
			cout << "----------------"<<prompt<<"----------------" << endl;
			
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
	            	if(onlyOne){
	            		firstPrint = true;
	        			return true;
					}
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
    	//����γ�������Ϊ0���Ҹý���δ���뵽����ɾ���б�������� 
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
	
	if(!getSelection("ɾ��δ��ʹ�õĽ���", undeletableList,selectList,classroomTotal,false)){
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

bool Classroom::update(){
	int *selectList;//��ѡ��Ŀγ��б�, ���ѡ����Ϊ1 
	int classroomTotal;//��ѡ�γ�������
	int line=0;//���±� 
	vector<Course>::iterator i;//�γ̱��������� 
    
    //��ʼ�� 
    vector<int> unchanableList;//���ɸĵĿγ��б�
    for(i=Course::courseList.begin();i!=Course::courseList.end();i++){
    	//����γ�������Ϊ0���Ҹý���δ���뵽����ɾ���б�������� 
    	if(0 != i->studentNumber){
    		if(!checkExist(unchanableList,i->roomId)){
    			unchanableList.push_back(i->roomId);
			}
		}
	}
    
	classroomTotal = roomList.size() - unchanableList.size();//��ɾ�����ҵ�������
	if(0 == classroomTotal){
		clear();
		cout << "Ŀǰû�п����޸ĵĽ���" << endl;
		goPrevious(); 
		return false;
	}

	selectList = new int[classroomTotal];
    for(int i=0;i<classroomTotal;i++){
    	selectList[i] = 0;
	}
	
	if(!getSelection("�޸�δ��ʹ�õĽ���", unchanableList,selectList,classroomTotal,false,true)){
		free(selectList);
		return false;
	}
	
	if(checkAllZero(selectList,classroomTotal)){
		cout << "��δ��ѡ��" << endl;
		goPrevious();
		return false;
	}
	
    //ȷ��ѡ�������޸� 
    cout << "���½��Ҵ��޸�"  << endl;
    printTitleToStream(cout);
    vector<Classroom>::iterator it;
    for(it=roomList.begin(),line=0;it!=roomList.end();it++){
    	//���������˵Ŀγ� 
		if(checkExist(unchanableList,it->roomId)){
			continue;
		}
		if(1 == selectList[line]){
			recordToStream(cout,it,true);
			changeInfo(it); 	
			break;
		}
    	line++;
	}

    free(selectList);
	goPrevious(); 
	return true;
}


bool Classroom::changeInfo(vector<Classroom>::iterator &it){
	int id,capacity;
	string name;
	
	if(it == roomList.end()){
		cerr <<"��Ч�ĵ�����" << endl;
		return false;
	}

	char confirm = 'y';
	while('y' == confirm || 'Y' == confirm){
		cout<<"���ұ��:";
		cin >> id;
		if(!isInputOk()){
			continue;
		}

		if(checkIdExist(id)){
			cout << "�ñ���Ѵ��ڣ�������ѡ��" << endl;
			cout << "�Ƿ����?Y/N" << endl;
			cin >> confirm;
			continue;
		}
		break;
	}
	if('y' != confirm && 'Y' != confirm){
		return false;
	}
		
	while('y' == confirm || 'Y' == confirm){
		cout << "��������:" ;
		cin >> name;

		if(checkNameExist(name)){
			cout << "�������Ѵ��ڣ�������ѡ��" << endl;
			cout << "�Ƿ����?Y/N" << endl;
			cin >> confirm;
			continue;
		}
		break;
	}
	if('y' != confirm && 'Y' != confirm){
		return false;
	}
		
	while('y' == confirm || 'Y' == confirm){
		cout << "��������";
		cin >> capacity;
		
		if(capacity < Global::ROOM_CAPACITY_MIN || capacity > Global::ROOM_CAPACITY_MAX){
			cout << "����������Ҫ�ں�����Χ("<< Global::ROOM_CAPACITY_MIN <<"--"<< Global::ROOM_CAPACITY_MAX <<")"<<endl;
			cout << "�Ƿ����?Y/N" << endl;
			cin >> confirm;
			continue;
		}
		break;
	}
	if('y' != confirm && 'Y' != confirm){
		return false;
	}
	
		
	it->roomId = id;
	it->roomName = name;
	it->capacity = capacity;
		
	cout << "�޸�����" << endl;
	printTitleToStream(cout);
	recordToStream(cout,it,true);
	return true;
}

//��ѯ�������� 
bool Classroom::retrieve(){
	clear();
	cout << "------������Ϣ��ѯ-----"	<< endl;
	cout << setw(Global::PRINT_WIDTH) << "���ұ��" << setw(Global::PRINT_LONG_WIDTH) << "��������" << setw(Global::PRINT_WIDTH) << "��������" << setw(Global::PRINT_LONG_WIDTH) << "�Ѱ��ſγ�" << endl;
	for(vector<Classroom>::iterator i=roomList.begin();i!=roomList.end();i++){

		cout << setw(Global::PRINT_WIDTH) << i->roomId << setw(Global::PRINT_LONG_WIDTH) << i->roomName << setw(Global::PRINT_WIDTH) << i->capacity ;	
		vector<Course>::iterator c;
		int courseTotal=0;
		for(c=Course::courseList.begin();c!=Course::courseList.end();c++){
			if(c->roomId == i->roomId){
				cout <<" "<< c->courseName <<" ";
				courseTotal++;
			}
		}		
		if(0!=courseTotal){
			cout << endl;
		}
		else{
			cout << "����" << endl;
		}
	}
	goPrevious();
	return true;
	
}

/*������������ 
��Ҫ�ж����������Ƿ����ظ�,�����󲻳��������������� 
*/
bool Classroom::create(){
	int id,capacity;
	string name;

	char confirm = 'y';
	clear();
	cout << "------����������Ϣ-----"	<< endl;
	
	while('y' == confirm || 'Y' == confirm){			

		if(Classroom::roomList.size() >= Global::ROOM_NUMBER_MAX){
			cout << "���������Ѵ�����("<< Global::ROOM_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "��������Ϣ" << endl;
		
		while('y' == confirm || 'Y' == confirm){
			cout<<"���ұ��:";
			cin >> id;
			if(!isInputOk()){
				continue;
			}

			if(checkIdExist(id)){
				cout << "�ñ���Ѵ��ڣ�������ѡ��" << endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> confirm;
				continue;
			}
			break;
		}
		if('y' != confirm && 'Y' != confirm){
			break;
		}
		
		while('y' == confirm || 'Y' == confirm){
			cout << "��������:" ;
			cin >> name;

			if(checkNameExist(name)){
				cout << "�������Ѵ��ڣ�������ѡ��" << endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> confirm;
				continue;
			}
			break;
		}
		if('y' != confirm && 'Y' != confirm){
			break;
		}
		
		while('y' == confirm || 'Y' == confirm){
			cout << "��������";
			cin >> capacity;
			
			if(capacity < Global::ROOM_CAPACITY_MIN || capacity > Global::ROOM_CAPACITY_MAX){
				cout << "����������Ҫ�ں�����Χ("<< Global::ROOM_CAPACITY_MIN <<"--"<< Global::ROOM_CAPACITY_MAX <<")"<<endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> confirm;
				continue;
			}
			break;
		}
		if('y' != confirm && 'Y' != confirm){
			break;
		}
		
		Classroom cr(id,name,capacity);
		cout << "����������������" << endl;
		printTitleToStream(cout);
		cr.recordToStream(cout);
		cout << "�Ƿ�ȷ������?Y/N" << endl;
		cin >> confirm;
		if('y' == confirm || 'Y' == confirm){	
			roomList.push_back(cr);
			cout << "��������������" << endl;
			recordToStream(cout,roomList.end()-1,true);
		}else{
			cout <<"��ȡ������"<<endl;
		}

		cout << "�Ƿ����?Y/N" << endl;
		cin >> confirm;
	}
	
	goPrevious();
	return true;
	
}