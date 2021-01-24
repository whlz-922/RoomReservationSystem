#include"orderFile.h"

//构造函数
OrderFile::OrderFile(){
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);
	
	//记录机房的基本信息：日期 时间段 学生ID 学生姓名 机房ID 状态
	string date;
	string interval;
	string studentId;
	string studentName;
	string roomId;
	string status;
	
	this->m_size = 0;//记录条数

	while(ifs >> date && ifs >> interval && ifs >> studentId && ifs >> studentName && ifs 
			>> roomId && ifs >> status){
		string key;
		string value;
		map<string, string> m;
		
		//可以封装成函数，减少代码量
		int pos = date.find(":");//4
		if(pos != -1){
			key = date.substr(0,pos);
			value = date.substr(pos+1,date.size()-pos-1);
			m.insert(make_pair(key, value));
		}

		pos = interval.find(":");
		if(pos != -1){
			key = interval.substr(0,pos);
			value = interval.substr(pos+1,interval.size()-pos-1);
			m.insert(make_pair(key, value));
		}

		pos = studentId.find(":");
		if(pos != -1){
			key = studentId.substr(0,pos);
			value = studentId.substr(pos+1, studentId.size()-pos-1);
			m.insert(make_pair(key, value));
		}
		pos = studentName.find(":");
		if(pos != -1){
			key = studentName.substr(0,pos);
			value = studentName.substr(pos+1,studentName.size()-pos-1);
			m.insert(make_pair(key,value));
		}
		pos = roomId.find(":");
		if(pos != -1){
			key = roomId.substr(0,pos);
			value = roomId.substr(pos,roomId.size()-pos-1);
			m.insert(make_pair(key,value));
		}
		pos = status.find(":");
		if(pos != -1){
			key = status.substr(0,pos);
			value = status.substr(pos+1,status.size()-pos-1);
			m.insert(make_pair(key,value));
		}
		m_orderData.insert(make_pair(this->m_size,m));
		this->m_size++;
	}

	ifs.close();

}

//更新预约记录
void OrderFile::updateOrder(){
	if(this->m_size == 0){
		return;//预约记录为0，直接return
	}
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out | ios::trunc);//删了重写
	for(int i = 0; i < this->m_size; i++){
		ofs << "date:" << this->m_orderData[i]["date"] << " ";
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "studentId:" << this->m_orderData[i]["studentId"] << " ";
		ofs << "studentName:" << this->m_orderData[i]["studentName"] << " ";
		ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] << endl;
	}
	ofs.close();
}

