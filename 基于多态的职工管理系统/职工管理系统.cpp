#include <iostream>
#include "workerManager.h"
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
int main()
{
	//Worker* worker = NULL;	
	//worker = new Employee(1, "zhangshan", 1);
	//worker->showInfo();
	//delete worker;
	//worker = new Manager(2, "lisi", 2);
	//worker->showInfo();
	//delete worker;
	//worker = new Boss(3, "wangwu", 3);
	//worker->showInfo();
	//delete worker;

	WorkerManager wm;

	int choice = 1;

	while (choice) {
		wm.show_Menu();
		cout << "请输入你的选择：";
		cin >> choice;
		switch (choice) {
		case 0: wm.exitSystem();//退出系统
			break;
		case 1: wm.addWorker();//增加
			break;
		case 2: wm.showEmp();//显示
			break;
		case 3: wm.deleteEmp();//删除
			break;
		case 4:wm.modEmp();//修改
			break;
		case 5:wm.findEmp();//查找
			break;
		case 6:wm.empSort();//排序
			break;
		case 7:wm.cleanFile();//清空文档
			break;
		default://退出系统
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}