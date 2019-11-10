#include <iostream>
using namespace std;

void test() {
	int* p = (int*)malloc(4);
	//char* p = (char*)malloc(4);
	*p = 10;
	free(p);
}

void test2() {
	int* p = new int;
	*p = 10;
	delete p;
}

void test3() {
	int* p = new int[];
	*p = 10;
	delete[] p;
}

void test4() {
	int size = sizeof(int) * 10;
	int* p1 = (int*)malloc(size);
	int* p2 = (int*)malloc(size);
	memset(p2, 0, size);

	int* p1 = new int;			//未被初始化
	int* p2 = new int();		//被初始化为0
	int* p3 = new int(5);		//被初始化为5
	int* p4 = new int[3];		//数组元素未被初始化
	int* p5 = new int[3]();		//3个数组元素都被初始化为0
	int* p6 = new int[3]{};		//3个数组元素都被初始化为0
	int* p7 = new int[3]{5};	//数组首元素被初始化为5，其他元素被初始化为0
}

struct Person {
	int m_id;
	int m_age;
	int m_height;
};

void test5() {
	Person person;
	person.m_id = 1;
	person.m_age = 20;
	person.m_height = 190;
	memset(&person, 0, sizeof(person));

	Person persons[] = { {1,20,190},{1,18,180} };
	memset(persons, 0, sizeof(persons));

}
//全局区
Person g_person;

//int main() {
//	//栈空间
//	Person person;
//	//堆空间
//	Person* p = new Person;
//	return 0;
//}

int main() {
	test();
	test2();
	test3();
	test4();
	getchar();
	return 0;
}