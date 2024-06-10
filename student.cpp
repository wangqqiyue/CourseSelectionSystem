#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

#ifndef INCLUDE_RECORD_PROCESS
#include "recordProcess.h" 
#endif

#ifndef INCLUDE_COURSE
#include "course.h"
#endif

#ifndef INCLUDE_CONIO
#include <conio.h>
#define INCLUDE_CONIO
#endif

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif

#ifndef INCLUDE_SSTREAM
#include <sstream>
#define INCLUDE_SSTREAM
#endif

#ifndef INCLUDE_FSTREAM
#include <fstream>
#define INCLUDE_FSTREAM
#endif

#ifndef INCLUDE_SELECTION_TABLE
#include "selectionTable.h"
#endif

#ifndef INCLUDE_CLASSROOM
#include "classroom.h"
#endif

#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif 

#ifndef INCLUDE_ADMINISTATOR
#include "administrator.h"
#endif


vector<Student> Student::studentList;

//函数指针数组的初始化 
bool (*Student::stuFuncs[Global::STU_FUNC_MAX])() = {showSelectedCourse,Course::retrieve,selectCourse,withdrawCourse,payOrder};
//当前登陆学生账号 
string Student::login_account="";

bool Student::checkAccountExist(string account){
	vector<Student>::iterator i;
	for(i=studentList.begin();i!=studentList.end();++i){
		if(i->account == account){
			return true;
		}
	}
	return false;
}


//返回的是studentList中第一个满足条件（即账号等于传入参数account）的 Student对象的地址。
Student* Student::getElementByAccount(string account){
	for(vector<Student>::iterator i=studentList.begin();i!=studentList.end();i++){
		if(i->account == account){
			return &(*i);
		}
	}
	return NULL;
}


bool Student::checkAccountExist(string account, vector<Student>::iterator &i){
	for(i=studentList.begin();i!=studentList.end();++i){
		if(i->account == account){
			return true;
		}
	}
	return false;
}

//学生基本操作流程 
void Student::process(){
	while(login(Global::STUDENT)){
		int stuFuncChoice = -1;
		while(Global::STU_FUNC_MAX != stuFuncChoice){
			clear();
			cout << "--------学生功能菜单---------" << endl;
			stuFuncChoice = getChoice("选择功能:", Global::stuFuncStr, Global::STU_FUNC_MAX);
			if(Global::STU_FUNC_MAX != stuFuncChoice){
				//不断执行操作，直到返回错误退出 
				stuFuncs[stuFuncChoice]();
			}
		}
	}
}


//创建学生账号 
bool Student::createAccount(){
	string account,name,id,tel,password,comfirmPasswd;
	char comfirm='y';
	bool result=true;
	
	clear();
	cout << "------注册学生账号-----" << endl;
	while('y' == comfirm || 'Y' == comfirm){
		while('y' == comfirm || 'Y' == comfirm){
			cout << "请输入账号名称:" ;
			cin >> account;

			if(checkAccountExist(account)){
				cout << "账号已存在!请重新输入"  << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}
			break;
		}
		if('y' != comfirm && 'Y' != comfirm){
			result=false;
			break;
		}
	
		cout << "请输入姓名：" ;
		cin >> name;
	
		while('y' == comfirm || 'Y' == comfirm){
			cout << "请输入身份证号：" ;
			cin >> id;
			if(Global::ID_LENGTH != id.length()){
				cout << "身份证号长度非法!请重新输入"  << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}
			break;
		}
		if('y' != comfirm && 'Y' != comfirm){
			result=false;
			break;
		}
		
		while('y' == comfirm || 'Y' == comfirm){
			cout << "请输入手机号:";
			cin >> tel;
			if(Global::TEL_LENGTH != tel.length()){
				cout << "手机号长度非法!请重新输入"  << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}
			break;
		}
		if('y' != comfirm && 'Y' != comfirm){
			result=false;
			break;
		}
		
		password = setPassword();	
		
		Student s = Student(account,id,name,tel,password);//新建一个学生对象 
		
		cout << "即将新增数据如下" << endl;
		printTitleToStream(cout);
		s.recordToStream(cout);
		cout << "是否确认新增?Y/N" << endl;
		cin >> comfirm;
		if('y' == comfirm || 'Y' == comfirm){	
			studentList.push_back(s);
			cout << "已新增数据如下" << endl;
			recordToStream(cout, studentList.end() - 1,true);
			Student::login_account =  account;
		}else{
			cout <<"已取消新增"<<endl;
			result = false;
		}
		break; 
	}
	goPrevious();
	return result;
}

