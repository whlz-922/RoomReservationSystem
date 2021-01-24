#include"student.h"
//默认构造
Student::Student(){}

//有参构造
Student::Student(int id, string name, string pwd){
	this->m_id = id;
	this->m_name = name;
	this->m_pwd = pwd;
	//初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE,ios::in);
	ComputerInfo com;
	while(ifs >> com.m_comId && ifs >> com.m_max){
		vCom.push_back(com);
	}
	ifs.close();
}

//菜单界面
void Student::openMenu(){
	cout << "欢迎学生代表： " << this->m_name << "登录！" << endl;
	cout << "********************************************" << endl;
	cout << "***                                      ***" << endl;
	cout << "***           1.申请预约                 ***" << endl;
	cout << "***                                      ***" << endl;
	cout << "***           2.查看自身预约             ***" << endl;
	cout << "***                                      ***" << endl;
	cout << "***           3.查看所有预约             ***" << endl;
	cout << "***                                      ***" << endl;
	cout << "***           4.取消预约                 ***" << endl;
	cout << "***                                      ***" << endl;
	cout << "***           0.注销登录                 ***" << endl;
	cout << "***                                      ***" << endl;
	cout << "********************************************" << endl;
	cout << "请输入您想要执行的操作： ";
}

//申请预约
void Student::applyOrder(){
	cout << "机房开放时间为周一至周五" << endl;
	cout << "请输入申请预约的时间： " << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;
	
	int date = 0;//日期
	int interval = 0;//时间段
	int room = 0;//机房编号
	while(true){
		cin >> date;
		if(date >= 1 && date <= 5){
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "请输入申请预约的时间段：" << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;
	
	while(true){
		cin >> interval;
		if(interval >= 1 && interval <= 2) {
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "请输入申请预约的机房编号: " << endl;
	for(int i = 0; i < vCom.size(); i++){
	cout << vCom[i].m_comId << "号机房容量为： " << vCom[i].m_max << endl;
	}
	while(true){
		cin >> room;
		if(room >= 1 && room <= vCom.size()) {
			break;
		}
		cout << "输入有误，请重新输入" << endl; 
	}
	cout << "预约成功！审核中" << endl;
	ofstream ofs;
	ofs.open(ORDER_FILE,ios::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "studentId:" << this->m_id << " ";
	ofs << "studentName:" << this->m_name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;
	ofs.close();
}

//查看预约
void Student::showMyOrder(){
	OrderFile of;
	if(of.m_size == 0){
		//无预约记录
		cout << "无预约记录！" << endl;
		return;
	}
	for(int i = 0; i < of.m_size; i++){
		if(this->m_id == atoi(of.m_orderData[i]["studentId"].c_str())){
		//找到自身预约
			cout << "预约日期： 周" << of.m_orderData[i]["date"];
			cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房号：" << of.m_orderData[i]["roomId"];
			string status = "状态：";
			if(of.m_orderData[i]["status"] == "1"){
				status += "审核中";
			}
			else if(of.m_orderData[i]["status"] == "2"){
				status += "预约成功";
			}
			else if(of.m_orderData[i]["status"] == "-1"){
				status += "预约失败";
			}
			else{
				status += "预约取消";
			}
			cout << status << endl;
		}
	}
	
}
//查看所有预约
void Student::showAllorder(){
	OrderFile of;
	if(of.m_size == 0){
		cout << "暂无预约！" << endl;
		return;
	}
	for(int i = 0; i < of.m_size; i++){
		cout << i+1 << "预约日期： 周" << of.m_orderData[i]["date"];
		cout << " 时间段： " << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << " 学号： " << of.m_orderData[i]["studentId"];
		cout << " 姓名： " << of.m_orderData[i]["studentName"];
		cout << " 机房号： " << of.m_orderData[i]["roomId"];
		string status = "状态：";
		if(of.m_orderData[i]["status"] == "1"){
			status += "预约中";
		}
		else if(of.m_orderData[i]["status"] == "2"){
			status += "预约成功";
		}
		else if(of.m_orderData[i]["status"] == "-1"){
			status += "预约失败";
		}
		else{
			status += "预约取消";
		}
		cout << status << endl;
	}
}

//取消预约
void Student::cancelOrder(){
	OrderFile of;
	if(of.m_size == 0){
		cout << "无预约记录" << endl;
		return;
	}
	cout << "审核中或者预约成功的记录可以取消，以下是可取消的记录：" << endl;
	int index = 1;
	vector<int> v;//记录最大容器中的下标编号
	for(int i = 0; i < of.m_size; i++){
		//先判断是否为自身学号
		if(this->m_id == atoi(of.m_orderData[i]["studentId"].c_str())){
			//再筛选状态
			if(of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2"){
				v.push_back(i);
				cout << index++ << "、";
				cout << "预约日期：周" << of.m_orderData[i]["date"];
				cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午": "下午");
				string status = "状态：";
				if(of.m_orderData[i]["status"] == "1"){
					status += "审核中";
				}
				else if(of.m_orderData[i]["status"] == "2"){
					status += "预约成功";
				}
				cout << status << endl;
			}
		}
	}
	cout << "请输入取消的记录，0代表返回" << endl;
	int select = 0;
	while(true){
		cin >> select;
		if(select >= 0 && select <= v.size()){
			if(select == 0){
				break;
			}
			else{
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "已取消预约" << endl;
				break;
			}
		}
		else{
			cout << "输入有误，请重新输入" << endl;
		}
	}
}

