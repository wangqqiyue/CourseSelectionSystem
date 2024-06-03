#ifndef INCLUDE_STUDENT
#include "student.h"
#endif

vector<Student> studentList;

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

//ѧ�������������� 
void Student::process(){
	while(login(Global::STUDENT)){
		clear();
		cout << "��½�ɹ�" << endl;
		system("pause");

	}
}


//����ѧ���˺� 
void Student::createAccount(){
	string account,name,id,tel,password,comfirmPasswd;
	char comfirm='y';
	
	clear();
	cout << "------ע��ѧ���˺�-----" << endl;
	while('y' == comfirm || 'Y' == comfirm){
		while('y' == comfirm || 'Y' == comfirm){
			cout << "�������˺�����:" ;
			cin >> account;

			if(checkAccountExist(account)){
				cout << "�˺��Ѵ���!����������"  << endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}
			break;
		}
		if('y' != comfirm && 'Y' != comfirm){
				break;
		}
	
		cout << "������������" ;
		cin >> name;
	
		while('y' == comfirm || 'Y' == comfirm){
			cout << "���������֤�ţ�" ;
			cin >> id;
			if(Global::ID_LENGTH != id.length()){
				cout << "���֤�ų��ȷǷ�!����������"  << endl;
				cout << "�Ƿ����?Y/N" << endl;
				cin >> comfirm;
				continue;
			}
			break;
		}
		if('y' != comfirm && 'Y' != comfirm){
				break;
		}
		
		while('y' == comfirm || 'Y' == comfirm){
			cout << "�������ֻ���:";
			cin >> tel;
			if(Global::TEL_LENGTH != tel.length()){
				cout << "�ֻ��ų��ȷǷ�!����������"  << endl;
				cout << "�Ƿ����?Y/N" << endl;
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
		
		cout << "��ע���˺����£�"	<< endl;
		Student::recordToStream(cout, studentList.end() - 1,true);
		break; 
	}
	cout << "�������������һ��" << endl;
	cin.ignore();
	getchar();
}

bool Student::recordToStream(ostream& out, vector<Student>::iterator firstRecord, bool onlyOne){
	//�Ƿ��� ����false 
	if(!out){
		cerr << "�Ƿ�����" << endl;
		return false;
	}
	
	out << setw(Global::PRINT_LONG_WIDTH)<<"�˺�" << setw(Global::PRINT_LONG_WIDTH) << "����" << setw(Global::PRINT_LONG_WIDTH) << "���֤��" << setw(Global::PRINT_LONG_WIDTH) << "�ֻ���" << setw(Global::PRINT_LONG_WIDTH) << "����"<< endl;
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

