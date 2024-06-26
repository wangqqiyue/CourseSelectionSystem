#ifndef INCLUDE_GLOBAL
#include "global.h"
#endif

#ifndef INCLUDE_TEACHER
#include "teacher.h"
#endif

#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

#ifndef INCLUDE_ADMINISTATOR
#include "administrator.h"
#endif

const int Global::LOGIN_RETRY_MAX=5;
const int Global::PRINT_WIDTH=12;
const int Global::PRINT_LONG_WIDTH=24;

const int Global::TEACHER_NUMBER_MAX=100;
const int Global::ROOM_NUMBER_MAX=100;
const int Global::COURSE_NUMBER_MAX=100;
const int Global::COURSE_PRICE_MAX=3000;
const int Global::COURSE_CAPACITY_MAX=200;
const int Global::COURSE_CAPACITY_MIN=20;
const int Global::ROOM_CAPACITY_MAX=500;
const int Global::ROOM_CAPACITY_MIN=40;
const int Global::ID_LENGTH=18;
const int Global::TEL_LENGTH=11;
//可上课时间段 
const int Global::COURSE_HOURS_LENGTH=8;
	
const char *Global::roleStr[]={"管理员","学生","老师","返回上一级"};
const char *Global::loginStr[]={"登陆","返回上一级"};
const char *Global::stuLoginStr[]={"注册","登陆","返回上一级"};
const char *Global::operationStr[]={"新增","删除","修改","查询","返回上一级"};
const char *Global::mgmtStr[]={"管理教师信息","管理教室信息","管理课程信息","返回上一级"};
const char *Global::stuFuncStr[]={"查看已选课程","查看所有课程","选择新课程","退选未支付的课程","支付订单","返回上一级"};
const char *Global::titleStr="培训中心管理系统";
const char *Global::teacherFuncStr[] = {"查看名下课程", "查看课程学生名单","返回上一级"}; 
const char *Global::greetingStr[] = {"继续进入系统", "查看帮助信息", "退出系统"};
const char *Global::aboutInfoFile="about.txt";
//上课时段字符串 
const char *Global::courseHourStr[] = {"6:00-8:00", "8:00-10:00", "10:00-12:00", "12:00-14:00", "14:00-16:00", "16:00-18:00", "18:00-20:00", "20:00-22:00","取消选择"};

//清空控制台
void clear(){
	system("cls");
}

//设置控制台颜色 
void setConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

//返回上一级 
void goPrevious(){
	cout << "按任意键返回上一级" << endl;
	while(true){	
		if (_kbhit()){
			_getch();
			return;
		}
	}
} 

//任意键继续 
void goContinue(){
	cout << "按任意键继续" << endl;
	while(true){	
		if (_kbhit()){
			_getch();
			return;
		}
	}
} 

//检查输入是否合规 
bool isInputOk(){
	//当我们在输入的时候，如果是整形变量int，我们输入char类型的字符，此时failbit的值会由0变为1
	if(cin.fail()){
		//输入的字符会卡在输入缓冲区导致后面无法进行输入操作
		cout << "请输入合法字符!" << endl;
		
		//我们首先使用cin>>clear()将falibit置为0让输入流可以正常工作，然后使ignore()取出缓冲区的字符，让下一次的输入可以正常运行。
		cin.clear();
		cin.ignore();
		return false;
	}
	return true;
}

//获取用户输入的选项 
int getChoice(const char* promptStr, const char **choiceStr, const int choiceMax){
	char choice = -1;
	//含choiceMax，用户可以选择退出/返回到上一级 
	while(choice > choiceMax || choice < 0){
		choice = -1;
		cout << promptStr <<endl;
		for(int i=0;i<choiceMax;i++){
			cout << i << ". " << choiceStr[i] << endl;
		}
		cout << "[Esc] "  << choiceStr[choiceMax] << endl;
		
		while(true){	
			if (_kbhit()){
				choice = _getch();
				if(choice < '0' + choiceMax && choice >= '0'){
					choice -= '0';
					break;
				}else if(choice == 27){//esc的ASCII码27
					choice =  choiceMax;
					break;
				}
			}
		}
	}
	
	return choice;
}

//设置密码 
string setPassword() {
    string password, comfirmPasswd;
    do {
        cout << "请输入密码：";
        cin >> password;

        cout << "请再次输入以确认密码：";
        cin >> comfirmPasswd;

        if (password != comfirmPasswd) {
            cout << "两次密码不一致，请重新输入！" << endl;
        }
    } while (password != comfirmPasswd);
    return password;
}

//登陆
bool login(Global::Role role){
	string inputAccount;
	string inputPasswd;
	vector<Student>::iterator is;
	vector<Teacher>::iterator it;
	int loginChoice = -1;
	char confirm = 'y';
	
	clear();
	cout << "------"<< Global::roleStr[role] <<"登陆-----" << endl;
	if(Global::STUDENT == role){
		loginChoice = getChoice("", Global::stuLoginStr, Global::STU_LOGIN_MAX);
		if(Global::STU_LOGIN_MAX == loginChoice){
			return false;
		}else if(Global::STU_SIGNUP == loginChoice){
			return Student::createAccount();
		}
	}else{
		loginChoice = getChoice("", Global::loginStr, Global::LOGIN_MAX);
		if(Global::LOGIN_MAX == loginChoice){
			return false;
		}
	}
	int i;
	for(i=0;i<Global::LOGIN_RETRY_MAX && ('y' == confirm || 'Y' == confirm);i++){
		cout << "请输入账号名称:" ;
		cin >> inputAccount;		
		
		if(Global::ADMINISTRATOR == role){	
			if(inputAccount != Administrator::adminAccount){
				cout << "账号不存在!请重新输入"  << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> confirm;
				continue;
			}
		}else if(Global::TEACHER == role){
			if(!Teacher::checkAccountExist(inputAccount,it)){
				cout << "账号不存在!请重新输入"  << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> confirm;
				continue;
			}
			
		}else{
			if(!Student::checkAccountExist(inputAccount,is)){
				cout << "账号不存在!请重新输入"  << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> confirm;
				continue;
			}
		}

		cout << "请输入密码:" ;
		cin >> inputPasswd;
		
		if(Global::ADMINISTRATOR == role){	
			if(inputPasswd != Administrator::password){
			
				cout << "密码错误!请重新输入"  << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> confirm;
				continue;
			}
		}else if(Global::TEACHER == role){
			if(inputPasswd != it->password){
				cout << "密码错误!请重新输入"  << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> confirm;
				continue;
			}
			//当前登陆账号 
			Teacher::login_account = inputAccount;
		}else{
			if(inputPasswd != is->password){
				cout << "密码错误!请重新输入"  << endl;
				cout << "是否继续?Y/N" << endl;
				cin >> confirm;
				continue;
			}
			Student::login_account =  inputAccount;
		}
		
		cout << "登陆成功" << endl;
		return true;
	}
	if(Global::LOGIN_RETRY_MAX == i){
		cout << "登陆次数超过" << Global::LOGIN_RETRY_MAX << endl; 
	}
	goPrevious();
	return false;
}

 bool checkAllZero(int *selectList, int total){
 	for(int i=0;i<total;i++){
 		if(selectList[i]){
 			return false;
		 }
	}
	return true;
 }
