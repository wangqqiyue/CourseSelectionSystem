#ifndef INCLUDE_GLOBAL
#define INCLUDE_GLOBAL


#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif

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
	
	//��������ַ��� 
	static const char *titleStr;
}; 


//��տ���̨
void clear();

//���ÿ���̨���� 
void setTitle();

//ͳһ�Ļ�ӭ����,��ȡ�û���� 
Global::Role greeting();

//��������Ƿ�Ϲ� 
bool isInputOk();

//��ȡ�û������ѡ�� 
int getChoice(const char* promptStr, const char **choiceStr, const int choiceMax);

#endif
