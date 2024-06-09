#ifndef INCLUDE_RECORD_PROCESS
#include "recordProcess.h" 
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_COURSE
#include "course.h"
#endif

#ifndef INCLUDE_ADMINISTATOR
#include "administrator.h"
#endif 

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif


#ifndef INCLUDE_SELECTION_TABLE
#include "selectionTable.h"
#endif

#ifndef INCLUDE_CLASSROOM
#include "classroom.h"
#endif


//��Ϣ���� 
void loadInfo(){
	
	//���ع���Ա��Ϣ	
	Administrator::loadInfo();
	
	//���ؽ�ʦ��Ϣ 
	Teacher::loadInfo();
	
	//���ؿγ���Ϣ
	Course::loadInfo();
	
	//���ؽ�����Ϣ
	Classroom::loadInfo();
	
	//����ѧ����Ϣ
	Student::loadInfo();
	
	//����ѡ�α� 
	CourseSelectionTable::loadInfo();
}


//��Ϣ�洢
void storeInfo(){

	//�洢����Ա��Ϣ 
	Administrator::storeInfo();
	
	//�洢��ʦ��Ϣ 
	Teacher::storeInfo();
	
	//�洢�γ���Ϣ 
	Course::storeInfo();
	
	//�洢������Ϣ 
	Classroom::storeInfo();
	
	//�洢������Ϣ 
	Student::storeInfo();
	
	//�洢ѡ�α���Ϣ 
	CourseSelectionTable::storeInfo();
}

