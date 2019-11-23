#include <iostream>
using namespace std;

class Car {
	//int m_price;
	//int m_length;
public:
	int m_price;
	int m_length;
	Car(int price = 0, int length = 0) :m_price(price), m_length(length) {
		cout << "Car(int price = 0, int lenght = 0)" << endl;
	}

	Car(const Car& car) {
		cout << "Car(const Car& car)" << endl;
		m_price = car.m_price;
		m_length = car.m_length;
	}

	void display() {
		cout << "price=" << m_price << ", length=" << m_length << endl;
	}
};

class Person {
	int m_age;
public :
	Person(int age = 0) :m_age(age) {}
	Person(const Person& person) :m_age(person.m_age) {}

};

class Student : public Person {
	int m_score;
public:
	Student(int age = 0, int score = 0) : Person(age), m_score(score) {}
	Student(const Student& student) :Person(student), m_score(student.m_score) {}
};
int main() {
	Car car1(100,5);
	Car car2;
	car2.m_price = car1.m_price;
	car2.m_length = car2.m_length;
	car1.display();
	car2.display();
	getchar();
	return 0;
}
