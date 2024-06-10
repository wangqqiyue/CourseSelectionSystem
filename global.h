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


#ifndef INCLUDE_VECTOR
#include <vector>
#define INCLUDE_VECTOR
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
	//���γ������޶� 
	static int ROOM_CAPACITY_MAX;
	//��С�γ������޶� 
	static int ROOM_CAPACITY_MIN;
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

	enum greetingChoice{
		GREETING_CONTINUE=0,
		GREETING_ABOUT,
		GREETING_MAX,
	};
	
	static const char *greetingStr[];

	static const char *aboutInfoFile;

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
		WITHDRAW_COURSE,//�˿�
		PAY_ORDER,//���� 
		STU_FUNC_MAX,
	};
	
	//��ʦ�����ַ��� 
	static const char *teacherFuncStr[];
	
	//��ʦ����ö�� 
	enum TEACHER_FUNC{
		SHOW_TEACHER_COURSE=0,//�鿴��ѡ�γ� 
		SHOW_ROSTER,//�鿴ѧ������ 
		TEACHER_FUNC_MAX,
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

//ͳһ�Ļ�ӭ����
bool greeting();

//��ӡ������Ϣ 
bool printAboutInfo();

 //��ȡ�û����
Global::Role getRole();

//��������Ƿ�Ϲ� 
bool isInputOk();

//��ȡ�û������ѡ�� 
int getChoice(const char* promptStr, const char **choiceStr, const int choiceMax);

//��������
string setPassword();

//��½
bool login(Global::Role role);

//������һ��
void goPrevious();

//��������� 
void goContinue();

//����Ƿ����id 
template<class T>
bool checkExist(const vector<T>& vec, const T& target){
	for(typename vector<T>::const_iterator i=vec.begin();i!=vec.end();i++){
		if(*i == target){
			return true;
		}
	}
	return false;
}

 bool checkAllZero(int *selectList, int total);
 
#endif