bool Student::recordToStream(ostream& out, vector<Student>::iterator firstRecord, bool onlyOne){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	
	printTitleToStream(out);
	for(vector<Student>::iterator i=studentList.begin();i!=studentList.end();i++){
		if(onlyOne){
			i = firstRecord;
		}
		out <<  setw(Global::PRINT_LONG_WIDTH)<<i->account << setw(Global::PRINT_LONG_WIDTH) <<	i->name << setw(Global::PRINT_LONG_WIDTH) <<	i->idCardNumber << setw(Global::PRINT_LONG_WIDTH) <<	i->telphone << setw(Global::PRINT_LONG_WIDTH)  << i->password << endl;
		if(onlyOne){
			break;
		}
	}
	return true;
} 

bool Student::printTitleToStream(ostream& out){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_LONG_WIDTH)<<"账号" << setw(Global::PRINT_LONG_WIDTH) << "姓名" << setw(Global::PRINT_LONG_WIDTH) << "身份证号" << setw(Global::PRINT_LONG_WIDTH) << "手机号" << setw(Global::PRINT_LONG_WIDTH) << "密码"<< endl;
	return true;
}
bool Student::recordToStream(ostream& out){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	
	out <<  setw(Global::PRINT_LONG_WIDTH)<< account << setw(Global::PRINT_LONG_WIDTH) << name << setw(Global::PRINT_LONG_WIDTH) << idCardNumber << setw(Global::PRINT_LONG_WIDTH) << telphone << setw(Global::PRINT_LONG_WIDTH)  << password << endl;

	return true;
} 


