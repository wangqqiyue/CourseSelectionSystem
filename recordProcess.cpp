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


//信息加载 
void loadInfo(){
	
	//加载管理员信息	
	Administrator::loadInfo();
	
	//加载教师信息 
	Teacher::loadInfo();
	
	//加载课程信息
	Course::loadInfo();
	
	//加载教室信息
	Classroom::loadInfo();
	
	//加载学生信息
	Student::loadInfo();
	
	//加载选课表 
	CourseSelectionTable::loadInfo();
}


//信息存储
void storeInfo(){

	//存储管理员信息 
	Administrator::storeInfo();
	
	//存储教师信息 
	Teacher::storeInfo();
	
	//存储课程信息 
	Course::storeInfo();
	
	//存储教室信息 
	Classroom::storeInfo();
	
	//存储教室信息 
	Student::storeInfo();
	
	//存储选课表信息 
	CourseSelectionTable::storeInfo();
}

