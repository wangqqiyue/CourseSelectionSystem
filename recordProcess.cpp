#ifndef INCLUDE_RECORD_PROCESS
#include "recordProcess.h" 
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


#ifndef INCLUDE_SSTREAM
#include <sstream>
#define INCLUDE_SSTREAM
#endif

#ifndef INCLUDE_FSTREAM
#include <fstream>
#define INCLUDE_FSTREAM
#endif


#ifndef INCLUDE_COURSE_RESOURCE
#include "courseResource.h"
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


#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif

#ifndef INCLUDE_CONIO
#include <conio.h>
#define INCLUDE_CONIO
#endif

#ifndef INCLUDE_ALGORITHM
#include <algorithm>
#define INCLUDE_ALGORITHM
#endif

template<class T>
bool checkExist(const vector<T>& vec, const T& target){
	for(typename vector<T>::const_iterator i=vec.begin();i!=vec.end();i++){
		if(*i == target){
			return true;
		}
	}
	return false;
}

//返回的是studentList中第一个满足条件（即账号等于传入参数account）的 Student对象的地址。
Student* getStudentByAccount(string account){
	for(vector<Student>::iterator i=studentList.begin();i!=studentList.end();i++){
		if(i->account == account){
			return &(*i);
		}
	}
	return NULL;
}

//选择菜单  idList是一个课程id名单表 , selectList 是选择表, courseTotal 是可选项总数, isInclusion表示是包含idList中的课程，还是跳过 
bool getSelection(const vector<int>& idList, int* selectList, const int& courseTotal,bool isInclusion){
		
	static bool firstPrint = true;
	int currentLine = 0;
	int line = 0;
	vector<Course>::iterator i;
	int selectTotal = 0;
	
	while (true) {
        if (_kbhit()|| firstPrint) {

	
        	clear();
        	//标题和规则说明 
			cout << "----------------学生选课----------------" << endl;
			
			//显示当前状态 
			float priceTotal = 0;
			cout << "选课状态" << endl;
			cout << "已选课程数量:" << selectTotal << "(";

            for(i=g_courseList.begin(),line=0;i!=g_courseList.end();i++){
            	
            	if(isInclusion){//跳过非idList里的项目 
            		if(!checkExist(idList,i->courseId)){
						continue;
					}
				}else{//跳过idList里的项目 
					if(checkExist(idList,i->courseId)){
						continue;
					}
				}
				
				if(1 == selectList[line]){
					priceTotal += i->price;
					cout << i->courseName << " ";
				} 
				line++;
			}
			
			cout << ")" << endl;
			cout << "课程总价格:" <<  fixed << setprecision(2)<< priceTotal  << endl;

			//获取输入 
			if(!firstPrint){
	            char ch = _getch();
	            if (ch == 72) { // 上箭头键
	                currentLine--;
	                if (currentLine < 0) {
	                    currentLine += courseTotal;
	                }
					
	            } else if (ch == 80) { // 下箭头键
	                currentLine++;
	                currentLine%=courseTotal;
	            } else if(ch == 13) {//回车键 
	            		selectList[currentLine] += 1;
	            		selectList[currentLine] %= 2;	            		
	        	}else if(ch == 'y'){
	        		firstPrint = true;
	        		return true;
				}else if(ch == 'q'){
					firstPrint = true;
	        		return false;
				}
			}

			Course::printTitleToStream(cout);
			//遍历所有课程行 
            for(i=g_courseList.begin(),line=0,selectTotal=0;i!=g_courseList.end();i++){
            	            	
            	if(isInclusion){//跳过非idList里的项目 
            		if(!checkExist(idList,i->courseId)){
						continue;
					}
				}else{//跳过idList里的项目 
					if(checkExist(idList,i->courseId)){
						continue;
					}
				}
				
            	//当前行高亮 
            	if(line == currentLine){
            		setConsoleColor(FOREGROUND_GREEN |  FOREGROUND_INTENSITY | BACKGROUND_INTENSITY); // 设置前景色为绿色
				}

				//如果当前课程被选中，则高亮 
				if(1 == selectList[line]){
            		setConsoleColor(BACKGROUND_GREEN |  FOREGROUND_INTENSITY | BACKGROUND_INTENSITY); // 设置背景色为白色
            		selectTotal++;
				}
				
            	Course::recordToStream(cout,i,true);
            	setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 恢复默认颜色
            	line++;
			}
			firstPrint = false;
			
			cout <<"操作提示： 上下选择, 回车键选中, [y]键确认, [q] 键退出" << endl;
        }
        
    }
} 

