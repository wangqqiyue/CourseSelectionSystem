#ifndef INCLUDE_COURSE
#include "course.h"
#endif

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif

#ifndef INCLUDE_CLASSROOM
#include "classroom.h"
#endif

/*-----------------Course 定义实现-------------------------------------*/ 
vector<Course> Course::courseList;

const char* Course::dataFile = "coursesInfo.txt"; 
int Course::courseHourTable[8] = {0}; 

bool Course::storeInfo(){
	bool result = true;
	ofstream out;
	//写入前设置文件属性为普通 
	SetFileAttributes(dataFile, FILE_ATTRIBUTE_NORMAL);
	
	//加载管理员账号密码
	out.open(dataFile,ios::out);
	if(!Course::recordToStream(out,Course::courseList.begin())){
		result= false;
	}

	out.close();
	
	//写入后设置文件属性为只读,防止他人修改 
	SetFileAttributes(dataFile, FILE_ATTRIBUTE_READONLY);
	return result;
}

bool Course::loadInfo(){
	ifstream in;
	string temp;
	
	//加载课程信息 
	in.open(dataFile,ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		int courseId,number,classroomId,capacity,courseHourIndex;
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
		ss >> courseHourIndex;
		
		Course c(courseId,courseName,number,price,teacherAccount,classroomId,capacity,courseHourIndex);
		Course::courseList.push_back(c);
	}
	in.close();
}

bool Course::printTitleToStream(ostream& out){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	out << setw(Global::PRINT_WIDTH)<<"课程编码" << setw(Global::PRINT_LONG_WIDTH) << "课程名" << setw(Global::PRINT_WIDTH) << "选课人数"<< setw(Global::PRINT_WIDTH) << "课程价格"<< setw(Global::PRINT_WIDTH) << "任课老师"<< setw(Global::PRINT_WIDTH) << "教室" << setw(Global::PRINT_WIDTH) <<  "人数限额" << setw(Global::PRINT_WIDTH) <<  "上课时间段" << endl;	
	return true;
}

//传入流对象，迭代器, 是否只打印一条记录 
bool Course::recordToStream(ostream& out, vector<Course>::iterator firstRecord, bool onlyOne){ 
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}

	if(!onlyOne){
		printTitleToStream(out);	
	}		
	
	for(vector<Course>::iterator i = Course::courseList.begin();i!=Course::courseList.end();i++){
		if(onlyOne){
			i=firstRecord;
		}
		out <<  setw(Global::PRINT_WIDTH)<<i->courseId << setw(Global::PRINT_LONG_WIDTH) <<	i->courseName << setw(Global::PRINT_WIDTH)  << i->studentNumber << setw(Global::PRINT_WIDTH) << fixed << setprecision(2) << i->price << setw(Global::PRINT_WIDTH)  << i->teacherAccount << setw(Global::PRINT_WIDTH)  << i->roomId << setw(Global::PRINT_WIDTH)  << i->capacity ;
		if(onlyOne){
			out << setw(Global::PRINT_WIDTH)  << Global::courseHourStr[i->courseHourIndex] << endl;
			break;
		}else{
			out << setw(Global::PRINT_WIDTH)  << i->courseHourIndex << endl;
		}		
	}
	return true;
}

 
bool Course::recordToStream(ostream& out){ 
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	out <<  setw(Global::PRINT_WIDTH)<< courseId << setw(Global::PRINT_LONG_WIDTH) <<	 courseName << setw(Global::PRINT_WIDTH)  <<  studentNumber << setw(Global::PRINT_WIDTH) << fixed << setprecision(2) << price << setw(Global::PRINT_WIDTH)  <<  teacherAccount << setw(Global::PRINT_WIDTH)  << roomId << setw(Global::PRINT_WIDTH)  << capacity  << setw(Global::PRINT_WIDTH)  << Global::courseHourStr[courseHourIndex]<<  endl;
	return true;
}

Course* Course::getElementById(int id){
		for(vector<Course>::iterator i=Course::courseList.begin();i!=Course::courseList.end();i++){
		if(i->courseId == id){
			return const_cast<Course*>(&(*i));
		}
	}
}

