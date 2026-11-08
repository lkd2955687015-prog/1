#include "workerManager.h"
#include "employee.h"
#include<limits>
#include<algorithm>

WorkerManager::WorkerManager()
{
	//文件不存在
	ifstream ifs;
	ifs.open(filename, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在，数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空!" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	ifs.close();

	//文件存在，数据记录
	int num = this->get_empNumber();
	cout << "职工人数为:" << num << endl;

	if (num > 0)
	{
		this->m_EmpNum = num;
		this->m_EmpArray = new worker * [num];
		this->m_FileIsEmpty = false;
		this->init_emp();
	}
	else
	{
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		this->m_FileIsEmpty = true;
	}
}

int WorkerManager::get_empNumber()
{
	ifstream ifs;
	ifs.open(filename, ios::in);
	if (!ifs.is_open())
	{
		return 0;
	}

	int id;
	string name;
	int did;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		num++;
	}
	ifs.close();
	return num;
}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(filename, ios::out);

	for (int i = 0;i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_id << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_deptid << endl;
	}
	ofs.close();
}

void WorkerManager::ShowMeau()
{
	cout << "*********************************" << endl;
	cout << "*******欢迎使用职工管理系统!*******" << endl;
	cout << "********* 0.退出管理程序 *********" << endl;
	cout << "********* 1.增加职工信息 *********" << endl;
	cout << "********* 2.显示职工信息 *********" << endl;
	cout << "********* 3.删除职工信息 *********" << endl;
	cout << "********* 4.修改职工信息 *********" << endl;
	cout << "********* 5.查找职工信息 *********" << endl;
	cout << "********* 6.按照编号排序 *********" << endl;
	cout << "********* 7.清空所有文档 *********" << endl;
	cout << "**********************************" << endl;
}

void WorkerManager::exitSystem()
{
	cout << "欢迎下次再使用" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::Add_Emp()
{
	cout << "请输入添加的数量: " << endl;
	int addnum = 0;
	if (!(cin >> addnum) || addnum <= 0)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "输入有误" << endl;
		system("pause");
		system("cls");
		return;
	}

	int newSize = this->m_EmpNum + addnum;
	worker** newSpace = new worker * [newSize];

	if (this->m_EmpArray != NULL)
	{
		for (int i = 0;i < this->m_EmpNum;i++)
		{
			newSpace[i] = this->m_EmpArray[i];
		}
	}

	for (int i = 0;i < addnum;i++)
	{
		int id = 0;
		string name;
		int dSelect = 0;

		//编号：输入非法或重复都要重新输入，避免出现空指针/重复编号
		cout << "请输入第" << i + 1 << "个新职工编号" << endl;
		while (true)
		{
			if (!(cin >> id))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "编号输入有误，请重新输入" << endl;
				continue;
			}

			bool dup = (this->IsExist(id) != -1);
			for (int k = 0;k < this->m_EmpNum + i && !dup;k++)
			{
				if (newSpace[k] != NULL && newSpace[k]->m_id == id)
				{
					dup = true;
				}
			}

			if (dup)
			{
				cout << "该编号已存在，请重新输入" << endl;
				continue;
			}
			break;
		}

		cout << "请输入第" << i + 1 << "个新职工姓名" << endl;
		cin >> name;

		//岗位只能是 1/2/3，否则会出现没有对象的空指针
		cout << "请输入职工岗位(1员工 2经理 3老板)" << endl;
		while (!(cin >> dSelect) || dSelect < 1 || dSelect > 3)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "岗位只能是 1、2、3，请重新输入" << endl;
		}

		worker* newWorker = NULL;
		switch (dSelect)
		{
		case 1:
			newWorker = new Employee(id, name, 1);
			break;
		case 2:
			newWorker = new manager(id, name, 2);
			break;
		case 3:
			newWorker = new boss(id, name, 3);
			break;
		}
		newSpace[this->m_EmpNum + i] = newWorker;
	}

	delete[] this->m_EmpArray;
	this->m_EmpArray = newSpace;
	this->m_EmpNum = newSize;
	this->m_FileIsEmpty = false;
	cout << "成功添加" << addnum << "名职工！" << endl;

	this->save();

	system("pause");
	system("cls");
}