/*----------------------学生选课-------------------------*/
bool selectCourse(){
	int *selectList;//已选择的课程列表, 如果选中则为1 
	int courseTotal;//可选课程总数量
	int line=0;//行下标 
	vector<Course>::iterator i;//课程遍历迭代器 
    
    //初始化 
	vector<int> paidList = CourseSelectionTable::paidOrder.getCourseByStudent(Student::login_account);//已支付的课程列表
	vector<int> unpaidList = CourseSelectionTable::unpaidOrder.getCourseByStudent(Student::login_account);//可退课程列表
	vector<int> exclusionList;//需要跳过的项目=已支付+可退 
	exclusionList.insert(exclusionList.end(),paidList.begin(),paidList.end());
	exclusionList.insert(exclusionList.end(),unpaidList.begin(),unpaidList.end());
	 
	courseTotal = g_courseList.size() - exclusionList.size();//可选课程总数量

	selectList = new int[courseTotal];
    for(int i=0;i<courseTotal;i++){
    	selectList[i] = 0;
	}
	
	if(!getSelection(exclusionList,selectList,courseTotal,false)){
		free(selectList);
		return false;
	}
    
    //确认选课结果计入订单 
    cout << "以下课程已计入订单,请及时在支付页面中付款"  << endl;
    Course::printTitleToStream(cout);
    for(i=g_courseList.begin(),line=0;i!=g_courseList.end();i++){
    	//跳过所有不可选的课程 
		if(checkExist(exclusionList,i->courseId)){
			continue;
		}
		if(1 == selectList[line]){
			Course::recordToStream(cout,i,true);
			CourseSelectionTable::unpaidOrder.addEntry(i->courseId,Student::login_account);
		}
    	line++;
	}

    free(selectList);
	goPrevious(); 
	return true;
}

//退课 
bool withdrawCourse(){
	int *selectList;//已选择的课程列表, 如果选中则为1 
	int courseTotal;//可选课程总数量
	int line=0;//行下标 
	vector<Course>::iterator i;//课程遍历迭代器 
    
    //初始化 
    vector<int> unpaidList = CourseSelectionTable::unpaidOrder.getCourseByStudent(Student::login_account);//可退课程列表
	courseTotal = unpaidList.size();//可退课程总数量

	selectList = new int[courseTotal];
    for(int i=0;i<courseTotal;i++){
    	selectList[i] = 0;
	}
	
	if(!getSelection(unpaidList,selectList,courseTotal)){
		free(selectList);
		return false;
	}
    
    
    //确认选课结果计入订单 
    cout << "以下课程(未缴费)已计入退课单"  << endl;
    Course::printTitleToStream(cout);
    for(i=g_courseList.begin(),line=0;i!=g_courseList.end();i++){
    	//跳过不可退的课程 
		if(!checkExist(unpaidList,i->courseId)){
			continue;
		}
		if(1 == selectList[line]){
			Course::recordToStream(cout,i,true);
			CourseSelectionTable::unpaidOrder.deleteEntry(i->courseId,Student::login_account);
		}
    	line++;
	}

    free(selectList);
	goPrevious(); 
	return true;
}


