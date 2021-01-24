#include"/home/wacky/Code/RoomReservationSystem/manager.h"

//默认构造
Manager::Manager(){}
//有参构造
Manager::Manager(string name, string pwd){
	this -> m_name = name;
	this -> m_pwd = pwd;
	//初始化容器 获取到所有文件中学生和老师的信息
	this -> initVector();
	//初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerInfo com;
	while(ifs >> com.m_comId && ifs >> com.m_max){
		vCom.push_back(com);
	}
	ifs.close();
	cout << "当前机房的数量： " << vCom.size() << endl;
}
//菜单界面
void Manager::openMenu(){
	cout << "欢迎管理员：" << this->m_name << "登录！" << endl;
	cout << "******************************************" << endl;
	cout << "***                                    ***" << endl;
	cout << "***           1.添加账号               ***" << endl;
	cout << "***                                    ***" << endl;
	cout << "***           2.查看账号               ***" << endl;
	cout << "***                                    ***" << endl;
	cout << "***           3.查看机房               ***" << endl;
	cout << "***                                    ***" << endl;
	cout << "***           4.清空预约               ***" << endl;
	cout << "***                                    ***" << endl;
	cout << "***           0.注销登录               ***" << endl;
	cout << "***                                    ***" << endl;
	cout << "******************************************" << endl;
	cout << "请选择您的操作： " << endl;
}
//添加账号
void Manager::addPerson(){
	cout << "请输入添加账号的类型:" << endl;
	cout << "1.添加学生" << endl;
	cout << "2.添加老师" << endl;
	string fileName;
	string tip;
	string errorTip;//重复错误提示
	ofstream ofs;	
	int select = 0;
	cin >> select;
	//添加学生账号
	if(select == 1){
		fileName = STUDENT_FILE;
		tip = "请输入学号： ";
		errorTip = "学号重复，请重新输入";
	}
	//添加职工编号
	else{
		fileName = TEACHER_FILE;
		tip = "请输入职工号： ";
		errorTip = "职工号重复，请重新输入";
	}
	//利用追加的方式写文件
	ofs.open(fileName, ios::out | ios::app);
	//由用户输入信息 学生或者老师
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	while(true){
		cin >> id;
		bool ret = checkRepeat(id, select);
		if(ret){//有重复
			cout << errorTip << endl;
		}
		else{
			break;
		}
	}
	cout << "请输入姓名： " << endl;
	cin >> name;
	cout << "请输入初始密码: " << endl;
	cin >> pwd;

	//向文件中添加数据
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功!" <<endl; 
	ofs.close();
	//调用初始化容器的接口，重新获取文件中的数据
	this->initVector();
	
}
void printStudent(Student &s){
	cout << "学号： " << s.m_id << " 姓名： " << s.m_name << "密码： " << s.m_pwd << endl;
}
void printTeacher(Teacher &t){
	cout << "职工号： " << t.m_empId << " 姓名： " << t.m_name << " 密码： " << t.m_pwd << endl;
}
//查看账号
void Manager::showPerson(){
	//由用户选择想要查看的对象 老师或者学生
	int select = 0;
	cout << "请选择查看对象： " << endl;
	cout << "1.查看所有学生 " << endl;
	cout << "2.查看所有老师 " << endl;
	cin >> select;
	if(select == 1){
		cout << "所有学生信息如下： " << endl;
		for_each(vStu.begin(),vStu.end(),printStudent);
	}
	else{
		cout << "所有老师信息如下:  " << endl;
		for_each(vTea.begin(),vTea.end(),printTeacher);
	}
}

//查看机房信息
void Manager::showComputer(){
	cout << "机房信息如下： " << endl;
	for(vector<ComputerInfo>::iterator it = vCom.begin(); it != vCom.end(); it++){
		cout << "机房编号： " << it -> m_comId << " 机房最大容量： " << it -> m_max << endl;
	}
}
//清空预约
void Manager::cleanFile(){
	//打开ORDER_FILE文件，然后清空重新创建ORDER_FILE文件
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "清空成功！"<< endl;
}

//初始化容器
void Manager::initVector(){
	vStu.clear();
	vTea.clear();
	//读取文件信息
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if(!ifs.is_open()){
		cout << "文件读取失败" << endl;
		return;
	}

	Student s;
	while(ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_pwd){
		vStu.push_back(s);
	}
	cout << "当前学生数量为：" << vStu.size() << endl;
	ifs.close();

	ifs.open(TEACHER_FILE, ios::in);
	if(!ifs.is_open()){
		cout << "文件读取失败" << endl;
		return;
	}
	Teacher t;
	while(ifs >> t.m_empId && ifs >> t.m_name && ifs >> m_pwd){
		vTea.push_back(t);
	}
	cout << "当前教师数量为：" << vTea.size() << endl;
	ifs.close();

}
//去重函数
bool Manager::checkRepeat(int id, int type){
	//学生
	if(type == 1){
		for(vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++){
			if(id == it->m_id){	
				return true;
			}
		}
	}
	//教师
	else{
		for(vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++){
			if(id == it->m_empId){
				return true;
			}
		}
	}
	return false;
}
