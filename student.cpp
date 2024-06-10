#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

#ifndef INCLUDE_RECORD_PROCESS
#include "recordProcess.h" 
#endif

#ifndef INCLUDE_COURSE
#include "course.h"
#endif

#ifndef INCLUDE_CONIO
#include <conio.h>
#define INCLUDE_CONIO
#endif

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif

#ifndef INCLUDE_SSTREAM
#include <sstream>
#define INCLUDE_SSTREAM
#endif

#ifndef INCLUDE_FSTREAM
#include <fstream>
#define INCLUDE_FSTREAM
#endif

#ifndef INCLUDE_SELECTION_TABLE
#include "selectionTable.h"
#endif

#ifndef INCLUDE_CLASSROOM
#include "classroom.h"
#endif

#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif 

#ifndef INCLUDE_ADMINISTATOR
#include "administrator.h"
#endif


vector<Student> Student::studentList;

//����ָ������ĳ�ʼ�� 
bool (*Student::stuFuncs[Global::STU_FUNC_MAX])() = {showSelectedCourse,Course::retrieve,selectCourse,withdrawCourse,payOrder};
//��ǰ��½ѧ���˺� 
string Student::login_account="";

bool Student::checkAccountExist(string account){
	vector<Student>::iterator i;
	for(i=studentList.begin();i!=studentList.end();++i){
		if(i->account == account){
			return true;
		}
	}
	return false;
}


//���ص���studentList�е�һ���������������˺ŵ��ڴ������account���� Student����ĵ�ַ��
Student* Student::getElementByAccount(string account){
	for(vector<Student>::iterator i=studentList.begin();i!=studentList.end();i++){
		if(i->account == account){
			return &(*i);
		}
	}
	return NULL;
}


bool Student::checkAccountExist(string account, vector<Student>::iterator &i){
	for(i=studentList.begin();i!=studentList.end();++i){
		if(i->account == account){
			return true;
		}
	}
	return false;
}

//ѧ�������������� 
void Student::process(){
	while(login(Global::STUDENT)){
		int stuFuncChoice = -1;
		while(Global::STU_FUNC_MAX != stuFuncChoice){
			clear();
			cout << "--------ѧ�����ܲ˵�---------" << endl;
			stuFuncChoice = getChoice("ѡ����:", Global::stuFuncStr, Global::STU_FUNC_MAX);
			if(Global::STU_FUNC_MAX != stuFuncChoice){
				//����ִ�в�����ֱ�����ش����˳� 
				stuFuncs[stuFuncChoice]();
			}
		}
	}
}


//����ѧ���˺� 
bool Student::createAccount(){
	string account,name,id,tel,password,comfirmPasswd;
	char comfirm='y';
	bool result=true;
	
	clear();
	cout << "------ע��ѧ���˺�-----" << endl;
	while('y' == comfirm || 'Y' == comfirm){
		while('y' == comfirm || 'Y' == comfirm){
			cout << "�������˺�����:" ;
			cin >> account;

			if(checkAccountExist(account)){
				cout << "�˺��Ѵ���!����������"  << endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}
			break;
		}
		if('y' != comfirm && 'Y' != comfirm){
			result=false;
			break;
		}
	
		cout << "������������" ;
		cin >> name;
	
		while('y' == comfirm || 'Y' == comfirm){
			cout << "���������֤�ţ�" ;
			cin >> id;
			if(Global::ID_LENGTH != id.length()){
				cout << "���֤�ų��ȷǷ�!����������"  << endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}
			break;
		}
		if('y' != comfirm && 'Y' != comfirm){
			result=false;
			break;
		}
		
		while('y' == comfirm || 'Y' == comfirm){
			cout << "�������ֻ���:";
			cin >> tel;
			if(Global::TEL_LENGTH != tel.length()){
				cout << "�ֻ��ų��ȷǷ�!����������"  << endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}
			break;
		}
		if('y' != comfirm && 'Y' != comfirm){
			result=false;
			break;
		}
		
		password = setPassword();	
		
		Student s = Student(account,id,name,tel,password);//�½�һ��ѧ������ 
		
		cout << "����������������" << endl;
		printTitleToStream(cout);
		s.recordToStream(cout);
		cout << "�Ƿ�ȷ������?Y/N" << endl;
		cin >> comfirm;
		if('y' == comfirm || 'Y' == comfirm){	
			studentList.push_back(s);
			cout << "��������������" << endl;
			recordToStream(cout, studentList.end() - 1,true);
			Student::login_account =  account;
		}else{
			cout <<"��ȡ������"<<endl;
			result = false;
		}
		break; 
	}
	goPrevious();
	return result;
}

