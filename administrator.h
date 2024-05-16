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
	if(!hasAccount){
		createAdmin();
	}
	login();
	
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
	clear();
	cout << "------����Ա��½-----" << endl;
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
		return true;
	}
	
	cout << "��½��������" << LOGIN_RETRY_MAX << endl; 
	cout << "���˳�" << endl;
	return false;
}

Administrator g_admin;

#endif
