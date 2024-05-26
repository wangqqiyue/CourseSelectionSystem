#ifndef INCLUDE_ADMINISTATOR
#include "administrator.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_RECORD_PROCESS
#include "recordProcess.h" 
#endif


//��̬��Ա������Ҫ�����ⶨ�� 
bool Administrator::hasAccount=false;
bool Administrator::hasLoaded=false;
string Administrator::adminAccount;
string Administrator::password;



//����ָ������ĳ�ʼ�� 
bool (*Administrator::mgmtFuncs[Global::MGMT_MAX])() = {teacherMgmt,classroomMgmt,courseMgmt};

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
		while(Global::MGMT_MAX != mgmtChoice){
			clear();
			cout << "------����Ա�˵�-------" << endl;
			mgmtChoice = getChoice("ѡ����:", Global::mgmtStr, Global::MGMT_MAX);
			if(Global::MGMT_MAX != mgmtChoice){
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
	loginChoice = getChoice("", Global::loginStr, Global::LOGIN_MAX);
	if(Global::LOGIN_MAX == loginChoice){
			return false;
	} 
	
	for(int i=0;i<Global::LOGIN_RETRY_MAX;i++){
		cout << "���������Ա�˺�����:" ;
		cin >> inputAccount;
		if(inputAccount != adminAccount){
			cout << "�˺Ų�����!����������"  << endl;
			continue;
		}

		cout << "���������Ա����:" ;
		cin >> inputPasswd;
		if(inputPasswd != Administrator::password){
		
			cout << "�������!����������"  << endl;
			cout <<"password="<<password<<endl;
		system("pause");
			continue;
		}
		
		cout << "��½�ɹ�" << endl;
		return true;
	}
	
	cout << "��½��������" << Global::LOGIN_RETRY_MAX << endl; 
	cout << "���˳�" << endl;
	return false;
}

bool Administrator::recordToStream(ostream& out){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_WIDTH)<<"�˺�" << setw(Global::PRINT_WIDTH) << "����" << endl;
	out << setw(Global::PRINT_WIDTH)<<Administrator::adminAccount << setw(Global::PRINT_WIDTH) << Administrator::password << endl;
	return true;
}

