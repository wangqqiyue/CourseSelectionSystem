#ifndef INCLUDE_ADMINISTATOR
#define INCLUDE_ADMINISTATOR

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


#ifndef INCLUDE_STRING
#include <string>
#define INCLUDE_STRING
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



//����Ĭ��ֻ��һ������Ա������Ҫ��ʵ������������Ϊ��̬�� 
class Administrator{
public:
	static bool hasAccount;
	static bool hasLoaded;
	static void createAdmin();
	static bool (*mgmtFuncs[Global::MGMT_MAX])();//�����ܵĺ���ָ������ 
	static string adminAccount;//����Ա�˺� 
	static string password;//����Ա����
	static void process();
	static bool recordToStream(ostream& out);
	const static  char* dataFile;//���ݴ洢�ļ�
	static bool storeInfo(); 
	static bool loadInfo();
}; 


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


/*-----------------����γ���Ϣ-----------------------------*/
bool courseMgmt();


#endif
