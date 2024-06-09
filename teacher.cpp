#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_COURSE
#include "course.h"
#endif

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif


#ifndef INCLUDE_FSTREAM
#include <fstream>
#define INCLUDE_FSTREAM
#endif


#ifndef INCLUDE_SSTREAM
#include <sstream>
#define INCLUDE_SSTREAM
#endif

#ifndef INCLUDE_SELECTION_TABLE
#include "selectionTable.h"
#endif

#ifndef INCLUDE_CLASSROOM
#include "classroom.h"
#endif

#ifndef INCLUDE_CONIO
#include <conio.h>
#define INCLUDE_CONIO
#endif


#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif 

vector<Teacher> teacherList;

//函数指针数组的初始化 
bool (*Teacher::teacherFuncs[Global::TEACHER_FUNC_MAX])() = {Teacher::showTeacherCourse,Teacher::showRoster};
string Teacher::login_account = "";//当前登陆账号 


const char* Teacher::dataFile = "teachersInfo.txt"; 

bool Teacher::storeInfo(){
	bool result = true;
	ofstream out;
	//写入前设置文件属性为普通 
	SetFileAttributes(dataFile, FILE_ATTRIBUTE_NORMAL);
	
	//加载管理员账号密码
	out.open(dataFile,ios::out);
	if(!Teacher::recordToStream(out, teacherList.begin())){
		result= false;
	}

	out.close();
	
	//写入后设置文件属性为只读,防止他人修改 
	SetFileAttributes(dataFile, FILE_ATTRIBUTE_READONLY);
	return result;
}

bool Teacher::loadInfo(){
	ifstream in;
	string temp;

	//加载管理员账号密码
	in.open(dataFile,ios::in);
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
}


//教师基本操作流程 
void Teacher::process(){
	while(login(Global::TEACHER)){
		int funcChoice = -1;
		while(Global::TEACHER_FUNC_MAX != funcChoice){
			clear();
			cout << "--------教师功能菜单---------" << endl;
			funcChoice = getChoice("选择功能:", Global::teacherFuncStr, Global::TEACHER_FUNC_MAX);
			if(Global::TEACHER_FUNC_MAX != funcChoice){
				//不断执行操作，直到返回错误退出 
				teacherFuncs[funcChoice]();
			}
		}

	}
}


bool Teacher::checkAccountExist(string account){
	for(vector<Teacher>::iterator  i=teacherList.begin();i!=teacherList.end();++i){
		if(i->account == account){
			return true;
		}
	}
	return false;
}

bool Teacher::checkAccountExist(string account, vector<Teacher>::iterator &i){
	for(i=teacherList.begin();i!=teacherList.end();++i){
		if(i->account == account){
			return true;
		}
	}
	return false;
}

bool Teacher::printTitleToStream(ostream& out){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	out << setw(Global::PRINT_WIDTH)<<"教师帐号" << setw(Global::PRINT_LONG_WIDTH) << "教师姓名" << setw(Global::PRINT_LONG_WIDTH) << "密码"<< endl;
	return true;
}

bool Teacher::recordToStream(ostream& out, vector<Teacher>::iterator firstRecord, bool onlyOne){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	
	if(!onlyOne){
		printTitleToStream(out);	
	}	
	
	for(vector<Teacher>::iterator i=teacherList.begin();i!=teacherList.end();i++){
		if(onlyOne){
			i=firstRecord;
		}
		out <<  setw(Global::PRINT_WIDTH)<<i->account << setw(Global::PRINT_LONG_WIDTH) <<	i->name << setw(Global::PRINT_LONG_WIDTH)  << i->password << endl;
		if(onlyOne){
			break;
		}
	}
	return true;
} 

bool Teacher::recordToStream(ostream& out, bool onlyOne){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}

	out <<  setw(Global::PRINT_WIDTH)<<account << setw(Global::PRINT_LONG_WIDTH) <<	name << setw(Global::PRINT_LONG_WIDTH)  << password << endl;

	return true;
} 

