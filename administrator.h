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
	static bool login(); 
	static bool (*mgmtFuncs[Global::MGMT_MAX])();//�����ܵĺ���ָ������ 
	static string adminAccount;//����Ա�˺� 
	static string password;//����Ա����
	static void process();

}; 


#endif
