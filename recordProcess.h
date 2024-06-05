#ifndef INCLUDE_RECORD_PROCESS
#define INCLUDE_RECORD_PROCESS

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

/*
��¼�������
���и������ݼ�¼�Ĵ���
���������¼�������¼���Ե��������ɾ�Ĳ�� 
*/

/*----------------------ѧ��ѡ��-------------------------*/
bool selectCourse();

bool withdrawCourse();//�˿� 

Student* getStudentByAccount(string account);

//��Ϣ���� 
void loadInfo();

//��Ϣ�洢
void storeInfo();

/*----------------�����ʦ��Ϣ-------------------------------*/
bool teacherMgmt(); 

/*������ʦ���� 
��Ҫ�ж����������Ƿ����ظ�,�����󲻳�����ʦ�������� 
*/
bool teacherInfoCreate();

//��ѯ��ʦ���� 
bool teacherInfoRetrieve();


/*------------------���������Ϣ ----------------------------*/
bool classroomMgmt();

//��ѯ�������� 
bool roomInfoRetrieve();

/*������������ 
��Ҫ�ж����������Ƿ����ظ�,�����󲻳��������������� 
*/
bool roomInfoCreate();

/*-----------------����γ���Ϣ-----------------------------*/
bool courseMgmt();
//��ѯ�γ����� 
bool courseInfoRetrieve();
/*�����γ����� 
��Ҫ�ж����������Ƿ����ظ�,�����󲻳����γ��������� 
*/
bool courseInfoCreate();
#endif