bool Student::recordToStream(ostream& out, vector<Student>::iterator firstRecord, bool onlyOne){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	
	printTitleToStream(out);
	for(vector<Student>::iterator i=studentList.begin();i!=studentList.end();i++){
		if(onlyOne){
			i = firstRecord;
		}
		out <<  setw(Global::PRINT_LONG_WIDTH)<<i->account << setw(Global::PRINT_LONG_WIDTH) <<	i->name << setw(Global::PRINT_LONG_WIDTH) <<	i->idCardNumber << setw(Global::PRINT_LONG_WIDTH) <<	i->telphone << setw(Global::PRINT_LONG_WIDTH)  << i->password << endl;
		if(onlyOne){
			break;
		}
	}
	return true;
} 

bool Student::printTitleToStream(ostream& out){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_LONG_WIDTH)<<"�˺�" << setw(Global::PRINT_LONG_WIDTH) << "����" << setw(Global::PRINT_LONG_WIDTH) << "���֤��" << setw(Global::PRINT_LONG_WIDTH) << "�ֻ���" << setw(Global::PRINT_LONG_WIDTH) << "����"<< endl;
	return true;
}
bool Student::recordToStream(ostream& out){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	
	out <<  setw(Global::PRINT_LONG_WIDTH)<< account << setw(Global::PRINT_LONG_WIDTH) << name << setw(Global::PRINT_LONG_WIDTH) << idCardNumber << setw(Global::PRINT_LONG_WIDTH) << telphone << setw(Global::PRINT_LONG_WIDTH)  << password << endl;

	return true;
} 


