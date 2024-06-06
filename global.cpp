#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif


#ifndef INCLUDE_VECTOR
#include <vector>
#define INCLUDE_VECTOR
#endif

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

#ifndef INCLUDE_ADMINISTATOR
#include "administrator.h"
#endif

int Global::LOGIN_RETRY_MAX=5;
int Global::PRINT_WIDTH=12;
int Global::PRINT_LONG_WIDTH=24;

int Global::TEACHER_NUMBER_MAX=100;
int Global::ROOM_NUMBER_MAX=100;
int Global::COURSE_NUMBER_MAX=100;
int Global::COURSE_PRICE_MAX=3000;
int Global::COURSE_CAPACITY_MAX=200;
int Global::COURSE_CAPACITY_MIN=20;
int Global::ID_LENGTH=18;
int Global::TEL_LENGTH=11;

const char *Global::roleStr[]={"����Ա","ѧ��","��ʦ","�˳�"};
const char *Global::loginStr[]={"��½","������һ��"};
const char *Global::stuLoginStr[]={"ע��","��½","������һ��"};
const char *Global::operationStr[]={"����","ɾ��","�޸�","��ѯ","������һ��"};
const char *Global::mgmtStr[]={"�����ʦ��Ϣ","���������Ϣ","����γ���Ϣ","������һ��"};
const char *Global::stuFuncStr[]={"�鿴��ѡ�γ�","�鿴���пγ�","ѡ���¿γ�","��ѡδ֧���Ŀγ�","֧������","������һ��"};
const char *Global::titleStr="��ѵ���Ĺ���ϵͳ";
const char *Global::teacherFuncStr[] = {"�鿴���¿γ�", "�鿴�γ�ѧ������","������һ��"}; 

//��տ���̨
void clear(){
	system("cls");
}

//���ÿ���̨���� 
void setTitle() {
	SetConsoleTitle(Global::titleStr);
}

//���ÿ���̨��ɫ 
void setConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

//ͳһ�Ļ�ӭ����,��ȡ�û���� 
Global::Role greeting(){
	int role = -1;
	clear(); 
	cout << "-----���˵�-----"<< endl;
	cout << "��ӭʹ��" << Global::titleStr << endl;

	role = getChoice("��������ǣ�",Global::roleStr,Global::ROLE_MAX);
	return (Global::Role)role;
}

//������һ�� 
void goPrevious(){
	cout << "�������������һ��" << endl;
	cin.ignore();
	getchar();
} 

//��������Ƿ�Ϲ� 
bool isInputOk(){
	//�������������ʱ����������α���int����������char���͵��ַ�����ʱfailbit��ֵ����0��Ϊ1
	if(cin.fail()){
		//������ַ��Ῠ�����뻺�������º����޷������������
		cout << "������Ϸ��ַ�!" << endl;
		
		//��������ʹ��cin>>clear()��falibit��Ϊ0����������������������Ȼ��ʹignore()ȡ�����������ַ�������һ�ε���������������С�
		cin.clear();
		cin.ignore();
		return false;
	}
	return true;
}

//��ȡ�û������ѡ�� 
int getChoice(const char* promptStr, const char **choiceStr, const int choiceMax){
	int choice = -1;
	//��choiceMax���û�����ѡ���˳�/���ص���һ�� 
	while(choice > choiceMax || choice < 0){
		choice = -1;
		cout << promptStr <<endl;
		for(int i=0;i<=choiceMax;i++){
			cout << i << ". " << choiceStr[i] << endl;
		}
		cin >> choice;
		
		if(!isInputOk()){
			choice = -1;
		}
	}
	
	return choice;
}

//�������� 
string setPassword() {
    string password, comfirmPasswd;
    do {
        cout << "���������룺";
        cin >> password;

        cout << "���ٴ�������ȷ�����룺";
        cin >> comfirmPasswd;

        if (password != comfirmPasswd) {
            cout << "�������벻һ�£����������룡" << endl;
        }
    } while (password != comfirmPasswd);
    return password;
}

//��½
bool login(Global::Role role){
	string inputAccount;
	string inputPasswd;
	vector<Student>::iterator is;
	vector<Teacher>::iterator it;
	int loginChoice = -1;
	
	clear();
	cout << "------"<< Global::roleStr[role] <<"��½-----" << endl;
	if(Global::STUDENT == role){
		loginChoice = getChoice("", Global::stuLoginStr, Global::STU_LOGIN_MAX);
		if(Global::STU_LOGIN_MAX == loginChoice){
			return false;
		}else if(Global::STU_SIGNUP == loginChoice){
			Student::createAccount();
			return true;
		}
	}else{
		loginChoice = getChoice("", Global::loginStr, Global::LOGIN_MAX);
		if(Global::LOGIN_MAX == loginChoice){
			return false;
		}
	}
	
	for(int i=0;i<Global::LOGIN_RETRY_MAX;i++){
		cout << "�������˺�����:" ;
		cin >> inputAccount;		
		
		if(Global::ADMINISTRATOR == role){	
			if(inputAccount != Administrator::adminAccount){
				cout << "�˺Ų�����!����������"  << endl;
				continue;
			}
		}else if(Global::TEACHER == role){
			if(!Teacher::checkAccountExist(inputAccount,it)){
				cout << "�˺Ų�����!����������"  << endl;
				continue;
			}
			
		}else{
			if(!Student::checkAccountExist(inputAccount,is)){
				cout << "�˺Ų�����!����������"  << endl;
				continue;
			}
		}

		cout << "����������:" ;
		cin >> inputPasswd;
		
		if(Global::ADMINISTRATOR == role){	
			if(inputPasswd != Administrator::password){
			
				cout << "�������!����������"  << endl;
				continue;
			}
		}else if(Global::TEACHER == role){
			if(inputPasswd != it->password){
				cout << "�������!����������"  << endl;
				continue;
			}
			//��ǰ��½�˺� 
			Teacher::login_account = inputAccount;
		}else{
			if(inputPasswd != is->password){
				cout << "�������!����������"  << endl;
				continue;
			}
			Student::login_account =  inputAccount;
		}
		
		cout << "��½�ɹ�" << endl;
		return true;
	}
	
	cout << "��½��������" << Global::LOGIN_RETRY_MAX << endl; 
	cout << "���˳�" << endl;
	return false;
}

 