//查看已选课程 
bool showSelectedCourse(){
	
	vector<Course>::iterator i;//课程遍历迭代器 
    
    //初始化 
    vector<int> unpaidList = CourseSelectionTable::unpaidOrder.getCourseByStudent(Student::login_account);//可退课程列表
    vector<int> paidList = CourseSelectionTable::paidOrder.getCourseByStudent(Student::login_account);//可退课程列表

    clear();
    //确认选课结果计入订单 
    cout << "---------------已选课程-----------------"  << endl;
   	cout << setw(Global::PRINT_WIDTH)<<"课程编号" << setw(Global::PRINT_WIDTH)<<"课程名称"  << setw(Global::PRINT_WIDTH)<<"教室"  << setw(Global::PRINT_WIDTH)<<"授课教师" << setw(Global::PRINT_WIDTH)<<"上课人数" <<setw(Global::PRINT_WIDTH)<< "缴费情况"<<endl;

    for(i=g_courseList.begin();i!=g_courseList.end();i++){
    	if(checkExist(paidList,i->courseId) || checkExist(unpaidList,i->courseId)){
    		string roomName,teacherName;
    		
    		Classroom* room = Classroom::getElementById(i->roomId);
    		Teacher* teacher = Teacher::getElementByAccount(i->teacherAccount);
    		if(!room || !teacher){
    			cerr << "教室/教师编号不存在" << endl;
			}
    		cout << setw(Global::PRINT_WIDTH)<<i->courseId <<setw(Global::PRINT_WIDTH)<< i->courseName << setw(Global::PRINT_WIDTH)<<room->roomName << setw(Global::PRINT_WIDTH)<<teacher->name << setw(Global::PRINT_WIDTH)<<i->studentNumber << setw(Global::PRINT_WIDTH)<<(checkExist(unpaidList,i->courseId)?"未缴费":"已缴费" )<< endl;
		}
	}

	goPrevious(); 
	return true;
}

//支付课程费用 
bool payOrder(){
	int courseTotal = 0;//课程总数量
	float priceTotal = 0;//总价 
	vector<Course>::iterator i;//课程遍历迭代器 
	char comfirm = 'y';
	bool result = true;
    
    //初始化 
    vector<int> unpaidList = CourseSelectionTable::unpaidOrder.getCourseByStudent(Student::login_account);//可退课程列表
    
    clear();
    cout << "---------------选课费用结算-----------------"  << endl;
    
    //未选课情况 
    if(unpaidList.size() == 0){
    	cout << "您没有待支付的课程"<<endl;
    	goPrevious(); 
		return result;
	}
	
	//列举选课未支付课程 
    cout << "您选择了以下课程:" << endl;
    Course::printTitleToStream(cout);
   	for(i=g_courseList.begin();i!=g_courseList.end();i++){
   		if(checkExist(unpaidList,i->courseId)){
   			courseTotal++;
   			priceTotal += i->price;
   			Course::recordToStream(cout,i,true);
		}	
	} 
	cout << "共" << courseTotal << "门, 合计" << fixed << setprecision(2) << priceTotal << "元" << endl;
	
	cout << "注意：支付后，报名信息将计入系统，将无法退课！" << endl;
	cout << "是否继续?Y/N" << endl;
	cin >> comfirm;
	if(comfirm == 'y' || comfirm == 'Y'){
		//尝试在对应课程人数中加1人,注意检查人数限额,如果失败则提示某门课程人数达到上限,建议退课后再支付 
		for(vector<int>::iterator i=unpaidList.begin();i!=unpaidList.end();i++){
			Course* course = Course::getElementById(*i);
			if(course){
				if(course->studentNumber+1>course->capacity){
					cout << "课程" << course->courseName << "已满额，无法选课，建议退课后再重新支付" << endl;
					result = false;
				}
			}else{
				cerr<<"编号为"<<*i<<"的课程不存在"<<endl;
				result = false;
			}
		}
		//如果前面执行失败,则不执行后面的内容 
		if(result){

			//将学生信息录入到paidList
			for(vector<int>::iterator i=unpaidList.begin();i!=unpaidList.end();i++){
				if(!CourseSelectionTable::paidOrder.addEntry(*i,Student::login_account)){
					result=false;
				}
			}

			//清空unpaidList
			for(vector<int>::iterator i=unpaidList.begin();i!=unpaidList.end();i++){
				if(!CourseSelectionTable::unpaidOrder.deleteEntry(*i,Student::login_account)){
					result=false;
				}
			}
					
			
		}
	
	}else{
		result = false;
	}
	
	//结算页面 
	if(result){
		cout << "支付成功！" << endl;
	}else{
		cout << "已取消支付" << endl;
	}
	goPrevious(); 
	return result;
}

