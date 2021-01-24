#include<iostream>
#include"identity.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"
#include"globalFile.h"
#include"computerRoom.h"
#include<fstream>
#include"orderFile.h"
#include<string>
#include<stdlib.h>
using namespace std;

//进入管理员子菜单界面
void managerMenu(Identity *&manager);
//进入学生子菜单界面
void studentMenu(Identity *&student);
//进入教师子菜单界面
void teacherMenu(Identity *&teacher);
//登录功能	操作文件名     操作身份类型
void LoginIn(string fileName, int type);


int main(){

	int select = 0;//用户的选择
	while(true){
	//显示界面
	cout << "********************欢迎来到机房预约系统********************" << endl;
	cout << "请输入您的身份:" << endl;
	cout << "************************************************************\n";
	cout << "****                                                     ***\n";
	cout << "****                  1.学生代表                         ***\n";
	cout << "****                                                     ***\n";
	cout << "****                  2.老    师                         ***\n";
	cout << "****                                                     ***\n";
	cout << "****                  3.管 理 员                         ***\n";
	cout << "****                                                     ***\n";
	cout << "****                  0.退    出                         ***\n";
	cout << "****                                                     ***\n";
	cout << "************************************************************\n";
	cout << "请输入您的选择：";
	cin >> select;
	switch(select){
	case 1://学生
		LoginIn(STUDENT_FILE,1);
		break;
	case 2://教师
		LoginIn(TEACHER_FILE,2);
		break;
	case 3: //管理
		LoginIn(ADMIN_FILE,3);
		break;
	case 0: 
		cout << "欢迎下一次使用!" << endl;
		return 0;
		break;
	default:
		cout << "输入有误，请重新选择！" << endl;
	}
	}
	return 0;
}

//进入管理员子菜单界面
void managerMenu(Identity *&manager){
	while(true){
		//父类指针调用管理员子菜单
		manager -> openMenu();
		//将父类指针 转为子类指针，调用子类里其他接口
		Manager* man = (Manager*)manager;
		int select = 0;
		//接受用户选项
		cin >> select;
		//添加账号
		if(select == 1){
			cout << "添加账号" << endl;
			man->addPerson();
		}
		//查看账号
		else if(select == 2){
			cout << "查看账号" << endl;
			man -> showPerson();
		}
		//查看机房
		else if(select == 3){
			cout << "查看机房" << endl;
			man -> showComputer();
		}
		//清空预约
		else if(select == 4){
			cout << "清空预约" << endl;
			man -> cleanFile();
		}
		else{
			delete manager;
			cout << "注销成功" << endl;
			return;
		}
	}
}
//登录功能	操作文件名     操作身份类型
void LoginIn(string fileName, int type){
	//父类指针，用于指向子类对象
	Identity * person = NULL;
	//读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);
	//判断文件是否存在
	if(!ifs.is_open()){
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//准备接受用户的信息
	int id = 0;
	string name;
	string pwd;

	//判断身份
	if(type == 1)//学生
	{
		cout << "请输入您的学号： ";
		cin >> id;
	}
	else if(type == 2)//教师
	{
		cout << "请输入您的职工号： ";
		cin >> id;
	}
	cout << "请输入用户名： " ;
	cin >> name;
	cout << "请输入密码： ";
	cin >> pwd;
	
	//身份验证
	//学生身份
	if(type == 1){
		 //记录从文件中读取的信息 id name pwd
		 int fId;
		 string fName;
		 string fPwd;
		 while(ifs >> fId && ifs >> fName && ifs >> fPwd){
		 	//与用户输入的信息做对比
			if(fId == id && fName == name && fPwd == pwd){
				cout << "学生验证通过，登录成功！" << endl;
				//实例化学生
				person = new Student(id, name, pwd);
				//进入学生身份的子菜单
				studentMenu(person);
				return;
			}
		 }
	}
	//教师身份
	else if(type == 2){
		//记录从文件中读取的信息 id name pwd
		int fId;
		string fName;
		string fPwd;
		while(ifs >> fId && ifs >> fName && ifs >> fPwd){
			//与用户输入的信息对比
			if(fId == id && fName == name && fPwd == pwd){
				cout << "教师验证通过，登录成功！" << endl;
				person = new Teacher(id, name, pwd);
				teacherMenu(person);
				return;
			}
		}
	}
	//管理员身份
	else if(type == 3){
		string fName;
		string fPwd;
		while(ifs >> fName && ifs >> fPwd){
			if(fName == name && fPwd == pwd){
				cout << "管理员验证通过，登录成功！" << endl;
				person = new Manager(name, pwd);
				//进入管理员子菜单界面
				managerMenu(person);
				return;
			}
		}	
	}
	cout << "验证登录失败" << endl;	
	return;
}

//进入学生子菜单界面
void studentMenu(Identity *&student){
	while(true){
		//调用学生子菜单
		student->openMenu();
		//将父类指针转为子类指针
		Student *stu = (Student*)student;
		//由用户输入选择，然后进入相应的接口
		int select = 0;
		cin >> select;
		if(select == 1){//申请预约
			cout << "开始申请预约" << endl;
			stu -> applyOrder();
		}
		else if(select == 2){//查看自身预约
			cout << "查看自身预约中" << endl;
			stu -> showMyOrder();
		}
		else if(select == 3){//查看所有预约
			cout << "查看所有预约中" << endl;
			stu -> showAllorder();
			
		}
		else if(select == 4){//取消预约
			cout << "正在为您取消预约" << endl;
			stu -> cancelOrder();
		}
		else{
			delete student;
			cout << "无此选项，请重新输入" << endl;
			return;
		}
	}	
}

//进入教师子菜单界面
void teacherMenu(Identity *&teacher){
	while(true){
		//调用教师子菜单
		teacher -> openMenu();
		//将父类指针转为子类指针
		Teacher *tea = (Teacher*)teacher;
		//接受教师的选择，然后进入相应的接口
		int select = 0;
		cin >> select;
		if(select == 1){
			cout << "查看所有预约" << endl;
			tea -> showAllOrder();
		}
		else if(select == 2){
			cout << "审核预约" << endl;
			tea -> validOrder();
		}
		else{
			delete teacher;
			cout << "注销成功" << endl;
			return;
		}
	}
}	

