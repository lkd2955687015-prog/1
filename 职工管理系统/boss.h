#pragma once
#include"worker.h"

class boss :public worker
{
public:

	boss(int id, string name, int did);

	virtual void showPerson();

	virtual string getdeptname();


};