//信息加载 
void loadInfo(){
	ifstream in;
	string temp;
	
	//加载管理员账号密码
	in.open("administrator.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		string account,password;
		stringstream ss(temp);
		ss >> account;
		ss >> password;
		Administrator::adminAccount=account;
		Administrator::password=password;
		Administrator::hasAccount=true;
	}
	in.close();
	
	//加载教师信息 
	in.open("teachersInfo.txt",ios::in);
	//一行行读取信息，并分割赋值 
	getline(in,temp);
	while(getline(in,temp)){
		string teacherAccount,teacherName,teacherPassword;
		stringstream ss(temp);
		ss >> teacherAccount;
		ss >> teacherName;
		ss >> teacherPassword;
		Teacher t(teacherAccount,teacherName,teacherPassword);
		teacherList.push_back(t);
	}
	in.close();
	
	//加载课程信息
	in.open("coursesInfo.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		int courseId,number,classroomId,capacity;
		float price;
		string courseName,teacherAccount;
		
		stringstream ss(temp);
		ss >> courseId;
		ss >> courseName;
		ss >> number;
		ss >> price;
		ss >> teacherAccount;
		ss >> classroomId;
		ss >> capacity;
		
		Course c(courseId,courseName,number,price,teacherAccount,classroomId,capacity);
		g_courseList.push_back(c);
	}
	in.close();
	
	//加载教室信息
	in.open("classroomsInfo.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		int roomId,capacity;
		string roomName;
		
		stringstream ss(temp);
		ss >> roomId;
		ss >> roomName;
		ss >> capacity;
		
		Classroom cr(roomId,roomName,capacity);
		g_roomList.push_back(cr);
	}
	in.close();
	
	//加载学生信息
	in.open("studentsInfo.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		string account,name,id,tel,password;
		
		stringstream ss(temp);
		ss >> account;
		ss >> name;
		ss >> id;
		ss >> tel;
		ss >> password;
		
		Student s = Student(account,id,name,tel,password);
		studentList.push_back(s);
	}
	in.close();
	
	//加载选课表 
	in.open("courseSelectionTable.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		string account;
		int id;
		
		stringstream ss(temp);
		ss >> id;
		ss >> account;

		CourseSelectionTable::paidOrder.addEntry(id,account);
	}
	in.close();
	
	//加载订单表 
	in.open("unpaidOrder.txt",ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		string account;
		int id;
		
		stringstream ss(temp);
		ss >> id;
		ss >> account;

		CourseSelectionTable::unpaidOrder.addEntry(id,account);
	}
	in.close();
}


//信息存储
void storeInfo(){
	ofstream out;

	//加载管理员账号密码
	out.open("administrator.txt",ios::out);
	Administrator::recordToStream(out);
	out.close();
	
	//存储教师信息 
	out.open("teachersInfo.txt",ios::out);
	Teacher::recordToStream(out, teacherList.begin());
	out.close();
	
	//存储课程信息 
	out.open("coursesInfo.txt",ios::out);
	Course::recordToStream(out,g_courseList.begin());
	out.close();
	
	//存储教室信息 
	out.open("classroomsInfo.txt",ios::out);
	Classroom::recordToStream(out);
	out.close();
	
	//存储教室信息 
	out.open("studentsInfo.txt",ios::out);
	Student::recordToStream(out,studentList.begin());
	out.close();
	
	//存储选课表信息 
	out.open("courseSelectionTable.txt",ios::out);
	CourseSelectionTable::paidOrder.recordToStream(out);
	out.close();
	
	//存储订单表信息 
	out.open("unpaidOrder.txt",ios::out);
	CourseSelectionTable::unpaidOrder.recordToStream(out);
	out.close();
}


/*----------------管理教师数据 -------------------*/


bool teacherMgmt(){
	int opChoice = -1;
	while(Global::OP_MAX != opChoice){
		opChoice = -1; 
		clear();
		cout << "------教师信息管理-----"  << endl;
		opChoice = getChoice("选择操作:", Global::operationStr, Global::OP_MAX);
		if(Global::RETRIEVE == opChoice){
			return teacherInfoRetrieve();
		}else if(Global::CREATE == opChoice){
			return teacherInfoCreate();
		}
	}
	return false;
}


