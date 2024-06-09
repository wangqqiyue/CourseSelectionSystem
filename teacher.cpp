#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_COURSE
#include "course.h"
#endif

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif


#ifndef INCLUDE_FSTREAM
#include <fstream>
#define INCLUDE_FSTREAM
#endif


#ifndef INCLUDE_SSTREAM
#include <sstream>
#define INCLUDE_SSTREAM
#endif

#ifndef INCLUDE_SELECTION_TABLE
#include "selectionTable.h"
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

vector<Teacher> teacherList;

//����ָ������ĳ�ʼ�� 
bool (*Teacher::teacherFuncs[Global::TEACHER_FUNC_MAX])() = {Teacher::showTeacherCourse,Teacher::showRoster};
string Teacher::login_account = "";//��ǰ��½�˺� 


const char* Teacher::dataFile = "teachersInfo.txt"; 

bool Teacher::storeInfo(){
	bool result = true;
	ofstream out;
	//д��ǰ�����ļ�����Ϊ��ͨ 
	SetFileAttributes(dataFile, FILE_ATTRIBUTE_NORMAL);
	
	//���ع���Ա�˺�����
	out.open(dataFile,ios::out);
	if(!Teacher::recordToStream(out, teacherList.begin())){
		result= false;
	}

	out.close();
	
	//д��������ļ�����Ϊֻ��,��ֹ�����޸� 
	SetFileAttributes(dataFile, FILE_ATTRIBUTE_READONLY);
	return result;
}

bool Teacher::loadInfo(){
	ifstream in;
	string temp;

	//���ع���Ա�˺�����
	in.open(dataFile,ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		string teacherAccount,teacherName,teacherPassword;
		stringstream ss(temp);
		ss >> teacherAccount;
		ss >> teacherName;
		ss >> teacherPassword;
		Teacher t(teacherAccount,teacherName,teacherPassword);
		teacherList.push_back(t);
	}
	in.close();
}


//��ʦ������������ 
void Teacher::process(){
	while(login(Global::TEACHER)){
		int funcChoice = -1;
		while(Global::TEACHER_FUNC_MAX != funcChoice){
			clear();
			cout << "--------��ʦ���ܲ˵�---------" << endl;
			funcChoice = getChoice("ѡ����:", Global::teacherFuncStr, Global::TEACHER_FUNC_MAX);
			if(Global::TEACHER_FUNC_MAX != funcChoice){
				//����ִ�в�����ֱ�����ش����˳� 
				teacherFuncs[funcChoice]();
			}
		}

	}
}


bool Teacher::checkAccountExist(string account){
	for(vector<Teacher>::iterator  i=teacherList.begin();i!=teacherList.end();++i){
		if(i->account == account){
			return true;
		}
	}
	return false;
}

bool Teacher::checkAccountExist(string account, vector<Teacher>::iterator &i){
	for(i=teacherList.begin();i!=teacherList.end();++i){
		if(i->account == account){
			return true;
		}
	}
	return false;
}

bool Teacher::printTitleToStream(ostream& out){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	out << setw(Global::PRINT_WIDTH)<<"��ʦ�ʺ�" << setw(Global::PRINT_LONG_WIDTH) << "��ʦ����" << setw(Global::PRINT_LONG_WIDTH) << "����"<< endl;
	return true;
}

bool Teacher::recordToStream(ostream& out, vector<Teacher>::iterator firstRecord, bool onlyOne){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	
	if(!onlyOne){
		printTitleToStream(out);	
	}	
	
	for(vector<Teacher>::iterator i=teacherList.begin();i!=teacherList.end();i++){
		if(onlyOne){
			i=firstRecord;
		}
		out <<  setw(Global::PRINT_WIDTH)<<i->account << setw(Global::PRINT_LONG_WIDTH) <<	i->name << setw(Global::PRINT_LONG_WIDTH)  << i->password << endl;
		if(onlyOne){
			break;
		}
	}
	return true;
} 

bool Teacher::recordToStream(ostream& out, bool onlyOne){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}

	out <<  setw(Global::PRINT_WIDTH)<<account << setw(Global::PRINT_LONG_WIDTH) <<	name << setw(Global::PRINT_LONG_WIDTH)  << password << endl;

	return true;
} 

