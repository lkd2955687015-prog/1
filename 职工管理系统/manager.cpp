#include"manager.h"

manager::manager(int id, string name, int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = did;
}

void manager::showPerson()
{
	cout << "经理编号: " << this->m_id
		<< "  经理姓名: " << this->m_name
		<< "  经理岗位: " << getdeptname()
		<< "  岗位职责：给职工交代任务" << endl;
}

string manager::getdeptname()
{
	return string("经理");
}