//查询教师信息 
bool teacherInfoRetrieve(){
	clear();
	cout << "------教师信息查询-----"	<< endl;
	Teacher::recordToStream(cout, teacherList.begin());
	goPrevious(); 
	return true;
	
}

/*新增教师数据 
需要判断新增数据是否有重复,新增后不超过教师总数上限 
*/
bool teacherInfoCreate(){
	string account,name,passwd;
	char comfirm = 'y';
	clear();
	cout << "------新增教师信息-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(teacherList.size() >= Global::TEACHER_NUMBER_MAX){
			cout << "教师数量已达上限("<< Global::TEACHER_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "请输入信息" << endl;
		cout<<"教师账号:";
		cin >> account;

		if(Teacher::checkAccountExist(account)){
			cout << "是否继续?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "教师姓名:" ;
		cin >> name;
		
		cout << "密码;";
		cin >> passwd;
		
		Teacher t(account,name,passwd);
		teacherList.push_back(t);
		
		cout << "已新增数据如下" << endl;
		Teacher::recordToStream(cout, teacherList.end()-1, true);

		cout << "是否继续?Y/N" << endl;
		cin >> comfirm;
	}
	
	cout << "按任意键返回上一级" << endl;
	cin.ignore();
	getchar();
	return true;
	
}
                

/*--------------------------------教室信息管理 ----------------------------------------*/
bool classroomMgmt(){
	int opChoice = -1;
	while(Global::OP_MAX != opChoice){
		opChoice = -1; 
		clear();
		cout << "------教室信息管理-----"  << endl;
		opChoice = getChoice("选择操作:", Global::operationStr, Global::OP_MAX);
		if(Global::RETRIEVE == opChoice){
			return roomInfoRetrieve();
		}else if(Global::CREATE == opChoice){
			return roomInfoCreate();
		}
	}
	return false;
}

//查询教室数据 
bool roomInfoRetrieve(){
	clear();
	cout << "------教室信息查询-----"	<< endl;
	Classroom::recordToStream(cout);
	cout << "按任意键返回上一级" << endl;
	cin.ignore();
	getchar();
	return true;
	
}


