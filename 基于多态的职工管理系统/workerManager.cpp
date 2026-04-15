#include"workerManager.h"

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//文件不存在
	if (!ifs.is_open())
	{
		//cout << "文件不存在！" << endl;
		this->m_empNum = 0;
		this->m_fileIsEmpty = true;
		this->m_empArray = NULL;
		ifs.close();
		return;
	}
	//文件存在，但为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件存在，但里面是空的！" << endl;
		this->m_empNum = 0;
		this->m_fileIsEmpty = true;
		this->m_empArray = NULL;
		ifs.close();
		return;
	}

	//文件存在且内有员工数据
	//更新系统内的人数
	int num = get_empNum();
	//cout << "职工的人数为：" << num << endl;
	this->m_empNum = num; //更新系统内的人数
	this->m_empArray = new Worker * [this->m_empNum];
	this->init_emp();

	//for (int i = 0; i < this->m_empNum;i++)
	//{
	//	cout << "编号：" << this->m_empArray[i]->m_id
	//		<< "姓名：" << this->m_empArray[i]->m_name
	//		<< "部门：" << this->m_empArray[i]->m_deptId << endl;
	//}
}

WorkerManager::~WorkerManager()
{
	if (this->m_empArray != NULL)
	{
		delete[] this->m_empArray;
		this->m_empArray = NULL;
	}
}

//展示菜单
void WorkerManager::show_Menu() 
{
	cout << "*****************************************" << endl;
	cout << "**********   1、增加员工信息   **********" << endl;
	cout << "**********   2、显示员工信息   **********" << endl;
	cout << "**********   3、删除离职员工   **********" << endl;
	cout << "**********   4、修改员工信息   **********" << endl;
	cout << "**********   5、查找员工信息   **********" << endl;
	cout << "**********   6、按照编号排序   **********" << endl;
	cout << "**********   7、清空所有文档   **********" << endl;
	cout << "**********   0、退出管理程序   **********" << endl;
	cout << "*****************************************" << endl;
	cout << endl;
}

//退出系统
void WorkerManager::exitSystem()
{
	cout << "您已退出系统" << endl;
	system("pause");
	exit(0);
}

//添加员工
void WorkerManager::addWorker()
{
	cout << "请输入要添加的员工数量：";
	int addNum;
	cin >> addNum;
	if (addNum > 0) {
		//add
		int newSize = this->m_empNum + addNum;
		//开辟新的空间，用于存储需要添加的员工
		Worker** newSpace = new Worker* [newSize]();
		//将原来空间里的员工，拷贝到新的空间中
		if (this->m_empArray != NULL)
		{
			for (int i = 0; i < this->m_empNum; i++)
			{
				newSpace[i] = this->m_empArray[i];
			}
		}

		//批量添加数据
		for (int i = 0; i < addNum; i++){
			int emp_id;//员工id
			string emp_name;//员工姓名
			int dselect;//选择岗位编号

			cout << "请输入您要添加的第 " << i + 1 << " 个员工的编号: ";
			cin >> emp_id;
			cout << "员工的姓名：";
			cin >> emp_name;
			cout << "员工的职位：1.普通员工 2.经理 3.老板  请选择：";
			cin >> dselect;

			Worker* worker = NULL;
			switch (dselect) {
			case 1:
				worker = new Employee(emp_id, emp_name, dselect);
				break;
			case 2:
				worker = new Manager(emp_id, emp_name, dselect);
				break;
			case 3:
				worker = new Boss(emp_id, emp_name, dselect);
				break;
			default:
				break;
			}
			newSpace[this->m_empNum + i] = worker;
		}
		//释放原有空间，保存新空间。以及人数
		delete[] this->m_empArray;
		this->m_empArray = newSpace;
		this->m_empNum = newSize;
		this->m_fileIsEmpty = false; //添加人员进去，表示里面就不为空。
		cout << "添加成功!" << endl;

		//保存数据到文件中
		this->save();
	}
	else {
		cout << "您输入有误，请重新输入!";
	}
	system("pause");
	system("cls");

}

//保存文件
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	//将每个人的数据写入文件中
	for (int i = 0; i < this->m_empNum; i++)
	{
		ofs << this->m_empArray[i]->m_id << " "
			<< this->m_empArray[i]->m_name << " "
			<< this->m_empArray[i]->m_deptId << " " << endl;
	}
	ofs.close();

}

//记录人数
int WorkerManager::get_empNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
		num++;//记录人数

	ifs.close();
	return num;
}

//初始化数据
void WorkerManager::init_emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	int id;
	string name;
	int dId;

	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if(dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else if (dId == 3)
		{
			worker = new Boss(id, name, dId);
		}
		this->m_empArray[index] = worker; 
		index++;
	}
	ifs.close();
}

