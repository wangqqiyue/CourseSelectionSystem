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

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif

#ifndef INCLUDE_CLASSROOM
#include "classroom.h"
#endif

#ifndef INCLUDE_CONIO
#include <conio.h>
#define INCLUDE_CONIO
#endif


#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif 


/*-----------------Course ����ʵ��-------------------------------------*/ 
vector<Course> Course::courseList;

const char* Course::dataFile = "coursesInfo.txt"; 

bool Course::storeInfo(){
	bool result = true;
	ofstream out;
	//д��ǰ�����ļ�����Ϊ��ͨ 
	SetFileAttributes(dataFile, FILE_ATTRIBUTE_NORMAL);
	
	//���ع���Ա�˺�����
	out.open(dataFile,ios::out);
	if(!Course::recordToStream(out,Course::courseList.begin())){
		result= false;
	}

	out.close();
	
	//д��������ļ�����Ϊֻ��,��ֹ�����޸� 
	SetFileAttributes(dataFile, FILE_ATTRIBUTE_READONLY);
	return result;
}

bool Course::loadInfo(){
	ifstream in;
	string temp;
	
	//���ع���Ա�˺�����
	in.open(dataFile,ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		int courseId,number,classroomId,capacity;
		float price;
		string courseName,teacherAccount;
		
		stringstream ss(temp);
		ss >> courseId;
		ss >> courseName;
		ss >> number;
		ss >> price;
		ss >> teacherAccount;
		ss >> classroomId;
		ss >> capacity;
		
		Course c(courseId,courseName,number,price,teacherAccount,classroomId,capacity);
		Course::courseList.push_back(c);
	}
	in.close();
}

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
	
	for(vector<Course>::iterator i = Course::courseList.begin();i!=Course::courseList.end();i++){
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

 
bool Course::recordToStream(ostream& out){ 
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	out <<  setw(Global::PRINT_WIDTH)<< courseId << setw(Global::PRINT_LONG_WIDTH) <<	 courseName << setw(Global::PRINT_WIDTH)  <<  studentNumber << setw(Global::PRINT_WIDTH) << fixed << setprecision(2) << price << setw(Global::PRINT_WIDTH)  <<  teacherAccount << setw(Global::PRINT_WIDTH)  << roomId << setw(Global::PRINT_WIDTH)  << capacity << endl;
	return true;
}

Course* Course::getElementById(int id){
		for(vector<Course>::iterator i=Course::courseList.begin();i!=Course::courseList.end();i++){
		if(i->courseId == id){
			return const_cast<Course*>(&(*i));
		}
	}
}

/*�����γ����� 
��Ҫ�ж����������Ƿ����ظ�,�����󲻳����γ��������� 
*/
bool Course::create(){
	int id,roomId,capacity;
	float price;
	string name,teacherAccount;

	char comfirm = 'y';
	clear();
	cout << "------�����γ���Ϣ-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(Course::courseList.size() >= Global::COURSE_NUMBER_MAX){
			cout << "�γ������Ѵ�����("<< Global::COURSE_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "��������Ϣ" << endl;
		
		while('y' == comfirm || 'Y' == comfirm){
			cout<<"�γ̱��:";
			cin >> id;
			if(!isInputOk()){
				continue;
			}
			
			vector<Course>::iterator i;
			for(i=Course::courseList.begin();i!=Course::courseList.end();++i){
				if(i->courseId == id){
					cout << "�ñ���Ѵ��ڣ�������ѡ��" << endl;
					break;
				}
			}
			if(i != Course::courseList.end()){
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
		
		
		while('y' == comfirm || 'Y' == comfirm){
			cout << "�γ�����:" ;
			cin >> name;
			
			vector<Course>::iterator i;
			for(i=Course::courseList.begin();i!=Course::courseList.end();++i){
				if(i->courseName == name){
					cout << "�������Ѵ��ڣ�������ѡ��" << endl;
					break;
				}
			}
			if(i != Course::courseList.end()){
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
		
		while('y' == comfirm || 'Y' == comfirm){
			cout << "�γ̼۸�";
			cin >> price;
			if(price < 0 || price > Global::COURSE_PRICE_MAX){
				cout << "�γ̼۸���Ҫ�ں���Χ(0--"<< Global::COURSE_PRICE_MAX <<")������������:" << endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
		
		while('y' == comfirm || 'Y' == comfirm){
			cout<<"��ʦ�ʺ�:";
			cin >> teacherAccount;

			if(!Teacher::checkAccountExist(teacherAccount)){
				cout << "�ñ�Ų����ڣ�������ѡ��" << endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}

		while('y' == comfirm || 'Y' == comfirm){
			cout << "�γ������޶�";
			cin >> capacity;
			if(capacity < Global::COURSE_CAPACITY_MIN || capacity > Global::COURSE_CAPACITY_MAX){
				cout << "�γ������޶���Ҫ�ں���Χ("<< Global::COURSE_CAPACITY_MIN <<"--"<< Global::COURSE_CAPACITY_MAX <<")"<<endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
		
		while('y' == comfirm || 'Y' == comfirm){
			cout<<"���ұ��:";
			cin >> roomId;
			if(!isInputOk()){
				continue;
			}
			vector<Classroom>::iterator i;
			if(!Classroom::checkIdExist(roomId,i)){
				cout << "�ñ�Ų����ڣ�������ѡ��" << endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else if(i->capacity < capacity){
				cout << "�ý��ҽ�������" << i->capacity << "��, ������ѡ��" << endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
		
		//�½��γ̶��󣬲���ӵ�����β�� 
		Course c(id,name,0,price,teacherAccount,roomId,capacity);
		cout << "����������������" << endl;
		printTitleToStream(cout);
		c.recordToStream(cout);
		cout << "�Ƿ�ȷ������?Y/N" << endl;
		cin >> comfirm;
		if('y' == comfirm || 'Y' == comfirm){	
			courseList.push_back(c);
			cout << "��������������" << endl;
			recordToStream(cout,Course::courseList.end() - 1,true);
		}else{
			cout <<"��ȡ������"<<endl;
		}

		cout << "�Ƿ����?Y/N" << endl;
		cin >> comfirm;
	}
	
	goPrevious();
	return true;
	
}

//ѡ��˵�  idList��һ���γ�id������ , selectList ��ѡ���, courseTotal �ǿ�ѡ������, isInclusion��ʾ�ǰ���idList�еĿγ̣��������� 
bool Course::getSelection(const string prompt, const vector<int>& idList, int* selectList, const int& courseTotal,bool isInclusion,bool onlyOne){
		
	static bool firstPrint = true;
	int currentLine = 0;
	int line = 0;
	vector<Course>::iterator i;
	int selectTotal = 0;
	
	while (true) {
        if (_kbhit()|| firstPrint) {

	
        	clear();
        	//����͹���˵�� 
			cout << "----------------"<<prompt<<"----------------" << endl;
			
			//��ʾ��ǰ״̬ 
			float priceTotal = 0;
			cout << "ѡ��״̬" << endl;
			cout << "��ѡ�γ�����:" << selectTotal << "(";

            for(i=Course::courseList.begin(),line=0;i!=Course::courseList.end();i++){
            	
            	if(isInclusion){//������idList�����Ŀ 
            		if(!checkExist(idList,i->courseId)){
						continue;
					}
				}else{//����idList�����Ŀ 
					if(checkExist(idList,i->courseId)){
						continue;
					}
				}
				
				if(1 == selectList[line]){
					cout << i->courseName << " ";
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
	                    currentLine += courseTotal;
	                }
					
	            } else if (ch == 80) { // �¼�ͷ��
	                currentLine++;
	                currentLine%=courseTotal;
	            } else if(ch == 13) {//�س��� 
	            		selectList[currentLine] += 1;
	            		selectList[currentLine] %= 2;	        
						if(onlyOne) {
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

			Course::printTitleToStream(cout);
			//�������пγ��� 
            for(i=Course::courseList.begin(),line=0,selectTotal=0;i!=Course::courseList.end();i++){
            	            	
            	if(isInclusion){//������idList�����Ŀ 
            		if(!checkExist(idList,i->courseId)){
						continue;
					}
				}else{//����idList�����Ŀ 
					if(checkExist(idList,i->courseId)){
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
				
            	Course::recordToStream(cout,i,true);
            	setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // �ָ�Ĭ����ɫ
            	line++;
			}
			firstPrint = false;
			
			cout <<"������ʾ�� ����ѡ��, �س���ѡ��, [y]��ȷ��, [q] ���˳�" << endl;
        }
        
    }
} 

bool Course::del(){
	int *selectList;//��ѡ��Ŀγ��б�, ���ѡ����Ϊ1 
	int courseTotal;//��ѡ�γ�������
	int line=0;//���±� 
	vector<Course>::iterator i;//�γ̱��������� 
    
    //��ʼ�� 
    vector<int> deletableList;//��ɾ�γ��б�
    for(i=courseList.begin();i!=courseList.end();i++){
    	if(0 == i->studentNumber){
    		deletableList.push_back(i->courseId);
		}
	}
    
	courseTotal = deletableList.size();//���˿γ�������
	if(0 == courseTotal){
		clear();
		cout << "Ŀǰû�п���ɾ���Ŀγ�" << endl;
		goPrevious(); 
		return false;
	}

	selectList = new int[courseTotal];
    for(int i=0;i<courseTotal;i++){
    	selectList[i] = 0;
	}
	
	if(!getSelection("ɾ������ѡ�εĿγ�",deletableList,selectList,courseTotal)){
		free(selectList);
		return false;
	}
	
	if(checkAllZero(selectList,courseTotal)){
		cout << "��δ��ѡ��" << endl;
		goPrevious();
		return false;
	}
	
    //ȷ��ѡ�ν����ɾ�� 
    cout << "���¿γ���ɾ��"  << endl;
    Course::printTitleToStream(cout);
    for(i=Course::courseList.begin(),line=0;i!=Course::courseList.end();i++){
    	//���������˵Ŀγ� 
		if(!checkExist(deletableList,i->courseId)){
			continue;
		}
		if(1 == selectList[line]){
			recordToStream(cout,i,true);
			i = courseList.erase(i);// erase֮���ǰ������ָ�����̡����������ʧЧ,�ᱨ��
			i--;
		}
    	line++;
	}

    free(selectList);
	goPrevious(); 
	return true;
}


//��ѯ�γ����� 
bool Course::retrieve(){
	clear();
	cout << "------�γ���Ϣ��ѯ-----"	<< endl;
	recordToStream(cout,Course::courseList.begin());
	goPrevious();
	return true;
	
}

//�޸Ŀγ���Ϣ 
bool Course::update(){
	int *selectList;//��ѡ��Ŀγ��б�, ���ѡ����Ϊ1 
	int courseTotal;//��ѡ�γ�������
	int line=0;//���±� 
	vector<Course>::iterator i;//�γ̱��������� 
    
    //��ʼ�� 
    vector<int> unchangableList;//��ɾ�γ��б�
    for(i=courseList.begin();i!=courseList.end();i++){
    	if(0 != i->studentNumber){
    		unchangableList.push_back(i->courseId);
		}
	}
    
	courseTotal = courseList.size() - unchangableList.size();//���˿γ�������
	if(0 == courseTotal){
		clear();
		cout << "Ŀǰû�п����޸ĵĿγ�" << endl;
		goPrevious(); 
		return false;
	}

	selectList = new int[courseTotal];
    for(int i=0;i<courseTotal;i++){
    	selectList[i] = 0;
	}
	
	if(!getSelection("�޸�����ѡ��Ŀγ���Ϣ",unchangableList,selectList,courseTotal,false,true)){
		free(selectList);
		return false;
	}
	
	if(checkAllZero(selectList,courseTotal)){
		cout << "��δ��ѡ��" << endl;
		goPrevious();
		return false;
	}
	
    //ȷ��ѡ�ν����ɾ�� 
    cout << "���¿γ̴��޸�"  << endl;
    Course::printTitleToStream(cout);
    for(i=Course::courseList.begin(),line=0;i!=Course::courseList.end();i++){
    	//���������޸ĵĿγ� 
		if(checkExist(unchangableList,i->courseId)){
			continue;
		}
		if(1 == selectList[line]){
			recordToStream(cout,i,true);
			changeInfo(i); 
		}
    	line++;
	}

    free(selectList);
	goPrevious(); 
	return true;
}

//�޸Ŀγ���Ϣ 
bool Course::changeInfo(vector<Course>::iterator &it){
	char comfirm = 'y';
	int id,capacity,roomId;
	string name,teacherAccount;
	float price;


	cout << "��������Ϣ" << endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		cout<<"�γ̱��:";
		cin >> id;
		if(!isInputOk()){
			continue;
		}
		
		Course* c= getElementById(id);
		if(!c){
			cout << "�ñ���Ѵ��ڣ�������ѡ��" << endl;
			cout << "�Ƿ����?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		break;
	}
	if('y' != comfirm && 'Y' != comfirm){
		return false;
	}
	


	while('y' == comfirm || 'Y' == comfirm){
		cout << "�γ�����:" ;
		cin >> name;
		
		vector<Course>::iterator i;
		for(i=Course::courseList.begin();i!=Course::courseList.end();++i){
			if(i->courseName == name){
				cout << "�������Ѵ��ڣ�������ѡ��" << endl;
				break;
			}
		}
		if(i != Course::courseList.end()){
			cout << "�Ƿ����?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		break;
	}
	if('y' != comfirm && 'Y' != comfirm){
		return false;
	}
	
	while('y' == comfirm || 'Y' == comfirm){
		cout << "�γ̼۸�";
		cin >> price;
		if(price < 0 || price > Global::COURSE_PRICE_MAX){
			cout << "�γ̼۸���Ҫ�ں���Χ(0--"<< Global::COURSE_PRICE_MAX <<")������������:" << endl;
			cout << "�Ƿ����?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		break;
	}
	if('y' != comfirm && 'Y' != comfirm){
		return false;
	}
	
	while('y' == comfirm || 'Y' == comfirm){
		cout<<"��ʦ�ʺ�:";
		cin >> teacherAccount;

		if(!Teacher::checkAccountExist(teacherAccount)){
			cout << "�ñ�Ų����ڣ�������ѡ��" << endl;
			cout << "�Ƿ����?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		break;
	}
	if('y' != comfirm && 'Y' != comfirm){
		return false;
	}

	while('y' == comfirm || 'Y' == comfirm){
		cout << "�γ������޶�";
		cin >> capacity;
		if(capacity < Global::COURSE_CAPACITY_MIN || capacity > Global::COURSE_CAPACITY_MAX){
			cout << "�γ������޶���Ҫ�ں���Χ("<< Global::COURSE_CAPACITY_MIN <<"--"<< Global::COURSE_CAPACITY_MAX <<")"<<endl;
			cout << "�Ƿ����?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		break;
	}
	if('y' != comfirm && 'Y' != comfirm){
		return false;
	}
	
	while('y' == comfirm || 'Y' == comfirm){
		cout<<"���ұ��:";
		cin >> roomId;
		if(!isInputOk()){
			continue;
		}
		vector<Classroom>::iterator i;
		if(!Classroom::checkIdExist(roomId,i)){
			cout << "�ñ�Ų����ڣ�������ѡ��" << endl;
			cout << "�Ƿ����?Y/N" << endl;
			cin >> comfirm;
			continue;
		}else if(i->capacity < capacity){
			cout << "�ý��ҽ�������" << i->capacity << "��, ������ѡ��" << endl;
			cout << "�Ƿ����?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		break;
	}
	if('y' != comfirm && 'Y' != comfirm){
		return false;
	}

	it->courseId = id;
	it->courseName = name;
	it->teacherAccount = teacherAccount;
	it->roomId = roomId;
	it->capacity = capacity;
		
	cout << "�޸�����" << endl;
	printTitleToStream(cout);
	recordToStream(cout,it,true);
	return true;
}

