#ifndef INCLUDE_RECORD_PROCESS
#define INCLUDE_RECORD_PROCESS

/*
��¼�������
���и������ݼ�¼�Ĵ���
���������¼�������¼���Ե��������ɾ�Ĳ�� 
*/


//��Ϣ���� 
void loadInfo();

//��Ϣ�洢
void storeInfo();

//�����ʦ��Ϣ 
bool teacherMgmt(); 
bool classroomMgmt();
bool courseMgmt();

/*������ʦ���� 
��Ҫ�ж����������Ƿ����ظ�,�����󲻳�����ʦ�������� 
*/
bool teacherInfoCreate();

//��ѯ��ʦ���� 
bool teacherInfoRetrieve();

#endif