void WorkerManager::init_emp()
{
	ifstream ifs;
	ifs.open(filename, ios::in);
	if (!ifs.is_open())
	{
		return;
	}

	int id;
	string name;
	int did;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		worker* newWorker = NULL;
		switch (did)
		{
		case 1:
			newWorker = new Employee(id, name, did);
			break;
		case 2:
			newWorker = new manager(id, name, did);
			break;
		case 3:
			newWorker = new boss(id, name, did);
			break;
		default:
			//文件里出现非法岗位时按员工处理，避免数组里留下空指针
			newWorker = new Employee(id, name, 1);
			break;
		}
		this->m_EmpArray[index] = newWorker;
		index++;
	}
	ifs.close();
}

void WorkerManager::show_emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "该文件为空或者不存在" << endl;

	}
	else
	{
		for (int i = 0;i < m_EmpNum;i++)
		{
			this->m_EmpArray[i]->showPerson();
		}
	}
	system("pause");
	system("cls");

}

int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0;i < m_EmpNum;i++)
	{
		if (this->m_EmpArray[i] != NULL && id == this->m_EmpArray[i]->m_id)
		{
			index = i;
			break;
		}
	}
	return index;
}

void WorkerManager::Del_emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "该文件为空或者不存在" << endl;

	}
	else
	{
		cout << "输入要删除职工的编号" << endl;
		int id;
		cin >> id;

		int index = this->IsExist(id);
		if (index != -1)
		{
			delete this->m_EmpArray[index];
			for (int i = index;i < m_EmpNum - 1;i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpArray[m_EmpNum - 1] = NULL;
			this->m_EmpNum--;
			this->save();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "该职工不存在" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "该文件为空或者不存在" << endl;

	}
	else
	{
		cout << "请输入修改的职工编号" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)
		{
			int newId = 0;
			string newName;
			int newDept = 0;

			cout << "请输入新职工编号" << endl;
			while (!(cin >> newId))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "编号输入有误，请重新输入" << endl;
			}

			cout << "请输入新职工姓名" << endl;
			cin >> newName;

			cout << "请输入职工岗位(1员工 2经理 3老板)" << endl;
			while (!(cin >> newDept) || newDept < 1 || newDept > 3)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "岗位只能是 1、2、3，请重新输入" << endl;
			}

			//新对象先建好，再删旧对象，避免中途失败把原数据删没了
			worker* newWorker = NULL;
			switch (newDept)
			{
			case 1:
				newWorker = new Employee(newId, newName, 1);
				break;
			case 2:
				newWorker = new manager(newId, newName, 2);
				break;
			case 3:
				newWorker = new boss(newId, newName, 3);
				break;
			}

			delete this->m_EmpArray[index];
			m_EmpArray[index] = newWorker;
			this->save();

			cout << "修改成功" << endl;
		}
		else
		{
			cout << "该职工不存在" << endl;
		}

	}
	system("pause");
	system("cls");

}

void WorkerManager::FindEmp()
{
	int id;
	cout << "输入要查找的编号" << endl;
	cin >> id;

	int ret = IsExist(id);

	if (ret != -1)
	{
		cout << "找到了" << endl;
		this->m_EmpArray[ret]->showPerson();
	}
	else
	{
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty || this->m_EmpNum == 0)
	{
		cout << "该文件为空或者不存在" << endl;
		system("pause");
		system("cls");
		return;
	}

	sort(this->m_EmpArray, this->m_EmpArray + this->m_EmpNum,
		[](worker* a, worker* b) { return a->m_id < b->m_id; });

	this->save();
	cout << "排序完成" << endl;
	this->show_emp();
}

void WorkerManager::clean_file()
{
	for (int i = 0;i < this->m_EmpNum;i++)
	{
		delete this->m_EmpArray[i];
	}
	delete[] this->m_EmpArray;
	this->m_EmpArray = NULL;
	this->m_EmpNum = 0;
	this->m_FileIsEmpty = true;

	ofstream ofs(filename, ios::trunc);
	ofs.close();

	cout << "清空成功" << endl;
	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager()
{
	for (int i = 0;i < this->m_EmpNum;i++)
	{
		delete this->m_EmpArray[i];
	}
	delete[] this->m_EmpArray;
	this->m_EmpArray = NULL;
	this->m_EmpNum = 0;
}
