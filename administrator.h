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

//management ����ö�� 
enum MGMT{
	TEACHER_MGMT=0,
	CLASSROOM_MGMT,
	COURSE_MGMT,
	MGMT_MAX,
};

//�������ַ��� 
const char *mgmtStr[]={"�����ʦ��Ϣ","���������Ϣ","����γ���Ϣ","������һ��"};

//��ѯ��ʦ���� 
bool teacherInfoRetrieve(){
	clear();
	cout << "------��ʦ��Ϣ��ѯ-----"	<< endl;
	cout << setw(Global::PRINT_WIDTH)<<"��ʦ���" << setw(Global::PRINT_LONG_WIDTH) << "��ʦ����" << setw(Global::PRINT_LONG_WIDTH) << "����"<< endl;
	for(vector<Teacher>::iterator i=g_teacherList.begin();i!=g_teacherList.end();i++){
		cout <<  setw(Global::PRINT_WIDTH)<<i->teacherId << setw(Global::PRINT_LONG_WIDTH) <<	i->name << setw(Global::PRINT_LONG_WIDTH)  << i->password << endl;
	}
	cout << "�������������һ��" << endl;
	cin.ignore();
	getchar();
	return true;
	
}

/*������ʦ���� 
��Ҫ�ж����������Ƿ����ظ�,�����󲻳�����ʦ�������� 
*/
bool teacherInfoCreate(){
	int id;
	string name;
	string passwd;
	char comfirm = 'y';
	clear();
	cout << "------������ʦ��Ϣ-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(g_teacherList.size() >= Global::TEACHER_NUMBER_MAX){
			cout << "��ʦ�����Ѵ�����("<< Global::TEACHER_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "��������Ϣ" << endl;
		cout<<"��ʦ���:";
		cin >> id;
		if(!isInputOk()){
			continue;
		}
		
		vector<Teacher>::iterator i;
		for(i=g_teacherList.begin();i!=g_teacherList.end();++i){
			if(i->teacherId == id){
				cout << "�ñ���Ѵ��ڣ�������ѡ��" << endl;
				break;
			}
		}
		if(i != g_teacherList.end()){
			cout << "�Ƿ����?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "��ʦ����:" ;
		cin >> name;
		
		cout << "����;";
		cin >> passwd;
		
		Teacher t(id,name,passwd);
		g_teacherList.push_back(t);
		
		cout << "��������������" << endl;
		cout << setw(Global::PRINT_WIDTH)<<"��ʦ���" << setw(Global::PRINT_LONG_WIDTH) << "��ʦ����" << setw(Global::PRINT_LONG_WIDTH) << "����"<< endl;
		cout <<  setw(Global::PRINT_WIDTH)<<id << setw(Global::PRINT_LONG_WIDTH) <<	name << setw(Global::PRINT_LONG_WIDTH)  << passwd << endl;
		
		
		cout << "�Ƿ����?Y/N" << endl;
		cin >> comfirm;
	}
	
	cout << "�������������һ��" << endl;
	cin.ignore();
	getchar();
	return true;
	
}

//�����ʦ��Ϣ 
bool teacherMgmt(){
	int opChoice = -1;
	while(OP_MAX != opChoice){
		opChoice = -1; 
		clear();
		cout << "------��ʦ��Ϣ����-----"  << endl;
		opChoice = getChoice("ѡ�����:", operationStr, OP_MAX);
		if(RETRIEVE == opChoice){
			return teacherInfoRetrieve();
		}else if(CREATE == opChoice){
			return teacherInfoCreate();
		}
	}
	return false;
}


//todo ���ƹ����� 
bool classroomMgmt(){return false;}
bool courseMgmt(){return false;}

//����Ĭ��ֻ��һ������Ա������Ҫ��ʵ������������Ϊ��̬�� 
class Administrator{
public:
	static bool hasAccount;
	static bool hasLoaded;
	static map<int,string> rooms; //���� 
	static void createAdmin();
	static bool login(); 
	static bool (*mgmtFuncs[MGMT_MAX])();//�����ܵĺ���ָ������ 
	static string adminAccount;//����Ա�˺� 
	static string password;//����Ա����
	static void process();

}; 

//��̬��Ա������Ҫ�����ⶨ�� 
bool Administrator::hasAccount=false;
bool Administrator::hasLoaded=false;
string Administrator::adminAccount;
string Administrator::password;

//����ָ������ĳ�ʼ�� 
bool (*Administrator::mgmtFuncs[MGMT_MAX])() = {teacherMgmt,classroomMgmt,courseMgmt};

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


#endif
