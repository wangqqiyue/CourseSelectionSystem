#ifndef INCLUDE_CLASSROOM
#include "classroom.h"
#endif

#ifndef INCLUDE_COURSE
#include "course.h"
#endif

#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif


#ifndef INCLUDE_FSTREAM
#include <fstream>
#define INCLUDE_FSTREAM
#endif


#ifndef INCLUDE_SSTREAM
#include <sstream>
#define INCLUDE_SSTREAM
#endif


#ifndef INCLUDE_CONIO
#include <conio.h>
#define INCLUDE_CONIO
#endif


#ifndef INCLUDE_WINDOWS
#include <windows.h>
#define INCLUDE_WINDOWS
#endif 


/*-----------------Classroom 定义实现-------------------------------------*/ 

vector<Classroom> Classroom::roomList;


bool Classroom::printTitleToStream(ostream& out){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	out << setw(Global::PRINT_WIDTH)<<"教室编号" << setw(Global::PRINT_LONG_WIDTH) << "教室名称" << setw(Global::PRINT_WIDTH) << "教室容量"<< endl;
	return true;
}

//既可以在函数声明中，也可以在函数定义中声明缺省参数，但不能既在函数声明中又在函数定义中同时声明缺省参数。
//传入流对象，迭代器, 是否只打印一条记录 
bool Classroom::recordToStream(ostream& out, vector<Classroom>::iterator firstRecord, bool onlyOne){ 
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}

	if(!onlyOne){
		printTitleToStream(out);	
	}		
	
	for(vector<Classroom>::iterator i=Classroom::roomList.begin();i!=Classroom::roomList.end();i++){
		if(onlyOne){
			i=firstRecord;
		}
		out <<  setw(Global::PRINT_WIDTH)<<i->roomId << setw(Global::PRINT_LONG_WIDTH) <<	i->roomName << setw(Global::PRINT_WIDTH)  << i->capacity << endl;
		if(onlyOne){
			break;
		}	
	}

	return true;
}


//根据id获取教室名称 
Classroom* Classroom::getElementById(int id){
	for(vector<Classroom>::iterator i=Classroom::roomList.begin();i!=Classroom::roomList.end();i++){
		if(i->roomId == id){
			return const_cast<Classroom*>(&(*i));
		}
	}
}


const char* Classroom::dataFile = "classroomsInfo.txt"; 

bool Classroom::storeInfo(){
	bool result = true;
	ofstream out;
	//加载管理员账号密码
	out.open(dataFile,ios::out);
	if(!Classroom::recordToStream(out,roomList.begin())){
		result= false;
	}

	out.close();
	return result;
}

bool Classroom::loadInfo(){
	ifstream in;
	string temp;
	
	//加载管理员账号密码
	in.open(dataFile,ios::in);
	getline(in,temp);
	while(getline(in,temp)){
		int roomId,capacity;
		string roomName;
		
		stringstream ss(temp);
		ss >> roomId;
		ss >> roomName;
		ss >> capacity;
		
		Classroom cr(roomId,roomName,capacity);
		Classroom::roomList.push_back(cr);
	}		
	in.close();
}

bool Classroom::checkIdExist(int id,vector<Classroom>::iterator &i){
	for(i=Classroom::roomList.begin();i!=roomList.end();i++){
		if(i->roomId == id){
			return true;
		}
	}
	return false;
}