/*新增教室数据 
需要判断新增数据是否有重复,新增后不超过教室总数上限 
*/
bool roomInfoCreate(){
	int id,capacity;
	string name;

	char comfirm = 'y';
	clear();
	cout << "------新增教室信息-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(g_roomList.size() >= Global::ROOM_NUMBER_MAX){
			cout << "教室数量已达上限("<< Global::ROOM_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "请输入信息" << endl;
		cout<<"教室编号:";
		cin >> id;
		if(!isInputOk()){
			continue;
		}
		
		vector<Classroom>::iterator i;
		for(i=g_roomList.begin();i!=g_roomList.end();++i){
			if(i->roomId == id){
				cout << "该编号已存在！请重新选择" << endl;
				break;
			}
		}
		if(i != g_roomList.end()){
			cout << "是否继续?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "教室名称:" ;
		cin >> name;
		for(i=g_roomList.begin();i!=g_roomList.end();++i){
			if(i->roomName == name){
				cout << "该名称已存在！请重新选择" << endl;
				break;
			}
		}
		if(i != g_roomList.end()){
			cout << "是否继续?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "教室容量";
		cin >> capacity;
		
		Classroom cr(id,name,capacity);
		g_roomList.push_back(cr);
		
		cout << "已新增数据如下" << endl;
		cout << setw(Global::PRINT_WIDTH)<<"教室编号" << setw(Global::PRINT_LONG_WIDTH) << "教室名称" << setw(Global::PRINT_LONG_WIDTH) << "教室容量"<< endl;
		cout <<  setw(Global::PRINT_WIDTH)<<id << setw(Global::PRINT_LONG_WIDTH) <<	name << setw(Global::PRINT_LONG_WIDTH)  << capacity << endl;
		
		
		cout << "是否继续?Y/N" << endl;
		cin >> comfirm;
	}
	
	cout << "按任意键返回上一级" << endl;
	cin.ignore();
	getchar();
	return true;
	
}

/*--------------------------------课程信息管理--------------------------------------------*/
bool courseMgmt(){
	int opChoice = -1;
	while(Global::OP_MAX != opChoice){
		opChoice = -1; 
		clear();
		cout << "------课程信息管理-----"  << endl;
		opChoice = getChoice("选择操作:", Global::operationStr, Global::OP_MAX);
		if(Global::RETRIEVE == opChoice){
			return courseInfoRetrieve();
		}else if(Global::CREATE == opChoice){
			return courseInfoCreate();
		}
	}
	return false;
}

//查询课程数据 
bool courseInfoRetrieve(){
	clear();
	cout << "------课程信息查询-----"	<< endl;
	Course::recordToStream(cout,g_courseList.begin());
	cout << "按任意键返回上一级" << endl;
	cin.ignore();
	getchar();
	return true;
	
}

/*新增课程数据 
需要判断新增数据是否有重复,新增后不超过课程总数上限 
*/
bool courseInfoCreate(){
	int id,roomId,capacity;
	float price;
	string name,teacherAccount;

	char comfirm = 'y';
	clear();
	cout << "------新增课程信息-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(g_courseList.size() >= Global::COURSE_NUMBER_MAX){
			cout << "课程数量已达上限("<< Global::COURSE_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "请输入信息" << endl;
		
		while('y' == comfirm || 'Y' == comfirm){
			cout<<"课程编号:";
			cin >> id;
			if(!isInputOk()){
				continue;
			}
			
			vector<Course>::iterator i;
			for(i=g_courseList.begin();i!=g_courseList.end();++i){
				if(i->courseId == id){
					cout << "该编号已存在！请重新选择" << endl;
					break;
				}
			}
			if(i != g_courseList.end()){
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
		
		
		while('y' == comfirm || 'Y' == comfirm){
			cout << "课程名称:" ;
			cin >> name;
			
			vector<Course>::iterator i;
			for(i=g_courseList.begin();i!=g_courseList.end();++i){
				if(i->courseName == name){
					cout << "该名称已存在！请重新选择" << endl;
					break;
				}
			}
			if(i != g_courseList.end()){
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
		
		while('y' == comfirm || 'Y' == comfirm){
			cout << "课程价格";
			cin >> price;
			if(price < 0 || price > Global::COURSE_PRICE_MAX){
				cout << "课程价格需要在合理范围(0--"<< Global::COURSE_PRICE_MAX <<")，请重新输入:" << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
		
		while('y' == comfirm || 'Y' == comfirm){
			cout<<"教师帐号:";
			cin >> teacherAccount;

			if(Teacher::checkAccountExist(teacherAccount)){
				cout << "该编号不存在！请重新选择" << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}

		while('y' == comfirm || 'Y' == comfirm){
			cout << "课程人数限额";
			cin >> capacity;
			if(capacity < Global::COURSE_CAPACITY_MIN || capacity > Global::COURSE_CAPACITY_MAX){
				cout << "课程人数限额需要在合理范围("<< Global::COURSE_CAPACITY_MIN <<"--"<< Global::COURSE_CAPACITY_MAX <<")"<<endl;
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
		
		while('y' == comfirm || 'Y' == comfirm){
			cout<<"教室编号:";
			cin >> roomId;
			if(!isInputOk()){
				continue;
			}
			vector<Classroom>::iterator i;
			if(!Classroom::checkExist(roomId,i)){
				cout << "该编号不存在！请重新选择" << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else if(i->capacity < capacity){
				cout << "该教室仅能容纳" << i->capacity << "人, 请重新选择！" << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != comfirm && 'Y' != comfirm){
			break;
		}
				
		//新建课程对象，并添加到向量尾部 
		Course c(id,name,0,price,teacherAccount,roomId,capacity);
		g_courseList.push_back(c);
		
		//打印新增数据 
		cout << "已新增数据如下" << endl;
		Course::recordToStream(cout,g_courseList.end() - 1,true);
		
		cout << "是否继续?Y/N" << endl;
		cin >> comfirm;
	}
	
	cout << "按任意键返回上一级" << endl;
	cin.ignore();
	getchar();
	return true;
	
}
