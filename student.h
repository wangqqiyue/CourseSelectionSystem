#ifndef INCLUDE_STUDENT
#define INCLUDE_STUDENT

#ifndef INCLUDE_ROLE
#include "role.h"
#endif

//ѧ�� ������ ���֤�� �ֻ��� ���� 
/*
���ܣ���½
		¼����Ϣ������Ϣ 
		�鿴��ѡ�γ�
		����
		��ȡѡ�ε����������ֻ��š��γ̡���ʦ�����ң� 
		----------�����Ǹ߼����� 
		��ѡ 
		�ɷ�
		
		 
*/ 
class Student{
	int id;
	string name;
	string telphone;
	vector<int> coursesIdList;
	
};

#endif
