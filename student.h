#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"computerRoom.h"
#include<fstream>
#include"globalFile.h"
#include"orderFile.h"
using namespace std;
#include "identity.h"
//学生类
class Student : public Identity{
public:
	//默认构造
	Student();
	//有参构造
	Student(int id, string name, string pwd);
	//菜单界面
	virtual void openMenu();
	//申请预约
	void applyOrder();
	//查看预约进程
	void showMyOrder();
	//查看所有预约
	void showAllorder();
	//取消预约
	void cancelOrder();
	//学号
	int m_id;
	//机房容器
	vector<ComputerInfo> vCom;
};
