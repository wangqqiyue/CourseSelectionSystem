#ifndef INCLUDE_ADMINISTATOR
#define INCLUDE_ADMINISTATOR

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


#ifndef INCLUDE_STRING
#include <string>
#define INCLUDE_STRING
#endif


//管理员 有账号和密码 
/*
功能：录入课程信息、教室信息 
		分配教师账号密码 
		---------------------以下是高级功能 
		查询统计课程信息 
		查询每个老师名下课程的选课情况
		查询每个教室的上课信息
		查询学生的选课情况和缴费信息
		--------------------以下是亮点功能
		删除无人选课的课程
		修改课程名称和教室
		热门课程推荐
		所有添加删除修改过的数据均以文件形式保存，系统重启后能根据修改后的数据完成各种功能 
*/ 



//由于默认只有一个管理员，不需要被实例化，所以设为静态类 
class Administrator{
public:
	static bool hasAccount;
	static bool hasLoaded;
	static void createAdmin();
	static bool (*mgmtFuncs[Global::MGMT_MAX])();//管理功能的函数指针数组 
	static string adminAccount;//管理员账号 
	static string password;//管理员密码
	static void process();
	static bool recordToStream(ostream& out);
	const static  char* dataFile;//数据存储文件
	static bool storeInfo(); 
	static bool loadInfo();
}; 


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

/*新增课程数据 
需要判断新增数据是否有重复,新增后不超过课程总数上限 
*/
bool courseInfoCreate();

#endif
