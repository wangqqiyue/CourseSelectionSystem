#ifndef INCLUDE_COURSE 
#define INCLUDE_COURSE

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

/*
�γ��пγ����ơ���Ӧ���ҡ���ʦ��ѡ������ ���۸�� 
Ĭ��ÿ�ſ�ֻ��һ����ʦ 
���ܣ�
	�޸Ŀγ�����
	�޸Ŀγ�����
	�޸Ŀγ̼۸�
	�޸���ʦ
	�޸Ľ���  
*/
class Course{
public:
	int courseId;
	string courseName;
	int studentNumber;
	//�Ͽ�ʱ��������6�㵽����10�� ,6-8,8-10,10-12,12-14,14-16,16-18,18-20,20-22 һ��8��ʱ��� ,�����Ŀγ�ֻ������8��ʱ�����ѡ��
	int courseHourIndex; //�Ͽ�ʱ���±� ,0����6-8,1����8-10���Դ����� 
	int capacity;//�γ������޶� 
	float price;
	string teacherAccount;
	int roomId;

	Course(int id,string name,int num,float p,string tAcc,int rId,int c,int index):courseId(id),courseName(name),studentNumber(num),price(p),teacherAccount(tAcc),roomId(rId),capacity(c),courseHourIndex(index){}
		
	static bool recordToStream(ostream& os, vector<Course>::iterator firstRecord,bool onlyOne=false);
	bool recordToStream(ostream& os);
	static bool printTitleToStream(ostream& out);
	static Course* getElementById(int id);
	static vector<Course> courseList;
	const static  char* dataFile;//���ݴ洢�ļ�
	static bool storeInfo(); 
	static bool loadInfo();
	static bool create();
	static bool del();
	static bool retrieve();
	static bool update();
	static bool changeInfo(vector<Course>::iterator& it);
	static bool getSelection(const string prompt, const vector<int>& idList, int* selectList, const int& courseTotal,bool isInclusion=true, bool onlyOne = false);
	static int courseHourTable[8];
};


#endif
