#include <iostream>
using namespace std;

//class Person{
//	//成员变量
//	int m_age;
//	//成员函数
//	void run() {
//		cout << "run()" << endl;
//	}
//};

class Person{
public:
	//成员变量
	int m_age;
	//成员函数
	void run() {
		cout << "Person :: run() - " << m_age <<  endl;
	}
};

void test1() {
	Person person;
	//访问person对象的成员变量
	person.m_age = 20;
	//用person对象调用成员函数
	person.run();

	//通过指针间接访问person对象
	Person* p = &person;
	p->m_age = 30;
	p->run();
}

void test2() {
	Person person1;
	person1.m_age = 10;

	Person person2;
	person2.m_age = 20;

	Person person3;
	person3.m_age = 30;
}

//struct Car {
//	int m_price;
//};

class Car {
public:
	int m_price;
};
/*int main() {
	Car car;
	car.m_price = 10;

	getchar();
	return 0;
}*/

int main() {
	Person person1;
	person1.m_age = 10;
	person1.run();
	Person person2;
	person2.m_age = 20;
	person2.run();
	Person person3;
	person3.m_age = 30;
	person.run();
	getchar();
	return 0;
}