//根据教师账号返回教师元素的指针 
Teacher* Teacher::getElementByAccount(string account){
		for(vector<Teacher>::iterator i=teacherList.begin();i!=teacherList.end();i++){
		if(i->account == account){
			return const_cast<Teacher*>(&(*i));
		}
	}
}

//打印当前教师名下的课程 
bool Teacher::showTeacherCourse(){
	bool result = true;

	clear();
	cout <<"-------------您名下的课程 -------------------------" << endl;
	Teacher *teacher=getElementByAccount(login_account);
	if(!teacher){
		cerr<<"账号为" << login_account << "的教师不存在" << endl;
		result = false;
	}
	
	cout << setw(Global::PRINT_LONG_WIDTH) << "课程名" << setw(Global::PRINT_WIDTH) << "选课人数" << setw(Global::PRINT_LONG_WIDTH) << "教室" << endl;
	for(vector<Course>::iterator i=Course::courseList.begin();i!=Course::courseList.end();i++){
		Classroom* room;
		if(i->teacherAccount == login_account){
			room = Classroom::getElementById(i->roomId);
			if(!room){
				cerr << "编号为" << i->roomId << "的教室不存在" << endl;
				result = false;
			}
			cout << setw(Global::PRINT_LONG_WIDTH) << i->courseName <<  setw(Global::PRINT_WIDTH) << i->studentNumber <<  setw(Global::PRINT_LONG_WIDTH) << room->roomName << endl;
		}
	}
	goPrevious();
	return result;
}

//打印学生花名册
bool Teacher::showRoster(){
	bool result = true;

	clear();
	cout <<"-------------您名下的课程的学生花名册 -------------------------" << endl;
	
	Teacher *teacher=getElementByAccount(login_account);
	if(!teacher){
		cerr<<"账号为" << login_account << "的教师不存在" << endl;
		result = false;
	}
	
	cout << setw(Global::PRINT_LONG_WIDTH) << "课程名" << setw(Global::PRINT_WIDTH) << "选课人数" << setw(Global::PRINT_LONG_WIDTH) << "教室" << endl;
	for(vector<Course>::iterator i=Course::courseList.begin();i!=Course::courseList.end();i++){
		Classroom* room;
		if(i->teacherAccount == login_account){
			room = Classroom::getElementById(i->roomId);
			if(!room){
				cerr << "编号为" << i->roomId << "的教室不存在" << endl;
				result = false;
			}
			cout << setw(Global::PRINT_LONG_WIDTH) << i->courseName <<  setw(Global::PRINT_WIDTH) << i->studentNumber <<  setw(Global::PRINT_LONG_WIDTH) << room->roomName << endl;
			if(0 == i->studentNumber){
				cout << "暂无学生选此门课程" << endl;
				continue;
			}
			
			cout <<"-------花名册-----" << endl;
			vector<string> studentList = CourseSelectionTable::paidOrder.getStudentByCourse(i->courseId);
			int  rosterNumber = 1;//花名单序号 
			for(vector<string>::iterator j=studentList.begin();j!=studentList.end();j++,rosterNumber++){
				Student* student = Student::getElementByAccount(*j);\
				if(!student){
					cerr << "账号为" << *j <<"的学生不存在" << endl;
					result = false;
				}
				cout << rosterNumber << ". " << student->name << endl;
			}
			cout << endl;
		}
	}
	goPrevious();
	return result;
} 


//查询教师信息 
bool Teacher::retrieve(){
	clear();
	cout << "------教师信息查询-----"	<< endl;
	recordToStream(cout, teacherList.begin());
	goPrevious(); 
	return true;
	
}