//���ݽ�ʦ�˺ŷ��ؽ�ʦԪ�ص�ָ�� 
Teacher* Teacher::getElementByAccount(string account){
		for(vector<Teacher>::iterator i=teacherList.begin();i!=teacherList.end();i++){
		if(i->account == account){
			return const_cast<Teacher*>(&(*i));
		}
	}
}

//��ӡ��ǰ��ʦ���µĿγ� 
bool Teacher::showTeacherCourse(){
	bool result = true;

	clear();
	cout <<"-------------�����µĿγ� -------------------------" << endl;
	Teacher *teacher=getElementByAccount(login_account);
	if(!teacher){
		cerr<<"�˺�Ϊ" << login_account << "�Ľ�ʦ������" << endl;
		result = false;
	}
	
	cout << setw(Global::PRINT_LONG_WIDTH) << "�γ���" << setw(Global::PRINT_WIDTH) << "ѡ������" << setw(Global::PRINT_LONG_WIDTH) << "����" << endl;
	for(vector<Course>::iterator i=Course::courseList.begin();i!=Course::courseList.end();i++){
		Classroom* room;
		if(i->teacherAccount == login_account){
			room = Classroom::getElementById(i->roomId);
			if(!room){
				cerr << "���Ϊ" << i->roomId << "�Ľ��Ҳ�����" << endl;
				result = false;
			}
			cout << setw(Global::PRINT_LONG_WIDTH) << i->courseName <<  setw(Global::PRINT_WIDTH) << i->studentNumber <<  setw(Global::PRINT_LONG_WIDTH) << room->roomName << endl;
		}
	}
	goPrevious();
	return result;
}

//��ӡѧ��������
bool Teacher::showRoster(){
	bool result = true;

	clear();
	cout <<"-------------�����µĿγ̵�ѧ�������� -------------------------" << endl;
	
	Teacher *teacher=getElementByAccount(login_account);
	if(!teacher){
		cerr<<"�˺�Ϊ" << login_account << "�Ľ�ʦ������" << endl;
		result = false;
	}
	
	cout << setw(Global::PRINT_LONG_WIDTH) << "�γ���" << setw(Global::PRINT_WIDTH) << "ѡ������" << setw(Global::PRINT_LONG_WIDTH) << "����" << endl;
	for(vector<Course>::iterator i=Course::courseList.begin();i!=Course::courseList.end();i++){
		Classroom* room;
		if(i->teacherAccount == login_account){
			room = Classroom::getElementById(i->roomId);
			if(!room){
				cerr << "���Ϊ" << i->roomId << "�Ľ��Ҳ�����" << endl;
				result = false;
			}
			cout << setw(Global::PRINT_LONG_WIDTH) << i->courseName <<  setw(Global::PRINT_WIDTH) << i->studentNumber <<  setw(Global::PRINT_LONG_WIDTH) << room->roomName << endl;
			if(0 == i->studentNumber){
				cout << "����ѧ��ѡ���ſγ�" << endl;
				continue;
			}
			
			cout <<"-------������-----" << endl;
			vector<string> studentList = CourseSelectionTable::paidOrder.getStudentByCourse(i->courseId);
			int  rosterNumber = 1;//��������� 
			for(vector<string>::iterator j=studentList.begin();j!=studentList.end();j++,rosterNumber++){
				Student* student = Student::getElementByAccount(*j);\
				if(!student){
					cerr << "�˺�Ϊ" << *j <<"��ѧ��������" << endl;
					result = false;
				}
				cout << rosterNumber << ". " << student->name << endl;
			}
			cout << endl;
		}
	}
	goPrevious();
	return result;
} 


//��ѯ��ʦ��Ϣ 
bool Teacher::retrieve(){
	clear();
	cout << "------��ʦ��Ϣ��ѯ-----"	<< endl;
	recordToStream(cout, teacherList.begin());
	goPrevious(); 
	return true;
	
}

