#pragma once
#include"worker.h"

class manager :public worker
{
public:

	manager(int id, string name, int did);

	virtual void showPerson() ;

	virtual string getdeptname() ;


};