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
	while(login(Global::ADMINISTRATOR)){
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
	clear();
	cout << "------��������Ա�˺�-----" << endl;
	cout << "���������Ա�˺�����:" ;
	cin >> adminAccount;
	
	Administrator::password = setPassword();
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

