#pragma once
#include"orderFile.h"
#include"identity.h"
#include"globalFile.h"
#include"computerRoom.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;
//老师类
class Teacher : public Identity{
public:
	//默认构造
	Teacher();
	//有参构造  员工编号  姓名  密码
	Teacher(int empId, string name, string pwd);
	//菜单界面
	virtual void openMenu();
	//查看预约
	void showAllOrder();
	//审核预约
	void validOrder();
	//教师编号
	int m_empId;

};