//选择菜单  idList是一个课程id名单表 , selectList 是选择表, classroomTotal 是可选项总数, isInclusion表示是包含idList中的课程，还是跳过 
bool Classroom::getSelection(const vector<int>& idList, int* selectList, const int& classroomTotal,bool isInclusion){
		
	static bool firstPrint = true;
	int currentLine = 0;
	int line = 0;
	vector<Classroom>::iterator i;
	int selectTotal = 0;
	
	while (true) {
        if (_kbhit()|| firstPrint) {

	
        	clear();
        	//标题和规则说明 
			cout << "----------------删除无人使用的教室----------------" << endl;
			
			//显示当前状态 
			float priceTotal = 0;
			cout << "选择状态" << endl;
			cout << "已选教室数量:" << selectTotal << "(";

            for(i=roomList.begin(),line=0;i!=roomList.end();i++){
            	
            	if(isInclusion){//跳过非idList里的项目 
            		if(!checkExist(idList,i->roomId)){
						continue;
					}
				}else{//跳过idList里的项目 
					if(checkExist(idList,i->roomId)){
						continue;
					}
				}
				
				if(1 == selectList[line]){
					cout << i->roomName << " ";
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
	                    currentLine += classroomTotal;
	                }
					
	            } else if (ch == 80) { // 下箭头键
	                currentLine++;
	                currentLine%=classroomTotal;
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

			Classroom::printTitleToStream(cout);
			//遍历所有课程行 
            for(i=roomList.begin(),line=0,selectTotal=0;i!=roomList.end();i++){
            	            	
            	if(isInclusion){//跳过非idList里的项目 
            		if(!checkExist(idList,i->roomId)){
						continue;
					}
				}else{//跳过idList里的项目 
					if(checkExist(idList,i->roomId)){
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

bool Classroom::del(){
	int *selectList;//已选择的课程列表, 如果选中则为1 
	int classroomTotal;//可选课程总数量
	int line=0;//行下标 
	vector<Course>::iterator i;//课程遍历迭代器 
    
    //初始化 
    vector<int> undeletableList;//不可删课程列表
    for(i=Course::courseList.begin();i!=Course::courseList.end();i++){
    	//如果课程人数不为0，且该教室未加入到不可删除列表，则加入 
    	if(0 != i->studentNumber){
    		if(!checkExist(undeletableList,i->roomId)){
    			undeletableList.push_back(i->roomId);
			}
		}
	}
    
	classroomTotal = roomList.size() - undeletableList.size();//可删除教室的总数量
	if(0 == classroomTotal){
		clear();
		cout << "目前没有可以删除的教室" << endl;
		goPrevious(); 
		return false;
	}

	selectList = new int[classroomTotal];
    for(int i=0;i<classroomTotal;i++){
    	selectList[i] = 0;
	}
	
	if(!getSelection(undeletableList,selectList,classroomTotal,false)){
		free(selectList);
		return false;
	}
	
	
	if(checkAllZero(selectList,classroomTotal)){
		cout << "您未做选择" << endl;
		goPrevious();
		return false;
	}
	
    //确认选课结果并删除 
    cout << "以下教室已删除"  << endl;
    printTitleToStream(cout);
    vector<Classroom>::iterator it;
    for(it=roomList.begin(),line=0;it!=roomList.end();it++){
    	//跳过不可退的课程 
		if(checkExist(undeletableList,it->roomId)){
			continue;
		}
		if(1 == selectList[line]){
			recordToStream(cout,it,true);
			it = roomList.erase(it);// erase之后，令当前迭代器指向其后继。否则迭代器失效,会报错
			it--;
		}
    	line++;
	}

    free(selectList);
	goPrevious(); 
	return true;
}

//查询教室数据 
bool Classroom::retrieve(){
	clear();
	cout << "------教室信息查询-----"	<< endl;
	recordToStream(cout,Classroom::roomList.begin());
	goPrevious();
	return true;
	
}

/*新增教室数据 
需要判断新增数据是否有重复,新增后不超过教室总数上限 
*/
bool Classroom::create(){
	int id,capacity;
	string name;

	char comfirm = 'y';
	clear();
	cout << "------新增教室信息-----"	<< endl;
	
	while('y' == comfirm || 'Y' == comfirm){
		if(Classroom::roomList.size() >= Global::ROOM_NUMBER_MAX){
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
		for(i=Classroom::roomList.begin();i!=Classroom::roomList.end();++i){
			if(i->roomId == id){
				cout << "该编号已存在！请重新选择" << endl;
				break;
			}
		}
		if(i != Classroom::roomList.end()){
			cout << "是否继续?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "教室名称:" ;
		cin >> name;
		for(i=Classroom::roomList.begin();i!=Classroom::roomList.end();++i){
			if(i->roomName == name){
				cout << "该名称已存在！请重新选择" << endl;
				break;
			}
		}
		if(i != Classroom::roomList.end()){
			cout << "是否继续?Y/N" << endl;
			cin >> comfirm;
			continue;
		}
		
		cout << "教室容量";
		cin >> capacity;
		
		Classroom cr(id,name,capacity);
		Classroom::roomList.push_back(cr);
		
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