//选择菜单  idList是一个课程id名单表 , selectList 是选择表, courseTotal 是可选项总数, isInclusion表示是包含idList中的课程，还是跳过 
bool Student::getSelection(const vector<int>& idList, int* selectList, const int& courseTotal,bool isInclusion){
		
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

            for(i=Course::courseList.begin(),line=0;i!=Course::courseList.end();i++){
            	
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
            for(i=Course::courseList.begin(),line=0,selectTotal=0;i!=Course::courseList.end();i++){
            	            	
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
bool Student::selectCourse(){
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
	 
	courseTotal = Course::courseList.size() - exclusionList.size();//可选课程总数量
	
	if(0 == courseTotal){
		clear();
		cout << "暂无可选课程" << endl;
		goPrevious(); 
		return true;
	}

	selectList = new int[courseTotal];
    for(int i=0;i<courseTotal;i++){
    	selectList[i] = 0;
	}
	

	
	if(!getSelection(exclusionList,selectList,courseTotal,false)){
		free(selectList);
		return false;
	}
	
	if(checkAllZero(selectList,courseTotal)){
		cout << "您未做选择" << endl;
		goPrevious();
		return false;
	}
    
    //确认选课结果计入订单 
    cout << "以下课程已计入订单,请及时在支付页面中付款"  << endl;
    Course::printTitleToStream(cout);
    for(i=Course::courseList.begin(),line=0;i!=Course::courseList.end();i++){
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
bool Student::withdrawCourse(){
	int *selectList;//已选择的课程列表, 如果选中则为1 
	int courseTotal;//可选课程总数量
	int line=0;//行下标 
	vector<Course>::iterator i;//课程遍历迭代器 
    
    //初始化 
    vector<int> unpaidList = CourseSelectionTable::unpaidOrder.getCourseByStudent(Student::login_account);//可退课程列表
	courseTotal = unpaidList.size();//可退课程总数量

	if(0 == courseTotal){
		clear();
		cout << "暂无可退课程" << endl;
		goPrevious(); 
		return true;
	}

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
    for(i=Course::courseList.begin(),line=0;i!=Course::courseList.end();i++){
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
bool Student::showSelectedCourse(){
	
	vector<Course>::iterator i;//课程遍历迭代器 
    
    //初始化 
    vector<int> unpaidList = CourseSelectionTable::unpaidOrder.getCourseByStudent(Student::login_account);//可退课程列表
    vector<int> paidList = CourseSelectionTable::paidOrder.getCourseByStudent(Student::login_account);//可退课程列表

    clear();
    //确认选课结果计入订单 
    cout << "---------------已选课程-----------------"  << endl;
   	cout << setw(Global::PRINT_WIDTH)<<"课程编号" << setw(Global::PRINT_LONG_WIDTH)<<"课程名称"  << setw(Global::PRINT_WIDTH)<<"教室"  << setw(Global::PRINT_WIDTH)<<"授课教师" << setw(Global::PRINT_WIDTH)<<"上课人数" <<setw(Global::PRINT_WIDTH)<< "缴费情况"<<endl;

    for(i=Course::courseList.begin();i!=Course::courseList.end();i++){
    	if(checkExist(paidList,i->courseId) || checkExist(unpaidList,i->courseId)){
    		string roomName,teacherName;
    		
    		Classroom* room = Classroom::getElementById(i->roomId);
    		Teacher* teacher = Teacher::getElementByAccount(i->teacherAccount);
    		if(!room || !teacher){
    			cerr << "教室/教师编号不存在" << endl;
			}
    		cout << setw(Global::PRINT_WIDTH)<<i->courseId <<setw(Global::PRINT_LONG_WIDTH)<< i->courseName << setw(Global::PRINT_WIDTH)<<room->roomName << setw(Global::PRINT_WIDTH)<<teacher->name << setw(Global::PRINT_WIDTH)<<i->studentNumber << setw(Global::PRINT_WIDTH)<<(checkExist(unpaidList,i->courseId)?"未缴费":"已缴费" )<< endl;
		}
	}

	goPrevious(); 
	return true;
}

//支付课程费用 
bool Student::payOrder(){
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
   	for(i=Course::courseList.begin();i!=Course::courseList.end();i++){
   		if(checkExist(unpaidList,i->courseId)){
   			courseTotal++;
   			priceTotal += i->price;
   			Course::recordToStream(cout,i,true);
		}	
	} 
	
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
		
	cout << "共" << courseTotal << "门, 合计" << fixed << setprecision(2) << priceTotal << "元" << endl;
	cout << "请向学校教务处银行卡账户转账" <<  fixed << setprecision(2) << priceTotal << "元" << endl;
	cout << "教务处银行卡账户16位卡号:" << Administrator::bankAccount << endl;
	cout << "注意：支付后，报名信息将计入系统，将无法退课！" << endl;
	cout << "是否继续?Y/N" << endl;
	cin >> comfirm;
	if(comfirm == 'y' || comfirm == 'Y'){
		
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
					
			//向课程增加人数
			for(vector<int>::iterator i=unpaidList.begin();i!=unpaidList.end();i++){
				Course* course = Course::getElementById(*i);
				course->studentNumber += 1;
			} 
		}
		else{
			result = false;
		}
	}else{
		cout << "已取消支付" << endl;
	}
	
	//结算页面 
	if(result){
		cout << "支付成功！选课信息已录入系统，无法更改" << endl;
		CourseSelectionTable::storeInfo();
	}else{
		cout << "信息录入出错,已取消支付" << endl;
	}
	goPrevious(); 
	return result;
}


const char* Student::dataFile = "studentsInfo.txt"; 

bool Student::storeInfo(){
	bool result = true;
	ofstream out;
	
	//写入前设置文件属性为普通 
	SetFileAttributes(dataFile, FILE_ATTRIBUTE_NORMAL);
	
	//加载管理员账号密码
	out.open(dataFile,ios::out);
	if(!Student::recordToStream(out,Student::studentList.begin())){
		result= false;
	}

	out.close();
		
	//写入后设置文件属性为只读,防止他人修改 
	SetFileAttributes(dataFile, FILE_ATTRIBUTE_READONLY);
	
	return result;
}

bool Student::loadInfo(){
	ifstream in;
	string temp;
	
	//加载管理员账号密码
	in.open(dataFile,ios::in);
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
		Student::studentList.push_back(s);
	}
	in.close();
}