/*������ʦ���� 
��Ҫ�ж����������Ƿ����ظ�,�����󲻳�����ʦ�������� 
*/
bool Teacher::create(){
	string account,name,passwd;
	char comfirm = 'y';
	clear();
	cout << "------������ʦ��Ϣ-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(teacherList.size() >= Global::TEACHER_NUMBER_MAX){
			cout << "��ʦ�����Ѵ�����("<< Global::TEACHER_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "��������Ϣ" << endl;
		cout<<"��ʦ�˺�:";
		cin >> account;

		if(Teacher::checkAccountExist(account)){
			cout << "���˺��Ѵ���" << endl; 
			cout << "�Ƿ����?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "��ʦ����:" ;
		cin >> name;
		
		passwd=setPassword();
		
		Teacher t(account,name,passwd);//�½�һ����ʦ���� 
		
		cout << "����������������" << endl;
		printTitleToStream(cout);
		t.recordToStream(cout);
		cout << "�Ƿ�ȷ������?Y/N" << endl;
		cin >> comfirm;
		if('y' == comfirm || 'Y' == comfirm){	
			teacherList.push_back(t);
			cout << "��������������" << endl;
			Teacher::recordToStream(cout, teacherList.end()-1, true);
		}else{
			cout <<"��ȡ������"<<endl;
		}
		
		cout << "�Ƿ����?Y/N" << endl;
		cin >> comfirm;
	}
	
	goPrevious();
	return true;
	
}
        


