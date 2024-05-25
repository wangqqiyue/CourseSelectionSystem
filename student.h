#include "role.h"

//学生 有姓名 身份证号 手机号 密码 
/*
功能：登陆
		录入信息、绑定信息 
		查看可选课程
		报名
		获取选课单（姓名、手机号、课程、教师、教室） 
		----------以下是高级功能 
		退选 
		缴费
		
		 
*/ 
class Student{
	int id;
	string name;
	string telphone;
	vector<int> coursesIdList;
	
};
