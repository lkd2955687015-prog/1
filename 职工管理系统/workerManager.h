#pragma once
#include <iostream>
using namespace std;
#include"worker.h"
#include"boss.h"
#include"manager.h"

#include<fstream>
#define filename "empfile.txt"

class WorkerManager
{
public:
	WorkerManager();

	void ShowMeau();

	void exitSystem();

	~WorkerManager();

	int m_EmpNum;

	worker** m_EmpArray;

	void Add_Emp();

	//文件管理
	void save();

	bool m_FileIsEmpty;

	int get_empNumber();

	void init_emp();

	void show_emp();

	int IsExist(int id);
	void Del_emp();

	void Mod_Emp();

	void FindEmp();

	void clean_file();

	void Sort_Emp();

};


