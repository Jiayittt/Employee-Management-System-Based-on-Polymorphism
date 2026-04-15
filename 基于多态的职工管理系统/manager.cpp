#include "manager.h"

Manager::Manager(int id, string name, int deptId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptId = deptId;
}

void Manager::showInfo()
{
	cout << "员工的编号：" << this->m_id << endl
		<< " \t员工的姓名：" << this->m_name << endl
		<< " \t员工的岗位：" << this->getDeptName() << endl
		<< " \t员工的职能： 服从经理的安排" << endl;
}

string Manager::getDeptName()
{
	return string("经理");
}
