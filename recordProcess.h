#ifndef INCLUDE_RECORD_PROCESS
#define INCLUDE_RECORD_PROCESS

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

/*
记录处理组件
进行各项数据记录的处理
包括导入记录、载入记录、对单个表的增删改查等 
*/

/*----------------------学生选课-------------------------*/
bool selectCourse();

bool withdrawCourse();//退课 

//查看已选课程 
bool showSelectedCourse();


bool payOrder();//支付课程费用 

Student* getStudentByAccount(string account);

//选择菜单  idList是一个课程id名单表 , selectList 是选择表, courseTotal 是可选项总数, isInclusion表示是包含idList中的课程，还是跳过 
bool getSelection(const vector<int>& idList, int* selectList, const int& courseTotal,bool isInclusion=true);
 
/*--------------------------------------文件操作--------------------------------------------------------*/
//信息加载 
void loadInfo();

//信息存储
void storeInfo();

/*----------------管理教师信息-------------------------------*/
bool teacherMgmt(); 

/*新增教师数据 
需要判断新增数据是否有重复,新增后不超过教师总数上限 
*/
bool teacherInfoCreate();

//查询教师数据 
bool teacherInfoRetrieve();


/*------------------管理教室信息 ----------------------------*/
bool classroomMgmt();

//查询教室数据 
bool roomInfoRetrieve();

/*新增教室数据 
需要判断新增数据是否有重复,新增后不超过教室总数上限 
*/
bool roomInfoCreate();

/*-----------------管理课程信息-----------------------------*/
bool courseMgmt();
//查询课程数据 
bool courseInfoRetrieve();
/*新增课程数据 
需要判断新增数据是否有重复,新增后不超过课程总数上限 
*/
bool courseInfoCreate();
#endif
