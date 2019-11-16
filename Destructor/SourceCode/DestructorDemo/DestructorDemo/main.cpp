#include <iostream>
using namespace std;

struct Car {
	int m_price;
	Car() {
		m_price = 0;
		cout << "Car::Car()" << endl;
	}
	~Car() {
		cout << "~Car::Car()" << endl;
	}
};

struct Person {
	int m_age;
	Car* m_car;
	Person() {
		m_age = 0;
		m_car = new Car();
		cout << "Person::Person()" << endl;
	}
	~Person() {
		delete m_car;
		cout << "~Person::Person()" << endl;
	}
};

void test() {
	cout << 1 << endl;
	{
		Person person;
	}
	cout << 2 << endl;
}

void test2() {
	{
		Person person;
	}
}
int main() {
	//test();
	{
		Person person;
	}
	getchar();
	return 0;
}