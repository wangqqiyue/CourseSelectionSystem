#ifndef _ADMINISTATOR_H 
#define _ADMINISTATOR_H

#include "role.h"
#include "teacher.h"

#include<map>

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

class Administrator{
private:
	bool hasAccount=false;
	bool hasLoaded=false;
	map<int,string> rooms; //���� 
	void createAdmin();
	bool login(); 
	
public:
	string adminAccount;//����Ա�˺� 
	string password;//����Ա����
	void loadAccount(string account,string password); 
	void process();

}; 

void Administrator::loadAccount(string account,string password){
	this->adminAccount=account;
	this->password=password;
	hasAccount=true;
}

//����Ա������������ 
void Administrator::process(){
	int mgmtChoice=MGMT_MAX; 
	if(!hasAccount){
		createAdmin();
	}
	while(login()){
		clear();
		cout << "------����Ա�˵�-------" << endl;
		/*��ӡ�˵�ѡ�� 
		��ʦ��Ϣ
			�� ɾ ��  �� 
		������Ϣ
			�� ɾ ��  �� 
		�γ���Ϣ 
			�� ɾ ��  �� 
		*/
		mgmtChoice = getChoice("ѡ����:", mgmtStr, MGMT_MAX);
		if(MGMT_MAX == mgmtChoice){
			continue;
		}
		//todo ʵ�־��幦�� 
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
