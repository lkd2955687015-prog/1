#include<iostream>
using namespace std;
#include"employee.h"

Employee::Employee(int id, string name, int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = did;
}

void Employee::showPerson()
{
	cout << "职工编号: " << this->m_id
		<< "  职工姓名: " << this->m_name
		<< "  职工岗位: " << getdeptname()
		<< "  岗位职责：完成经理交给的任务" << endl;
}
string Employee::getdeptname()
{
	return string("员工");
}
