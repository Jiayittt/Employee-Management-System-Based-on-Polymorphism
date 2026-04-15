#pragma once
#include <iostream>
#include <string>
using namespace std;
class Worker 
{
public:
	//员工编号
	int m_id;
	//员工姓名
	string m_name;
	//岗位编号
	int m_deptId;

	//展示个人信息
	virtual void showInfo() = 0;

	//获取岗位名称
	virtual string getDeptName() = 0;
};