/*新增教师数据 
需要判断新增数据是否有重复,新增后不超过教师总数上限 
*/
bool Teacher::create(){
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
			cout << "该账号已存在" << endl; 
			cout << "是否继续?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "教师姓名:" ;
		cin >> name;
		
		passwd=setPassword();
		
		Teacher t(account,name,passwd);//新建一个教师对象 
		
		cout << "即将新增数据如下" << endl;
		printTitleToStream(cout);
		t.recordToStream(cout);
		cout << "是否确认新增?Y/N" << endl;
		cin >> comfirm;
		if('y' == comfirm || 'Y' == comfirm){	
			teacherList.push_back(t);
			cout << "已新增数据如下" << endl;
			Teacher::recordToStream(cout, teacherList.end()-1, true);
		}else{
			cout <<"已取消新增"<<endl;
		}
		
		cout << "是否继续?Y/N" << endl;
		cin >> comfirm;
	}
	
	goPrevious();
	return true;
	
}
        


//选择菜单  idList是一个课程id名单表 , selectList 是选择表, teacherTotal 是可选项总数, isInclusion表示是包含idList中的课程，还是跳过 
bool Teacher::getSelection(const string prompt, const vector<string>& idList, int* selectList, const int& teacherTotal,bool isInclusion,bool onlyOne){
		
	static bool firstPrint = true;
	int currentLine = 0;
	int line = 0;
	vector<Teacher>::iterator i;
	int selectTotal = 0;
	
	while (true) {
        if (_kbhit()|| firstPrint) {

	
        	clear();
        	//标题和规则说明 
			cout << "----------------"<< prompt <<"----------------" << endl;
			
			//显示当前状态 
			float priceTotal = 0;
			cout << "选择状态" << endl;
			cout << "已选教师数量:" << selectTotal << "(";

            for(i=teacherList.begin(),line=0;i!=teacherList.end();i++){
            	
            	if(isInclusion){//跳过非idList里的项目 
            		if(!checkExist(idList,i->account)){
						continue;
					}
				}else{//跳过idList里的项目 
					if(checkExist(idList,i->account)){
						continue;
					}
				}
				
				if(1 == selectList[line]){
					cout << i->name << " ";
				} 
				line++;
			}
			
			cout << ")" << endl;

			//获取输入 
			if(!firstPrint){
	            char ch = _getch();
	            if (ch == 72) { // 上箭头键
	                currentLine--;
	                if (currentLine < 0) {
	                    currentLine += teacherTotal;
	                }
					
	            } else if (ch == 80) { // 下箭头键
	                currentLine++;
	                currentLine%=teacherTotal;
	            } else if(ch == 13) {//回车键 
            		selectList[currentLine] += 1;
            		selectList[currentLine] %= 2;	  
					if(onlyOne){
						firstPrint = true;
						return true;
					}          		
	        	}else if(ch == 'y'){
	        		firstPrint = true;
	        		return true;
				}else if(ch == 'q'){
					firstPrint = true;
	        		return false;
				}
			}

			printTitleToStream(cout);
			//遍历所有课程行 
            for(i=teacherList.begin(),line=0,selectTotal=0;i!=teacherList.end();i++){
            	            	
            	if(isInclusion){//跳过非idList里的项目 
            		if(!checkExist(idList,i->account)){
						continue;
					}
				}else{//跳过idList里的项目 
					if(checkExist(idList,i->account)){
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
				
            	recordToStream(cout,i,true);
            	setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 恢复默认颜色
            	line++;
			}
			firstPrint = false;
			
			cout <<"操作提示： 上下选择, 回车键选中, [y]键确认, [q] 键退出" << endl;
        }
        
    }
} 

bool Teacher::del(){
	int *selectList;//已选择的课程列表, 如果选中则为1 
	int teacherTotal;//可选课程总数量
	int line=0;//行下标 
	vector<Course>::iterator i;//课程遍历迭代器 
    
    //初始化 
    vector<string> undeletableList;//不可删课程列表
    for(i=Course::courseList.begin();i!=Course::courseList.end();i++){
    	//如果课程人数不为0，且该老师未加入到不可删除列表，则加入 
    	if(0 != i->studentNumber){
    		if(!checkExist(undeletableList,i->teacherAccount)){
    			undeletableList.push_back(i->teacherAccount);
			}
		}
	}
    
	teacherTotal = teacherList.size() - undeletableList.size();//可删除教室的总数量
	if(0 == teacherTotal){
		clear();
		cout << "目前没有可以删除的教师账号" << endl;
		goPrevious(); 
		return false;
	}

	selectList = new int[teacherTotal];
    for(int i=0;i<teacherTotal;i++){
    	selectList[i] = 0;
	}
	
	if(!getSelection("删除无课程任务的教师账号", undeletableList,selectList,teacherTotal,false)){
		free(selectList);
		return false;
	}
	
	
	if(checkAllZero(selectList,teacherTotal)){
		cout << "您未做选择" << endl;
		goPrevious();
		return false;
	}
	
    //确认选课结果并删除 
    cout << "以下教师账号已删除"  << endl;
    printTitleToStream(cout);
    vector<Teacher>::iterator it;
    for(it=teacherList.begin(),line=0;it!=teacherList.end();it++){
    	//跳过不可删的教师 
		if(checkExist(undeletableList,it->account)){
			continue;
		}
		if(1 == selectList[line]){
			recordToStream(cout,it,true);
			it = teacherList.erase(it);// erase之后，令当前迭代器指向其后继。否则迭代器失效,会报错
			it--;
		}
    	line++;
	}

    free(selectList);
	goPrevious(); 
	return true;
}
 
bool Teacher::update(){
	int *selectList;//已选择的课程列表, 如果选中则为1 
	int teacherTotal;//可选课程总数量
	int line=0;//行下标 

	vector<string> idList;
	vector<string> unchangableAccounts;
	for(vector<Teacher>::iterator i=teacherList.begin();i!=teacherList.end();i++){
		idList.push_back(i->account);
	}
	
	for(vector<Course>::iterator i=Course::courseList.begin();i!=Course::courseList.end();i++){
		if(0 != i->studentNumber){
			unchangableAccounts.push_back(i->teacherAccount);
		}
	}
	
	teacherTotal = teacherList.size();//可修改的总数量
	if(0 == teacherTotal){
		clear();
		cout << "目前没有可以修改的教师账号" << endl;
		goPrevious(); 
		return false;
	}

	selectList = new int[teacherTotal];
    for(int i=0;i<teacherTotal;i++){
    	selectList[i] = 0;
	}
	
	if(!getSelection("修改教师账号", idList,selectList,teacherTotal,true,true)){
		free(selectList);
		return false;
	}

	if(checkAllZero(selectList,teacherTotal)){
		cout << "您未做选择" << endl;
		goPrevious();
		return false;
	}
	
    //确认选课结果并删除 
    cout << "以下教师账号待修改"  << endl;
    printTitleToStream(cout);
    vector<Teacher>::iterator it;
    for(it=teacherList.begin(),line=0;it!=teacherList.end();it++){

		if(1 == selectList[line]){
			recordToStream(cout,it,true);
			changeInfo(unchangableAccounts, it);
		}
    	line++;
	}

    free(selectList);
	goPrevious(); 
	return true;
}

bool Teacher::changeInfo(const vector<string>& unchangableAccounts,vector<Teacher>::iterator &it){
	string account,name,passwd;
	
	if(checkExist(unchangableAccounts,it->account)){
		cout << "该教师有授课,无法修改账号" << endl;
	}else{
		char comfirm = 'y';
		while(comfirm == 'y' || 'Y' == comfirm){
			cout << "请输入教师账号:";
			cin >> account;
			if(Teacher::checkAccountExist(account)){
				cout << "账号已存在" << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> comfirm;
				continue;
			}
			it->account = account;
			break;
		}
	}
	
	cout << "教师姓名:" ;
	cin >> name;

	passwd = setPassword();
	
	it->name = name;
	it->password = passwd;
	
	cout << "修改如下" << endl;
	printTitleToStream(cout);
	recordToStream(cout,it,true);
}