//显示职工
void WorkerManager::showEmp()
{
	if (this->m_fileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for(int i = 0; i < this->m_empNum;i++)
		{
			//利用多态调用接口
			this->m_empArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
	return;
}

//删除员工
void WorkerManager::deleteEmp()
{
	if (this->m_fileIsEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		cout << "请输入你要删除的员工的编号： ";
		int id;
		cin >> id;
		int index = this->isExist(id);

		if ( index != -1 )
		{
			for (int i = index + 1; i < this->m_empNum; i++)
			{
				this->m_empArray[i - 1] = this->m_empArray[i];
			}
			this->m_empNum--;
			//数据同步更新到文件中
			this->save();
			cout << "删除成功！";
		}
		else
		{
			cout << "您要删除的员工不存在！";
		}
	}
	if (this->m_empNum == 0)
	{
		this->m_fileIsEmpty = true;
	}
	system("pause");
	system("cls");
	return;
}

//按照编号查找员工
int WorkerManager::isExist(int id)
{
	for (int i = 0; i < this->m_empNum; i++)
	{
		if (this->m_empArray[i]->m_id == id)
		{
			return i;
		}
	}
	return -1;
}

void WorkerManager::modEmp()
{
	if (this->m_fileIsEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		cout << "请输入修改的职工的编号： ";
		int id;
		cin >> id;
		int index = this->isExist(id);
		if (index != -1)
		{
			//直接清空
			delete this->m_empArray[index];

			int newId = 0;
			string newName = "";
			int dselect = 0;

			cout << "查到：" << id << " 员工，请输入要修改的编号：";
			cin >> newId;

			cout << "请输入新的姓名： ";
			cin >> newName;

			cout << "请输入新的岗位编号： 1. 普通员工  2. 经理  3. 老板  请输入： ";
			cin >> dselect;

			Worker* worker = NULL;

			switch (dselect)
			{
			case 1:
				worker = new Employee(newId, newName, dselect);
				break;
			case 2:
				worker = new Manager(newId, newName, dselect);
				break;
			case 3:
				worker = new Boss(newId, newName, dselect);
				break;
			default:
				break;
			}

			//更新数据到数组中
			this->m_empArray[index] = worker;
			cout << "修改成功！" << endl;
			this->save();
		}
		else
		{
			cout << "没有这个职工！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//查找员工
void WorkerManager::findEmp()
{
	if (this->m_fileIsEmpty)
	{
		cout << "文件不存在或记录为空！";
	}
	else
	{
		//按照编号查
		cout << "请输入你要查找的方式，按照编号输入1，按照姓名输入2： ";
		int select = 0;
		cin >> select;
		//按照编号查
		if (select == 1)
		{
			int id = 0;
			cout << "请输入你要查找的编号： ";
			cin >> id;
			if (isExist(id) != -1)
			{
				this->m_empArray[isExist(id)]->showInfo();
			}
			else
			{
				cout << "查无此人！" << endl;
			}
		}
		else if (select == 2)
		{
			cout << "请输入你要查找的员工的姓名： ";
			string name;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < this->m_empNum; i++)
			{
				if (this->m_empArray[i]->m_name == name)
				{
					this->m_empArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "查无此人!" << endl;
			}
		}
		else
		{
			cout << "您的输入错误，请输入1或者2！" << endl;
		}
		//按照姓名查
	}
	system("pause");
	system("cls");
}

void WorkerManager::empSort()
{
	if (this->m_fileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "按照职工的编号进行排序，请选择升序：1   降序：2 , 请选择：   ";
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			for (int i = 0; i < this->m_empNum; i++)
			{
				int min = i;
				for (int j = i + 1; j < this->m_empNum; j++)
				{
					if (this->m_empArray[min]->m_id > this->m_empArray[j]->m_id)
						min = j;
				}
				if (i != min)
				{
					Worker* temp = this->m_empArray[i];
					this->m_empArray[i] = this->m_empArray[min];
					this->m_empArray[min] = temp;
				}
			}
			cout << "升序排序成功！排序好之后的结果为：" << endl;
			this->save();
			this->showEmp();

		}
		else if (select == 2)
		{
			for (int i = 0; i < this->m_empNum; i++)
			{
				int max = i;
				for (int j = i + 1; j < this->m_empNum; j++)
				{
					if (this->m_empArray[max]->m_id < this->m_empArray[j]->m_id)
						max = j;
				}
				if (i != max)
				{
					Worker* temp = this->m_empArray[i];
					this->m_empArray[i] = this->m_empArray[max];
					this->m_empArray[max] = temp;
				}
			}
			cout << "降序排序成功！排序好之后的结果为：" << endl;
			this->save();
				this->showEmp();
		}
		else
		{
			cout << "请输入1或者2！" << endl;
			system("pause");
			system("cls");
		}
	}
}

void WorkerManager::cleanFile()
{
	cout << "确定清空吗？选择 1:确定 2:返回。 请选择： ";
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_empArray != NULL)
		{
			for(int i = 0; i < m_empNum; i++)
			{
				if (this->m_empArray[i] != NULL)
				{
					delete this->m_empArray[i];
				}
			}
			this->m_empNum = 0;
			delete[] this->m_empArray;
			this->m_empArray = NULL;
			this->m_fileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}