/*新增课程数据 
需要判断新增数据是否有重复,新增后不超过课程总数上限 
*/
bool Course::create(){
	int id,roomId,capacity;
	float price;
	string name,teacherAccount;

	char confirm = 'y';
	clear();
	cout << "------新增课程信息-----"	<< endl;
	
	while('y' == confirm || 'Y' == confirm){
		if(Course::courseList.size() >= Global::COURSE_NUMBER_MAX){
			cout << "课程数量已达上限("<< Global::COURSE_NUMBER_MAX <<")!" << endl;
			break;
		}
		cout << "请输入信息" << endl;
		
		while('y' == confirm || 'Y' == confirm){
			cout<<"课程编号:";
			cin >> id;
			if(!isInputOk()){
				continue;
			}
			
			vector<Course>::iterator i;
			for(i=Course::courseList.begin();i!=Course::courseList.end();++i){
				if(i->courseId == id){
					cout << "该编号已存在！请重新选择" << endl;
					break;
				}
			}
			if(i != Course::courseList.end()){
				cout << "是否继续?Y/N" << endl;
				cin >> confirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != confirm && 'Y' != confirm){
			break;
		}
		
		
		while('y' == confirm || 'Y' == confirm){
			cout << "课程名称:" ;
			cin >> name;
			
			vector<Course>::iterator i;
			for(i=Course::courseList.begin();i!=Course::courseList.end();++i){
				if(i->courseName == name){
					cout << "该名称已存在！请重新选择" << endl;
					break;
				}
			}
			if(i != Course::courseList.end()){
				cout << "是否继续?Y/N" << endl;
				cin >> confirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != confirm && 'Y' != confirm){
			break;
		}
		
		while('y' == confirm || 'Y' == confirm){
			cout << "课程价格";
			cin >> price;
			
			if(!isInputOk()){
				continue;
			}
			
			if(price < 0 || price > Global::COURSE_PRICE_MAX){
				cout << "课程价格需要在合理范围(0--"<< Global::COURSE_PRICE_MAX <<")，请重新输入:" << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> confirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != confirm && 'Y' != confirm){
			break;
		}
		
		while('y' == confirm || 'Y' == confirm){
			cout<<"教师帐号:";
			cin >> teacherAccount;

			if(!Teacher::checkAccountExist(teacherAccount)){
				cout << "该编号不存在！请重新选择" << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> confirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != confirm && 'Y' != confirm){
			break;
		}

		while('y' == confirm || 'Y' == confirm){
			cout << "课程人数限额";
			cin >> capacity;
			if(!isInputOk()){
				continue;
			}
			
			if(capacity < Global::COURSE_CAPACITY_MIN || capacity > Global::COURSE_CAPACITY_MAX){
				cout << "课程人数限额需要在合理范围("<< Global::COURSE_CAPACITY_MIN <<"--"<< Global::COURSE_CAPACITY_MAX <<")"<<endl;
				cout << "是否继续?Y/N" << endl;
				cin >> confirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != confirm && 'Y' != confirm){
			break;
		}
		
		while('y' == confirm || 'Y' == confirm){
			cout<<"教室编号:";
			cin >> roomId;
			if(!isInputOk()){
				continue;
			}
			vector<Classroom>::iterator i;
			if(!Classroom::checkIdExist(roomId,i)){
				cout << "该编号不存在！请重新选择" << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> confirm;
				continue;
			}else if(i->capacity < capacity){
				cout << "该教室仅能容纳" << i->capacity << "人, 请重新选择！" << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> confirm;
				continue;
			}else{
				break;
			}
		}
		if('y' != confirm && 'Y' != confirm){
			break;
		}
		
		int courseHourChoice = -1;
		while('y' == confirm || 'Y' == confirm){
			courseHourChoice = -1;
			courseHourChoice = getChoice("请选择上课时间段", Global::courseHourStr,Global::COURSE_HOURS_LENGTH);
			if(Global::COURSE_HOURS_LENGTH == courseHourChoice){
				cout <<"已取消新增"<<endl;
			}else if(0 != courseHourTable[courseHourChoice]){
				cout << "已有课程在该时间段" << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> confirm;
				continue;
			}else{
				courseHourTable[courseHourChoice] = 1;
				break;
			}
		}
		if('y' != confirm && 'Y' != confirm){
			break;
		}
		
		//新建课程对象，并添加到向量尾部 
		Course c(id,name,0,price,teacherAccount,roomId,capacity,courseHourChoice);
		cout << "即将新增数据如下" << endl;
		printTitleToStream(cout);
		c.recordToStream(cout);
		cout << "是否确认新增?Y/N" << endl;
		cin >> confirm;
		if('y' == confirm || 'Y' == confirm){	
			courseList.push_back(c);
			cout << "已新增数据如下" << endl;
			printTitleToStream(cout);
			recordToStream(cout,Course::courseList.end() - 1,true);
		}else{
			cout <<"已取消新增"<<endl;
		}

		cout << "是否继续?Y/N" << endl;
		cin >> confirm;
	}
	
	goPrevious();
	return true;
	
}

//选择菜单  idList是一个课程id名单表 , selectList 是选择表, courseTotal 是可选项总数, isInclusion表示是包含idList中的课程，还是跳过 
bool Course::getSelection(const string prompt, const vector<int>& idList, int* selectList, const int& courseTotal,bool isInclusion,bool onlyOne){
		
	static bool firstPrint = true;
	int currentLine = 0;
	int line = 0;
	vector<Course>::iterator i;
	int selectTotal = 0;
	
	while (true) {
        if (_kbhit()|| firstPrint) {

	
        	clear();
        	//标题和规则说明 
			cout << "----------------"<<prompt<<"----------------" << endl;
			
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
					cout << i->courseName << " ";
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
	                    currentLine += courseTotal;
	                }
					
	            } else if (ch == 80) { // 下箭头键
	                currentLine++;
	                currentLine%=courseTotal;
	            } else if(ch == 13) {//回车键 
	            		selectList[currentLine] += 1;
	            		selectList[currentLine] %= 2;	        
						if(onlyOne) {
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

bool Course::del(){
	int *selectList;//已选择的课程列表, 如果选中则为1 
	int courseTotal;//可选课程总数量
	int line=0;//行下标 
	vector<Course>::iterator i;//课程遍历迭代器 
    
    //初始化 
    vector<int> deletableList;//可删课程列表
    for(i=courseList.begin();i!=courseList.end();i++){
    	if(0 == i->studentNumber){
    		deletableList.push_back(i->courseId);
		}
	}
    
	courseTotal = deletableList.size();//可退课程总数量
	if(0 == courseTotal){
		clear();
		cout << "目前没有可以删除的课程" << endl;
		goPrevious(); 
		return false;
	}

	selectList = new int[courseTotal];
    for(int i=0;i<courseTotal;i++){
    	selectList[i] = 0;
	}
	
	if(!getSelection("删除无人选课的课程",deletableList,selectList,courseTotal)){
		free(selectList);
		return false;
	}
	
	if(checkAllZero(selectList,courseTotal)){
		cout << "您未做选择" << endl;
		goPrevious();
		return false;
	}
	
    //确认选课结果并删除 
    cout << "以下课程已删除"  << endl;
    Course::printTitleToStream(cout);
    for(i=Course::courseList.begin(),line=0;i!=Course::courseList.end();i++){
    	//跳过不可退的课程 
		if(!checkExist(deletableList,i->courseId)){
			continue;
		}
		if(1 == selectList[line]){
			recordToStream(cout,i,true);
			i = courseList.erase(i);// erase之后，令当前迭代器指向其后继。否则迭代器失效,会报错
			i--;
		}
    	line++;
	}

    free(selectList);
	goPrevious(); 
	return true;
}


//查询课程数据 
bool Course::retrieve(){
	clear();
	cout << "------课程信息查询-----"	<< endl;
	printTitleToStream(cout);
	for(vector<Course>::iterator i=courseList.begin();i!=courseList.end();i++){
		recordToStream(cout,i,true);
	}
	goPrevious();
	return true;
	
}

//修改课程信息 
bool Course::update(){
	int *selectList;//已选择的课程列表, 如果选中则为1 
	int courseTotal;//可选课程总数量
	int line=0;//行下标 
	vector<Course>::iterator i;//课程遍历迭代器 
    
    //初始化 
    vector<int> unchangableList;//可删课程列表
    for(i=courseList.begin();i!=courseList.end();i++){
    	if(0 != i->studentNumber){
    		unchangableList.push_back(i->courseId);
		}
	}
    
	courseTotal = courseList.size() - unchangableList.size();//可退课程总数量
	if(0 == courseTotal){
		clear();
		cout << "目前没有可以修改的课程" << endl;
		goPrevious(); 
		return false;
	}

	selectList = new int[courseTotal];
    for(int i=0;i<courseTotal;i++){
    	selectList[i] = 0;
	}
	
	if(!getSelection("修改无人选择的课程信息",unchangableList,selectList,courseTotal,false,true)){
		free(selectList);
		return false;
	}
	
	if(checkAllZero(selectList,courseTotal)){
		cout << "您未做选择" << endl;
		goPrevious();
		return false;
	}
	
    //确认选课结果并删除 
    cout << "以下课程待修改"  << endl;
    Course::printTitleToStream(cout);
    for(i=Course::courseList.begin(),line=0;i!=Course::courseList.end();i++){
    	//跳过不可修改的课程 
		if(checkExist(unchangableList,i->courseId)){
			continue;
		}
		if(1 == selectList[line]){
			recordToStream(cout,i,true);
			changeInfo(i); 
		}
    	line++;
	}

    free(selectList);
	goPrevious(); 
	return true;
}

//修改课程信息 
bool Course::changeInfo(vector<Course>::iterator &it){
	char confirm = 'y';
	int id,capacity,roomId;
	string name,teacherAccount;
	float price;


	cout << "请输入信息" << endl;
	
	while('y' == confirm || 'Y' == confirm){
		cout<<"课程编号:";
		cin >> id;
		if(!isInputOk()){
			continue;
		}
		
		Course* c= getElementById(id);
		if(!c){
			cout << "该编号已存在！请重新选择" << endl;
			cout << "是否继续?Y/N" << endl;
			cin >> confirm;
			continue;
		}
		break;
	}
	if('y' != confirm && 'Y' != confirm){
		return false;
	}
	


	while('y' == confirm || 'Y' == confirm){
		cout << "课程名称:" ;
		cin >> name;
		
		vector<Course>::iterator i;
		for(i=Course::courseList.begin();i!=Course::courseList.end();++i){
			if(i->courseName == name){
				cout << "该名称已存在！请重新选择" << endl;
				break;
			}
		}
		if(i != Course::courseList.end()){
			cout << "是否继续?Y/N" << endl;
			cin >> confirm;
			continue;
		}
		break;
	}
	if('y' != confirm && 'Y' != confirm){
		return false;
	}
	
	while('y' == confirm || 'Y' == confirm){
		cout << "课程价格";
		cin >> price;
		if(price < 0 || price > Global::COURSE_PRICE_MAX){
			cout << "课程价格需要在合理范围(0--"<< Global::COURSE_PRICE_MAX <<")，请重新输入:" << endl;
			cout << "是否继续?Y/N" << endl;
			cin >> confirm;
			continue;
		}
		break;
	}
	if('y' != confirm && 'Y' != confirm){
		return false;
	}
	
	while('y' == confirm || 'Y' == confirm){
		cout<<"教师帐号:";
		cin >> teacherAccount;

		if(!Teacher::checkAccountExist(teacherAccount)){
			cout << "该编号不存在！请重新选择" << endl;
			cout << "是否继续?Y/N" << endl;
			cin >> confirm;
			continue;
		}
		break;
	}
	if('y' != confirm && 'Y' != confirm){
		return false;
	}

	while('y' == confirm || 'Y' == confirm){
		cout << "课程人数限额";
		cin >> capacity;
		if(capacity < Global::COURSE_CAPACITY_MIN || capacity > Global::COURSE_CAPACITY_MAX){
			cout << "课程人数限额需要在合理范围("<< Global::COURSE_CAPACITY_MIN <<"--"<< Global::COURSE_CAPACITY_MAX <<")"<<endl;
			cout << "是否继续?Y/N" << endl;
			cin >> confirm;
			continue;
		}
		break;
	}
	if('y' != confirm && 'Y' != confirm){
		return false;
	}
	
	while('y' == confirm || 'Y' == confirm){
		cout<<"教室编号:";
		cin >> roomId;
		if(!isInputOk()){
			continue;
		}
		vector<Classroom>::iterator i;
		if(!Classroom::checkIdExist(roomId,i)){
			cout << "该编号不存在！请重新选择" << endl;
			cout << "是否继续?Y/N" << endl;
			cin >> confirm;
			continue;
		}else if(i->capacity < capacity){
			cout << "该教室仅能容纳" << i->capacity << "人, 请重新选择！" << endl;
			cout << "是否继续?Y/N" << endl;
			cin >> confirm;
			continue;
		}
		break;
	}
	if('y' != confirm && 'Y' != confirm){
		return false;
	}

	it->courseId = id;
	it->courseName = name;
	it->teacherAccount = teacherAccount;
	it->roomId = roomId;
	it->capacity = capacity;
		
	cout << "修改如下" << endl;
	printTitleToStream(cout);
	recordToStream(cout,it,true);
	return true;
}