//ѡ��˵�  idList��һ���γ�id������ , selectList ��ѡ���, courseTotal �ǿ�ѡ������, isInclusion��ʾ�ǰ���idList�еĿγ̣��������� 
bool Student::getSelection(const vector<int>& idList, int* selectList, const int& courseTotal,bool isInclusion){
		
	static bool firstPrint = true;
	int currentLine = 0;
	int line = 0;
	vector<Course>::iterator i;
	int selectTotal = 0;
	
	while (true) {
        if (_kbhit()|| firstPrint) {

	
        	clear();
        	//����͹���˵�� 
			cout << "----------------ѧ��ѡ��----------------" << endl;
			
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
					priceTotal += i->price;
					cout << i->courseName << " ";
				} 
				line++;
			}
			
			cout << ")" << endl;
			cout << "�γ��ܼ۸�:" <<  fixed << setprecision(2)<< priceTotal  << endl;

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

/*----------------------ѧ��ѡ��-------------------------*/
bool Student::selectCourse(){
	int *selectList;//��ѡ��Ŀγ��б�, ���ѡ����Ϊ1 
	int courseTotal;//��ѡ�γ�������
	int line=0;//���±� 
	vector<Course>::iterator i;//�γ̱��������� 
    
    //��ʼ�� 
	vector<int> paidList = CourseSelectionTable::paidOrder.getCourseByStudent(Student::login_account);//��֧���Ŀγ��б�
	vector<int> unpaidList = CourseSelectionTable::unpaidOrder.getCourseByStudent(Student::login_account);//���˿γ��б�
	vector<int> exclusionList;//��Ҫ��������Ŀ=��֧��+���� 
	exclusionList.insert(exclusionList.end(),paidList.begin(),paidList.end());
	exclusionList.insert(exclusionList.end(),unpaidList.begin(),unpaidList.end());
	 
	courseTotal = Course::courseList.size() - exclusionList.size();//��ѡ�γ�������
	
	if(0 == courseTotal){
		clear();
		cout << "���޿�ѡ�γ�" << endl;
		goPrevious(); 
		return true;
	}

	selectList = new int[courseTotal];
    for(int i=0;i<courseTotal;i++){
    	selectList[i] = 0;
	}
	

	
	if(!getSelection(exclusionList,selectList,courseTotal,false)){
		free(selectList);
		return false;
	}
	
	if(checkAllZero(selectList,courseTotal)){
		cout << "��δ��ѡ��" << endl;
		goPrevious();
		return false;
	}
    
    //ȷ��ѡ�ν�����붩�� 
    cout << "���¿γ��Ѽ��붩��,�뼰ʱ��֧��ҳ���и���"  << endl;
    Course::printTitleToStream(cout);
    for(i=Course::courseList.begin(),line=0;i!=Course::courseList.end();i++){
    	//�������в���ѡ�Ŀγ� 
		if(checkExist(exclusionList,i->courseId)){
			continue;
		}
		if(1 == selectList[line]){
			Course::recordToStream(cout,i,true);
			CourseSelectionTable::unpaidOrder.addEntry(i->courseId,Student::login_account);
		}
    	line++;
	}

    free(selectList);
	goPrevious(); 
	return true;
}

//�˿� 
bool Student::withdrawCourse(){
	int *selectList;//��ѡ��Ŀγ��б�, ���ѡ����Ϊ1 
	int courseTotal;//��ѡ�γ�������
	int line=0;//���±� 
	vector<Course>::iterator i;//�γ̱��������� 
    
    //��ʼ�� 
    vector<int> unpaidList = CourseSelectionTable::unpaidOrder.getCourseByStudent(Student::login_account);//���˿γ��б�
	courseTotal = unpaidList.size();//���˿γ�������

	if(0 == courseTotal){
		clear();
		cout << "���޿��˿γ�" << endl;
		goPrevious(); 
		return true;
	}

	selectList = new int[courseTotal];
    for(int i=0;i<courseTotal;i++){
    	selectList[i] = 0;
	}
	
	if(!getSelection(unpaidList,selectList,courseTotal)){
		free(selectList);
		return false;
	}
    
    
    //ȷ��ѡ�ν�����붩�� 
    cout << "���¿γ�(δ�ɷ�)�Ѽ����˿ε�"  << endl;
    Course::printTitleToStream(cout);
    for(i=Course::courseList.begin(),line=0;i!=Course::courseList.end();i++){
    	//���������˵Ŀγ� 
		if(!checkExist(unpaidList,i->courseId)){
			continue;
		}
		if(1 == selectList[line]){
			Course::recordToStream(cout,i,true);
			CourseSelectionTable::unpaidOrder.deleteEntry(i->courseId,Student::login_account);
		}
    	line++;
	}

    free(selectList);
	goPrevious(); 
	return true;
}


//�鿴��ѡ�γ� 
bool Student::showSelectedCourse(){
	
	vector<Course>::iterator i;//�γ̱��������� 
    
    //��ʼ�� 
    vector<int> unpaidList = CourseSelectionTable::unpaidOrder.getCourseByStudent(Student::login_account);//���˿γ��б�
    vector<int> paidList = CourseSelectionTable::paidOrder.getCourseByStudent(Student::login_account);//���˿γ��б�

    clear();
    //ȷ��ѡ�ν�����붩�� 
    cout << "---------------��ѡ�γ�-----------------"  << endl;
   	cout << setw(Global::PRINT_WIDTH)<<"�γ̱��" << setw(Global::PRINT_LONG_WIDTH)<<"�γ�����"  << setw(Global::PRINT_WIDTH)<<"����"  << setw(Global::PRINT_WIDTH)<<"�ڿν�ʦ" << setw(Global::PRINT_WIDTH)<<"�Ͽ�����" <<setw(Global::PRINT_WIDTH)<< "�ɷ����"<<endl;

    for(i=Course::courseList.begin();i!=Course::courseList.end();i++){
    	if(checkExist(paidList,i->courseId) || checkExist(unpaidList,i->courseId)){
    		string roomName,teacherName;
    		
    		Classroom* room = Classroom::getElementById(i->roomId);
    		Teacher* teacher = Teacher::getElementByAccount(i->teacherAccount);
    		if(!room || !teacher){
    			cerr << "����/��ʦ��Ų�����" << endl;
			}
    		cout << setw(Global::PRINT_WIDTH)<<i->courseId <<setw(Global::PRINT_LONG_WIDTH)<< i->courseName << setw(Global::PRINT_WIDTH)<<room->roomName << setw(Global::PRINT_WIDTH)<<teacher->name << setw(Global::PRINT_WIDTH)<<i->studentNumber << setw(Global::PRINT_WIDTH)<<(checkExist(unpaidList,i->courseId)?"δ�ɷ�":"�ѽɷ�" )<< endl;
		}
	}

	goPrevious(); 
	return true;
}

//֧���γ̷��� 
bool Student::payOrder(){
	int courseTotal = 0;//�γ�������
	float priceTotal = 0;//�ܼ� 
	vector<Course>::iterator i;//�γ̱��������� 
	char comfirm = 'y';
	bool result = true;
    
    //��ʼ�� 
    vector<int> unpaidList = CourseSelectionTable::unpaidOrder.getCourseByStudent(Student::login_account);//���˿γ��б�
    
    clear();
    cout << "---------------ѡ�η��ý���-----------------"  << endl;
    
    //δѡ����� 
    if(unpaidList.size() == 0){
    	cout << "��û�д�֧���Ŀγ�"<<endl;
    	goPrevious(); 
		return result;
	}
	
	//�о�ѡ��δ֧���γ� 
    cout << "��ѡ�������¿γ�:" << endl;
    Course::printTitleToStream(cout);
   	for(i=Course::courseList.begin();i!=Course::courseList.end();i++){
   		if(checkExist(unpaidList,i->courseId)){
   			courseTotal++;
   			priceTotal += i->price;
   			Course::recordToStream(cout,i,true);
		}	
	} 
	
	//�����ڶ�Ӧ�γ������м�1��,ע���������޶�,���ʧ������ʾĳ�ſγ������ﵽ����,�����˿κ���֧�� 
	for(vector<int>::iterator i=unpaidList.begin();i!=unpaidList.end();i++){
		Course* course = Course::getElementById(*i);
		if(course){
			if(course->studentNumber+1>course->capacity){
				cout << "�γ�" << course->courseName << "������޷�ѡ�Σ������˿κ�������֧��" << endl;
				result = false;
			}
		}else{
			cerr<<"���Ϊ"<<*i<<"�Ŀγ̲�����"<<endl;
			result = false;
		}
	}
		
	cout << "��" << courseTotal << "��, �ϼ�" << fixed << setprecision(2) << priceTotal << "Ԫ" << endl;
	cout << "����ѧУ�������п��˻�ת��" <<  fixed << setprecision(2) << priceTotal << "Ԫ" << endl;
	cout << "�������п��˻�16λ����:" << Administrator::bankAccount << endl;
	cout << "ע�⣺֧���󣬱�����Ϣ������ϵͳ�����޷��˿Σ�" << endl;
	cout << "�Ƿ����?Y/N" << endl;
	cin >> comfirm;
	if(comfirm == 'y' || comfirm == 'Y'){
		
		//���ǰ��ִ��ʧ��,��ִ�к�������� 
		if(result){

			//��ѧ����Ϣ¼�뵽paidList
			for(vector<int>::iterator i=unpaidList.begin();i!=unpaidList.end();i++){
				if(!CourseSelectionTable::paidOrder.addEntry(*i,Student::login_account)){
					result=false;
				}
			}

			//���unpaidList
			for(vector<int>::iterator i=unpaidList.begin();i!=unpaidList.end();i++){
				if(!CourseSelectionTable::unpaidOrder.deleteEntry(*i,Student::login_account)){
					result=false;
				}
			}
					
			//��γ���������
			for(vector<int>::iterator i=unpaidList.begin();i!=unpaidList.end();i++){
				Course* course = Course::getElementById(*i);
				course->studentNumber += 1;
			} 
		}
		else{
			result = false;
		}
	}else{
		cout << "��ȡ��֧��" << endl;
	}
	
	//����ҳ�� 
	if(result){
		cout << "֧���ɹ���ѡ����Ϣ��¼��ϵͳ���޷�����" << endl;
		CourseSelectionTable::storeInfo();
	}else{
		cout << "��Ϣ¼�����,��ȡ��֧��" << endl;
	}
	goPrevious(); 
	return result;
}


const char* Student::dataFile = "studentsInfo.txt"; 

bool Student::storeInfo(){
	bool result = true;
	ofstream out;
	
	//д��ǰ�����ļ�����Ϊ��ͨ 
	SetFileAttributes(dataFile, FILE_ATTRIBUTE_NORMAL);
	
	//���ع���Ա�˺�����
	out.open(dataFile,ios::out);
	if(!Student::recordToStream(out,Student::studentList.begin())){
		result= false;
	}

	out.close();
		
	//д��������ļ�����Ϊֻ��,��ֹ�����޸� 
	SetFileAttributes(dataFile, FILE_ATTRIBUTE_READONLY);
	
	return result;
}

bool Student::loadInfo(){
	ifstream in;
	string temp;
	
	//���ع���Ա�˺�����
	in.open(dataFile,ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		string account,name,id,tel,password;
		
		stringstream ss(temp);
		ss >> account;
		ss >> name;
		ss >> id;
		ss >> tel;
		ss >> password;
		
		Student s = Student(account,id,name,tel,password);
		Student::studentList.push_back(s);
	}
	in.close();
}

