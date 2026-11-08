#include<iostream>
using namespace std;
#include "workerManager.h"

#include"worker.h"
#include"employee.h"
#include"boss.h"
#include"manager.h"


int main()
{
	//worker* worker1 = NULL;
	//worker1 = new Employee(1, "张三", 1);
	//worker1->showPerson();

	//worker* worker2 = NULL;
	//worker2 = new manager(2, "李四", 2);
	//worker2->showPerson();

	//worker* worker3 = NULL;
	//worker3 = new boss(3, "王五", 3);
	//worker3->showPerson();


	WorkerManager wm;

	int choice = 0;

	while (true)
	{
		//调用展示菜单的成员函数
		wm.ShowMeau();

		cout << "请输入您的选择: " << endl;
		cin >> choice;

		switch (choice)
		{
		case 0://退出系统
			wm.exitSystem();
			break;

		case 1://增加
			wm.Add_Emp();

			break;

		case 2://显示
			wm.show_emp();
			break;

		case 3://删除
			wm.Del_emp();
			break;

		case 4://修改
			wm.Mod_Emp();
			break;

		case 5://查找
			wm.FindEmp();
			break;

		case 6://排序
			wm.Sort_Emp();
			break;

		case 7://清空
			wm.clean_file();
			break;

		}

	}
	system("pause");
	return 0;
}