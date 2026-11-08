#include"boss.h"

boss::boss(int id, string name, int did)
{
	this->m_name = name;
	this->m_deptid = did;
	this->m_id = id;
}

void boss::showPerson()
{
	cout << "老板编号: " << this->m_id
		<< "  老板姓名: " << this->m_name
		<< "  老板岗位: " << getdeptname()
		<< "  岗位职责：给经理交代任务" << endl;
 }

string boss::getdeptname()
{
	return string("老板");
 }

