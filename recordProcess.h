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


/*--------------------------------------文件操作--------------------------------------------------------*/
//信息加载 
void loadInfo();

//信息存储
void storeInfo();

//查询课程数据 
bool courseInfoRetrieve();

#endif
