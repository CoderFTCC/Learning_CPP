#pragma once

#include <string>

#define CAPACITY 1000
#define INFOLENGTH 5
#define VERSION "1.0.0-Previewed"

using namespace std;

struct Person {
	//姓名
	string p_name;
	//性别 0 女 1 男
	int p_gender;
	//年龄
	int p_age;
	//电话
	string p_phone;
	//住址
	string p_address;
};

struct AddressBooks {
	//通讯录中保存的联系人数组
	struct Person personArray[CAPACITY];
	//通讯录中当前人员个数
	int info[INFOLENGTH];
};

void showMenu();

void menuSelect(struct AddressBooks* pAdbs);

void menuExit();

int checkIfExist(string phone, struct Person* personArray, int length);

void printPerson(int index, AddressBooks* pAdbs);

void addPerson(AddressBooks* pAdbs);

void findPerson(AddressBooks* pAdbs);

void TestData(AddressBooks* pAdbs);

void showAddressBooks(AddressBooks* pAdbs);

void removePerson(AddressBooks* pAdbs);

void removeAll(AddressBooks* pAdbs);

void About();

void menu(struct AddressBooks* pAdbs);

struct AddressBooks* init(int* flag);
