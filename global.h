/*
�����ļ���Ҫ�Ŀ�ͷ�ļ� 
*/

#ifndef INCLUDE_GLOBAL
#define INCLUDE_GLOBAL

#ifndef INCLUDE_IOMANIP
#include <iomanip>
#define INCLUDE_IOMANIP
#endif

#ifndef INCLUDE_IOSTREAM
#include <iostream>
#define INCLUDE_IOSTREAM
#endif 

#ifndef INCLUDE_MINWINDEF
#include <minwindef.h>
#define INCLUDE_MINWINDEF
#endif 


using namespace std;

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
	//���������� 
	static int ROOM_NUMBER_MAX; 
	//���γ����� 
	static int COURSE_NUMBER_MAX; 
	//���γ̼۸� 
	static int COURSE_PRICE_MAX;
	//���γ������޶� 
	static int COURSE_CAPACITY_MAX;
	//��С�γ������޶� 
	static int COURSE_CAPACITY_MIN;
	//���֤�ų��� 
	static int ID_LENGTH;
	//�ֻ��ų��� 
	static int TEL_LENGTH;
	
		
	/*�û���ɫ����ͷ�ļ�*/
	enum Role{
		ADMINISTRATOR=0,
		STUDENT,
		TEACHER,
		ROLE_MAX,
	};
	
	static const char *roleStr[];
	
	enum LoginChoice{
		LOGIN=0,
		LOGIN_MAX,
	};
	
	static const char *loginStr[];

	enum StuLoginChoice{
		STU_SIGNUP=0,
		STU_LOGIN,
		STU_LOGIN_MAX,
	};
	
	static const char *stuLoginStr[];


	//���ݲ���ö�� 
	enum OPERATION{
		CREATE=0,//�� 
		DEL,//ɾ 
		UPDATE,//�� 
		RETRIEVE,//�� 
		OP_MAX,
	};
	
	//�������ַ��� 
	static const char *operationStr[];
	
	//management ����ö�� 
	enum MGMT{
		TEACHER_MGMT=0,
		CLASSROOM_MGMT,
		COURSE_MGMT,
		MGMT_MAX,
	};
	
	//�������ַ��� 
	static const char *mgmtStr[];
	
	//ѧ������ö�� 
	enum STU_FUNC{
		LIST_SELECTED_COURSE=0,//�鿴��ѡ�γ� 
		SHOW_ALL_COURSE,//�鿴���пγ� 
		SELECT_COURSE,//ѡ��
		PAY_ORDER,//���� 
		STU_FUNC_MAX,
	};
	
	//ѧ�������ַ��� 
	static const char *stuFuncStr[];
	
	
	
	//��������ַ��� 
	static const char *titleStr;
}; 


//��տ���̨
void clear();

//���ÿ���̨���� 
void setTitle();

//���ÿ���̨��ɫ 
void setConsoleColor(WORD color);

//ͳһ�Ļ�ӭ����,��ȡ�û���� 
Global::Role greeting();

//��������Ƿ�Ϲ� 
bool isInputOk();

//��ȡ�û������ѡ�� 
int getChoice(const char* promptStr, const char **choiceStr, const int choiceMax);

//��������
string setPassword();

//��½
bool login(Global::Role role);

#endif