//ѡ��˵�  idList��һ���γ�id������ , selectList ��ѡ���, teacherTotal �ǿ�ѡ������, isInclusion��ʾ�ǰ���idList�еĿγ̣��������� 
bool Teacher::getSelection(const string prompt, const vector<string>& idList, int* selectList, const int& teacherTotal,bool isInclusion,bool onlyOne){
		
	static bool firstPrint = true;
	int currentLine = 0;
	int line = 0;
	vector<Teacher>::iterator i;
	int selectTotal = 0;
	
	while (true) {
        if (_kbhit()|| firstPrint) {

	
        	clear();
        	//����͹���˵�� 
			cout << "----------------"<< prompt <<"----------------" << endl;
			
			//��ʾ��ǰ״̬ 
			float priceTotal = 0;
			cout << "ѡ��״̬" << endl;
			cout << "��ѡ��ʦ����:" << selectTotal << "(";

            for(i=teacherList.begin(),line=0;i!=teacherList.end();i++){
            	
            	if(isInclusion){//������idList�����Ŀ 
            		if(!checkExist(idList,i->account)){
						continue;
					}
				}else{//����idList�����Ŀ 
					if(checkExist(idList,i->account)){
						continue;
					}
				}
				
				if(1 == selectList[line]){
					cout << i->name << " ";
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
	                    currentLine += teacherTotal;
	                }
					
	            } else if (ch == 80) { // �¼�ͷ��
	                currentLine++;
	                currentLine%=teacherTotal;
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

			printTitleToStream(cout);
			//�������пγ��� 
            for(i=teacherList.begin(),line=0,selectTotal=0;i!=teacherList.end();i++){
            	            	
            	if(isInclusion){//������idList�����Ŀ 
            		if(!checkExist(idList,i->account)){
						continue;
					}
				}else{//����idList�����Ŀ 
					if(checkExist(idList,i->account)){
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

bool Teacher::del(){
	int *selectList;//��ѡ��Ŀγ��б�, ���ѡ����Ϊ1 
	int teacherTotal;//��ѡ�γ�������
	int line=0;//���±� 
	vector<Course>::iterator i;//�γ̱��������� 
    
    //��ʼ�� 
    vector<string> undeletableList;//����ɾ�γ��б�
    for(i=Course::courseList.begin();i!=Course::courseList.end();i++){
    	//����γ�������Ϊ0���Ҹ���ʦδ���뵽����ɾ���б������ 
    	if(0 != i->studentNumber){
    		if(!checkExist(undeletableList,i->teacherAccount)){
    			undeletableList.push_back(i->teacherAccount);
			}
		}
	}
    
	teacherTotal = teacherList.size() - undeletableList.size();//��ɾ�����ҵ�������
	if(0 == teacherTotal){
		clear();
		cout << "Ŀǰû�п���ɾ���Ľ�ʦ�˺�" << endl;
		goPrevious(); 
		return false;
	}

	selectList = new int[teacherTotal];
    for(int i=0;i<teacherTotal;i++){
    	selectList[i] = 0;
	}
	
	if(!getSelection("ɾ���޿γ�����Ľ�ʦ�˺�", undeletableList,selectList,teacherTotal,false)){
		free(selectList);
		return false;
	}
	
	
	if(checkAllZero(selectList,teacherTotal)){
		cout << "��δ��ѡ��" << endl;
		goPrevious();
		return false;
	}
	
    //ȷ��ѡ�ν����ɾ�� 
    cout << "���½�ʦ�˺���ɾ��"  << endl;
    printTitleToStream(cout);
    vector<Teacher>::iterator it;
    for(it=teacherList.begin(),line=0;it!=teacherList.end();it++){
    	//��������ɾ�Ľ�ʦ 
		if(checkExist(undeletableList,it->account)){
			continue;
		}
		if(1 == selectList[line]){
			recordToStream(cout,it,true);
			it = teacherList.erase(it);// erase֮���ǰ������ָ�����̡����������ʧЧ,�ᱨ��
			it--;
		}
    	line++;
	}

    free(selectList);
	goPrevious(); 
	return true;
}
 
bool Teacher::update(){
	int *selectList;//��ѡ��Ŀγ��б�, ���ѡ����Ϊ1 
	int teacherTotal;//��ѡ�γ�������
	int line=0;//���±� 

	vector<string> idList;
	vector<string> unchangableAccounts;
	for(vector<Teacher>::iterator i=teacherList.begin();i!=teacherList.end();i++){
		idList.push_back(i->account);
	}
	
	for(vector<Course>::iterator i=Course::courseList.begin();i!=Course::courseList.end();i++){
		if(0 != i->studentNumber){
			unchangableAccounts.push_back(i->teacherAccount);
		}
	}
	
	teacherTotal = teacherList.size();//���޸ĵ�������
	if(0 == teacherTotal){
		clear();
		cout << "Ŀǰû�п����޸ĵĽ�ʦ�˺�" << endl;
		goPrevious(); 
		return false;
	}

	selectList = new int[teacherTotal];
    for(int i=0;i<teacherTotal;i++){
    	selectList[i] = 0;
	}
	
	if(!getSelection("�޸Ľ�ʦ�˺�", idList,selectList,teacherTotal,true,true)){
		free(selectList);
		return false;
	}

	if(checkAllZero(selectList,teacherTotal)){
		cout << "��δ��ѡ��" << endl;
		goPrevious();
		return false;
	}
	
    //ȷ��ѡ�ν����ɾ�� 
    cout << "���½�ʦ�˺Ŵ��޸�"  << endl;
    printTitleToStream(cout);
    vector<Teacher>::iterator it;
    for(it=teacherList.begin(),line=0;it!=teacherList.end();it++){

		if(1 == selectList[line]){
			recordToStream(cout,it,true);
			changeInfo(unchangableAccounts, it);
		}
    	line++;
	}

    free(selectList);
	goPrevious(); 
	return true;
}

bool Teacher::changeInfo(const vector<string>& unchangableAccounts,vector<Teacher>::iterator &it){
	string account,name,passwd;
	
	if(checkExist(unchangableAccounts,it->account)){
		cout << "�ý�ʦ���ڿ�,�޷��޸��˺�" << endl;
	}else{
		char comfirm = 'y';
		while(comfirm == 'y' || 'Y' == comfirm){
			cout << "�������ʦ�˺�:";
			cin >> account;
			if(Teacher::checkAccountExist(account)){
				cout << "�˺��Ѵ���" << endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}
			it->account = account;
			break;
		}
	}
	
	cout << "��ʦ����:" ;
	cin >> name;

	passwd = setPassword();
	
	it->name = name;
	it->password = passwd;
	
	cout << "�޸�����" << endl;
	printTitleToStream(cout);
	recordToStream(cout,it,true);
}
