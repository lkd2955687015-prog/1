#pragma once
#include<iostream>
using namespace std;
#include<string>

class worker
{
public:
	//xingwei
	virtual void showPerson() = 0;

	virtual string getdeptname() = 0;

	virtual ~worker() {}

	//shuxing
	int m_id;
	string m_name;
	int m_deptid;
};