#pragma once
#include<iostream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include<fstream>
#define FILENAME "empfile.txt"
using namespace std;

class WorkerManager {
public:
	//记录在职员工人数
	int m_empNum;

	//保存员工信息数组
	Worker** m_empArray;

	//标志文件是否为空
	bool m_fileIsEmpty;

	WorkerManager();//构造
	~WorkerManager();//析构

	//展示菜单
	void show_Menu();

	//退出系统
	void exitSystem();

	//增加员工
	void addWorker();

	//保存文件
	void save();

	//获取人数
	int get_empNum();

	//初始化数据
	void init_emp();

	//显示职工
	void showEmp();

	//删除职工 按照编号删除
	void deleteEmp();

	//判断职工是否存在，若存在返回所在位置，不存在返回-1
	int isExist(int id);

	//修改职工
	void modEmp();

	//查找职工
	void findEmp();

	//排序职工
	void empSort();

	//清空文档
	void cleanFile();
};