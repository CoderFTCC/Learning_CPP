#include <iostream>
#include <stdlib.h>
#include <string>
#include "Launcher.h"
using namespace std;

int mainS1P() {

	int flag = false;

	struct AddressBooks* pAdbs = init(&flag);

	TestData(pAdbs);

	menu(pAdbs);

	//system("pause");

	return 0;
}

void About()
{
	cout << "************************" << endl;
	cout << "**********关于**********" << endl;
	cout << "***版本号：" << VERSION << endl;
	cout << "***Copright FT,All rights reserved." << endl;
	cout << "************************" << endl;
}

void removeAll(AddressBooks* pAdbs)
{
	cout << "您确定要清空通讯录吗？（键入\"1\"以确认！）" << endl;
	int choice = 0;
	cin >> choice;
	if (choice == 1) {
		for (int i = 0; i < pAdbs->info[0]; i++) {
			struct Person newPerson;
			pAdbs->personArray[i] = newPerson;
		}
		pAdbs->info[0] = 0;
		cout << "通讯录已清空！" << endl;
	}
	else {
		cout << "已取消清空！" << endl;
	}
}

void removePerson(AddressBooks* pAdbs)
{
	cout << "请输入需要删除的联系人的手机号码：" << endl;
	string target;
	cin >> target;
	int result = checkIfExist(target, pAdbs->personArray, pAdbs->info[0]);
	if (result != -1) {
		cout << "您确定要删除该联系人吗？（键入\"1\"以确认！）" << endl;
		printPerson(result, pAdbs);
		int choice = 0;
		cin >> choice;
		if (choice == 1) {
			for (int i = result; i < pAdbs->info[0] - 1; i++) {
				pAdbs->personArray[i] = pAdbs->personArray[i + 1];
			}
			struct Person newPerson;
			pAdbs->personArray[pAdbs->info[0] - 1] = newPerson;
			pAdbs->info[0]--;
			cout << "删除成功！" << endl;
		}
		else {
			cout << "已取消删除！" << endl;
		}
	}
	else {
		cout << "未找到该联系人！" << endl;
	}
}

void showAddressBooks(AddressBooks* pAdbs)
{
	cout << "***********************" << endl;
	cout << "您通讯录当前共有 " << pAdbs->info[0] << " 个联系人" << endl;
	for (int i = 0; i < pAdbs->info[0]; i++) {
		printPerson(i, pAdbs);
	}
	cout << "***********************" << endl;
}

void TestData(AddressBooks* pAdbs)
{
	pAdbs->personArray[0] = { "张三", 1, 20, "12345678901", "北京市" };
	pAdbs->personArray[1] = { "李四", 0, 18, "12345678902", "上海市" };
	pAdbs->personArray[2] = { "王五", 3, 22, "12345678903", "北京市" };
	pAdbs->personArray[3] = { "王五", 5, 24, "12345678904", "赣州市" };
	pAdbs->personArray[4] = { "王五", 3, 25, "12345678905", "广州市" };

	pAdbs->info[0] = 5;
}

void findPerson(AddressBooks* pAdbs)
{
	cout << "请选择查询方式：" << endl;
	cout << "1 -- 按姓名查询" << endl;
	cout << "2 -- 按电话查询" << endl;
	int choice = 0;
	string target;
	cin >> choice;
	if (choice == 1) {
		cout << "请输入要查找联系人的姓名：" << endl;
		cin >> target;
		int num = 0;
		for (int i = 0; i < pAdbs->info[0]; i++) {
			if (!pAdbs->personArray[i].p_name.compare(target)) {
				num++;
				printPerson(i, pAdbs);
			}
		}
		if (num > 0) {
			cout << "共找到" << num << "个联系人！" << endl;
		}
		else {
			cout << "未找到名为 \"" << target << "\" 的联系人！" << endl;
		}
	}
	else if (choice == 2) {
		cout << "请输入要查找联系人的电话号码：" << endl;
		cin >> target;
		int result = checkIfExist(target, pAdbs->personArray, pAdbs->info[0]);
		if (result != -1) {
			printPerson(result, pAdbs);
		}
		else {
			cout << "未找到该联系人！" << endl;
		}
	}
	else {
		cout << "输入有误！" << endl;

	}
}

