#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

#ifndef INCLUDE_RECORD_PROCESS
#include "recordProcess.h" 
#endif

vector<Student> studentList;

//函数指针数组的初始化 
bool (*Student::stuFuncs[Global::STU_FUNC_MAX])() = {NULL,courseInfoRetrieve,selectCourse,NULL,NULL};
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
void Student::createAccount(){
	string account,name,id,tel,password,comfirmPasswd;
	char comfirm='y';
	
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
				break;
		}
		
		password = setPassword();	
			
		Student s = Student(account,id,name,tel,password);
		studentList.push_back(s);
		
		cout << "已注册账号如下："	<< endl;
		Student::recordToStream(cout, studentList.end() - 1,true);
		Student::login_account =  account;
		break; 
	}
	cout << "按任意键返回上一级" << endl;
	cin.ignore();
	getchar();
}

bool Student::recordToStream(ostream& out, vector<Student>::iterator firstRecord, bool onlyOne){
	//非法流 返回false 
	if(!out){
		cerr << "非法的流" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_LONG_WIDTH)<<"账号" << setw(Global::PRINT_LONG_WIDTH) << "姓名" << setw(Global::PRINT_LONG_WIDTH) << "身份证号" << setw(Global::PRINT_LONG_WIDTH) << "手机号" << setw(Global::PRINT_LONG_WIDTH) << "密码"<< endl;
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

