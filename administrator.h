#ifndef INCLUDE_ADMINISTATOR
#define INCLUDE_ADMINISTATOR

#ifndef INCLUDE_ROLE
#include "role.h"
#endif

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif


#ifndef INCLUDE_MAP
#include<map>
#define INCLUDE_MAP
#endif

//����Ա ���˺ź����� 
/*
���ܣ�¼��γ���Ϣ��������Ϣ 
		�����ʦ�˺����� 
		---------------------�����Ǹ߼����� 
		��ѯͳ�ƿγ���Ϣ 
		��ѯÿ����ʦ���¿γ̵�ѡ�����
		��ѯÿ�����ҵ��Ͽ���Ϣ
		��ѯѧ����ѡ������ͽɷ���Ϣ
		--------------------���������㹦��
		ɾ������ѡ�εĿγ�
		�޸Ŀγ����ƺͽ���
		���ſγ��Ƽ�
		�������ɾ���޸Ĺ������ݾ����ļ���ʽ���棬ϵͳ�������ܸ����޸ĺ��������ɸ��ֹ��� 
*/ 

//����: ���ұ��-�������� �� 1101-��һ��ѧ¥101�� 
typedef pair<int,string> Classroom;

//management ����ö�� 
enum MGMT{
	TEACHER_MGMT=0,
	CLASSROOM_MGMT,
	COURSE_MGMT,
	MGMT_MAX,
};

//�������ַ��� 
const char *mgmtStr[]={"�����ʦ��Ϣ","���������Ϣ","����γ���Ϣ","������һ��"};

bool teacherInfoRetrieve(){
	clear();
	cout << "------��ʦ��Ϣ��ѯ-----"	<< endl;
	cout << setw(PRINT_WIDTH)<<"��ʦ���" << setw(PRINT_LONG_WIDTH) << "��ʦ����" << setw(PRINT_LONG_WIDTH) << "����"<< endl;
	for(vector<Teacher>::iterator i=g_teacherList.begin();i!=g_teacherList.end();i++){
		cout <<  setw(PRINT_WIDTH)<<i->teacherId << setw(PRINT_LONG_WIDTH) <<	i->name << setw(PRINT_LONG_WIDTH)  << i->password << endl;
	}
	cout << "�������������һ��" << endl;
	cin.ignore();
	getchar();
	return true;
	
}

bool teacherMgmt(){
	int opChoice = -1;
	while(OP_MAX != opChoice){
		opChoice = -1; 
		clear();
		cout << "------��ʦ��Ϣ����-----"  << endl;
		opChoice = getChoice("ѡ�����:", operationStr, OP_MAX);
		if(RETRIEVE == opChoice){
			return teacherInfoRetrieve();
		}	
	}
	return false;
}


//todo ���ƹ����� 
bool classroomMgmt(){return false;}
bool courseMgmt(){return false;}

class Administrator{
private:
	bool hasAccount=false;
	bool hasLoaded=false;
	map<int,string> rooms; //���� 
	void createAdmin();
	bool login(); 
	bool (*mgmtFuncs[MGMT_MAX])();

	
public:
	Administrator();
	string adminAccount;//����Ա�˺� 
	string password;//����Ա����
	void loadAccount(string account,string password); 
	void process();

}; 

//����Ա���ܺ��������ʼ�� 
Administrator::Administrator(){
	mgmtFuncs[TEACHER_MGMT] = teacherMgmt;
	mgmtFuncs[CLASSROOM_MGMT] = classroomMgmt;
	mgmtFuncs[COURSE_MGMT] = courseMgmt;	
}

void Administrator::loadAccount(string account,string password){
	this->adminAccount=account;
	this->password=password;
	hasAccount=true;
}

//����Ա������������ 
void Administrator::process(){
	if(!hasAccount){
		createAdmin();
	}
	while(login()){
		int mgmtChoice=-1; 	
		/*��ӡ�˵�ѡ�� 
		��ʦ��Ϣ
			�� ɾ ��  �� 
		������Ϣ
			�� ɾ ��  �� 
		�γ���Ϣ 
			�� ɾ ��  �� 
		*/
		while(MGMT_MAX != mgmtChoice){
			clear();
			cout << "------����Ա�˵�-------" << endl;
			mgmtChoice = getChoice("ѡ����:", mgmtStr, MGMT_MAX);
			if(MGMT_MAX != mgmtChoice){
				//����ִ�й��������ֱ�����ش����˳� 
				while(mgmtFuncs[mgmtChoice]());
			}
		}
	}
	
}

//��������Ա�˺� 
void Administrator::createAdmin(){
	string comfirmPasswd;
	clear();
	cout << "------��������Ա�˺�-----" << endl;
	cout << "���������Ա�˺�����:" ;
	cin >> adminAccount;
	
	do{
		cout << "���������Ա����:" ;
		cin >> password;
		
		cout << "���ٴ�������ȷ������:" ;
		cin >> comfirmPasswd;	
		
		if(password != comfirmPasswd){
			cout << "�������벻һ�£�����������!" << endl;
		}
	}while(password != comfirmPasswd);
}

bool Administrator::login(){
	string inputAccount;
	string inputPasswd;
	int loginChoice = -1;
	
	clear();
	cout << "------����Ա��½-----" << endl;
	loginChoice = getChoice("", loginStr, LOGIN_MAX);
	if(LOGIN_MAX == loginChoice){
			return false;
	} 
	
	for(int i=0;i<LOGIN_RETRY_MAX;i++){
		cout << "���������Ա�˺�����:" ;
		cin >> inputAccount;
		if(inputAccount != adminAccount){
			cout << "�˺Ų�����!����������"  << endl;
			continue;
		}

		cout << "���������Ա����:" ;
		cin >> inputPasswd;
		if(inputPasswd != password){
			cout << "�������!����������"  << endl;
			continue;
		}
		
		cout << "��½�ɹ�" << endl;
		return true;
	}
	
	cout << "��½��������" << LOGIN_RETRY_MAX << endl; 
	cout << "���˳�" << endl;
	return false;
}

Administrator g_admin;

#endif
