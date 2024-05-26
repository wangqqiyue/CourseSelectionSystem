#ifndef INCLUDE_ROLE
#define INCLUDE_ROLE

#ifndef INCLUDE_IOSTREAM
#include <iostream>
#define INCLUDE_IOSTREAM
#endif 

#ifndef INCLUDE_STRING
#include <string>
#define INCLUDE_STRING
#endif

#ifndef INCLUDE_IOMANIP
#include <iomanip>
#define INCLUDE_IOMANIP
#endif

#ifndef INCLUDE_VECTOR
#include <vector>
#define INCLUDE_VECTOR
#endif

#ifndef INCLUDE_ALGORITHM
#include <algorithm>
#define INCLUDE_ALGORITHM
#endif

#ifndef INCLUDE_FUNCTIONAL
#include <functional>
#define INCLUDE_FUNCTIONAL
#endif

using namespace std;

/*�û���ɫ����ͷ�ļ�*/
enum Role{
	ADMINISTRATOR=0,
	STUDENT,
	TEACHER,
	ROLE_MAX,
};

const char *roleStr[]={"����Ա","ѧ��","��ʦ","�˳�"};

enum LoginChoice{
	LOGIN=0,
	LOGIN_MAX,
};

const char *loginStr[]={"��½","������һ��"};

//���ݲ���ö�� 
enum OPERATION{
	CREATE=0,//�� 
	DEL,//ɾ 
	UPDATE,//�� 
	RETRIEVE,//�� 
	OP_MAX,
};

//�������ַ��� 
const char *operationStr[]={"����","ɾ��","�޸�","��ѯ","������һ��"};

//�궨��ȫ�ֱ����� 
class Global{
public:
	//��½��ೢ�Դ��� 
	static int LOGIN_RETRY_MAX;

	//��ӡ�ַ���� 
	static int PRINT_WIDTH;
	static int PRINT_LONG_WIDTH;

	//�����ʦ����
	static int TEACHER_NUMBER_MAX;
}; 

int Global::LOGIN_RETRY_MAX=5;
int Global::PRINT_WIDTH=8;
int Global::PRINT_LONG_WIDTH=16;
int Global::TEACHER_NUMBER_MAX=100;

//��տ���̨
void clear(){
	system("cls");
}

int getChoice(const char* promptStr, const char **choiceStr, const int choiceMax){
	int choice = -1;
	//��choiceMax���û�����ѡ���˳�/���ص���һ�� 
	while(choice > choiceMax || choice < 0){
		cout << promptStr <<endl;
		for(int i=0;i<=choiceMax;i++){
			cout << i << ". " << choiceStr[i] << endl;
		}
		cin >> choice;
		
		//�������������ʱ����������α���int����������char���͵��ַ�����ʱfailbit��ֵ����0��Ϊ1
		if(cin.fail()==true){
			//������ַ��Ῠ�����뻺�������º����޷������������
			cout << "������Ϸ��ַ�!" << endl;
			
			//��������ʹ��cin>>clear()��falibit��Ϊ0����������������������Ȼ��ʹignore()ȡ�����������ַ�������һ�ε���������������С�
			cin.clear();
			cin.ignore();
			choice = -1;
		}
	}
	
	return choice;
}

#endif