void addPerson(AddressBooks* pAdbs)
{
	int index = pAdbs->info[0];

	if (index == CAPACITY)
	{
		cout << "通讯录已满，无法添加" << endl;
		return;
	}
	string phone;
	cout << "请输入电话号码：" << endl;
	while (true) {
		cin >> phone;
		if (phone.compare("0") == 0) {
			cout << "已取消添加！" << endl;
			return;
		}
		else if (phone.length() != 11) {
			cout << "电话号码格式错误！请重新输入，若要取消添加，请输入\"0\"！" << endl;
		}
		else {
			break;
		}
	}

	int result = checkIfExist(phone, pAdbs->personArray, index);

	if (result == -1) {

		//联系电话
		pAdbs->personArray[index].p_phone = phone;

		//姓名
		string name;
		cout << "请输入姓名：" << endl;

		cin >> name;
		pAdbs->personArray[index].p_name = name;

		//性别
		cout << "请输入性别：" << endl;
		cout << "1 -- 男" << endl;
		cout << "2 -- 女" << endl;
		cout << ">=3 -- 未知" << endl;

		int gender = 0;
		cin >> gender;
		pAdbs->personArray[index].p_gender = gender;

		//年龄
		cout << "请输入年龄：" << endl;
		int age = 0;
		while (true) {
			cin >> age;
			if (age >= 0 && age <= 120) {
				pAdbs->personArray[index].p_age = age;
				break;
			}
			else {
				cout << "年龄输入有误，请重新输入：（年龄范围0 ~ 120）" << endl;
			}
		}

		//家庭住址
		cout << "请输入家庭住址：" << endl;
		string address;
		cin >> address;
		pAdbs->personArray[index].p_address = address;

		//更新通讯录人数
		pAdbs->info[0] = index + 1;

		cout << "联系人 " << name << " 已添加至您的通讯录！" << endl;
		printPerson(index, pAdbs);
	}
	else {
		cout << "该联系人已存在！" << endl;
		printPerson(result, pAdbs);
	}
}

void printPerson(int index, AddressBooks* pAdbs)
{
	if (index >= 0 && index <= pAdbs->info[0]) {
		cout << "***********************" << endl;
		cout << "***姓名：" << pAdbs->personArray[index].p_name << endl;
		cout << "***性别：";
		switch (pAdbs->personArray[index].p_gender) {
		case 0:
			cout << "女" << endl;
			break;
		case 1:
			cout << "男" << endl;
			break;
		default:
			cout << "未知" << endl;
			break;
		}
		cout << "***年龄：" << pAdbs->personArray[index].p_age << endl;
		cout << "***电话：" << pAdbs->personArray[index].p_phone << endl;
		cout << "***住址：" << pAdbs->personArray[index].p_address << endl;
		cout << "***********************" << endl;
	}
	else {
		cout << "该联系人不存在！" << endl;
	}
}

int checkIfExist(string phone, struct Person* personArray, int length)
{
	for (int i = 0; i < length; i++) {
		if (!personArray[i].p_phone.compare(phone)) {
			return i;
		}
	}
	return -1;
}

void menuExit()
{
	cout << "通讯录管理系统已退出，感谢您的使用！" << endl;
	exit(0);
}

void menuSelect(struct AddressBooks* pAdbs)
{
	int select = 0;
	cout << "请输入您的选择：" << endl;
	while (true) {
		cin >> select;
		switch (select) {
		case 1:
			addPerson(pAdbs);
			return;
		case 2:
			showAddressBooks(pAdbs);
			return;
		case 3:
			removePerson(pAdbs);
			return;
		case 4:
			findPerson(pAdbs);
			return;
		case 5:
			cout << "修改联系人" << endl;
			return;
		case 6:
			removeAll(pAdbs);
			return;
		case 10:
			About();
			return;
		case 0:
			menuExit();
			return;
		default:
			cout << "输入有误，请重新输入。" << endl;
		}
	}
}

void showMenu()
{
	cout << "***************************" << endl;
	cout << "*****  1、添加联系人  *****" << endl;
	cout << "*****  2、显示联系人  *****" << endl;
	cout << "*****  3、删除联系人  *****" << endl;
	cout << "*****  4、查找联系人  *****" << endl;
	cout << "*****  5、修改联系人  *****" << endl;
	cout << "*****  6、清空联系人  *****" << endl;
	cout << "*****  10、关于通讯录  *****" << endl;
	cout << "*****  0、退出通讯录  *****" << endl;
	cout << "***************************" << endl;
}

void menu(struct AddressBooks* pAdbs)
{
	while (true) {
		showMenu();
		menuSelect(pAdbs);
	}
}

struct AddressBooks* init(int* flag)
{
	if (*flag) {
		cout << "Alert:系统错误，请检查安装版本是否为官方版本！" << endl;
		exit(2001);
	}
	struct AddressBooks* pAddressBooks = new AddressBooks;
	pAddressBooks->info[0] = 0;
	*flag = true;
	return pAddressBooks;
}