#include <iostream>
using namespace std;

struct Person {
	int m_age;
	//int m_height;

	//Person(int age, int height) {
	//	m_age = age;
	//	m_height = height;
	//}

	//Person(int age, int height) :m_age(age), m_height(height) {
	//}

	//Person(int age = 0, int height = 0) :m_age(age), m_height(height) {
	//}

	Person(){
		//Person(10, 20);
		cout << "Person::Person()" << endl;
	}

	/*Person(int age, int height) {
		m_age = age;
		m_height = height;
	}*/

	~Person() {
		cout << m_age <<endl;
	}

};

struct Student :Person {
	int m_no;
	Student() {
		cout << "Student::Student()" << endl;
	}
};

int main() {
	{
		Person person;
	}
	//Person person(18, 180);
	//cout << person.m_age << endl;
	//cout << person.m_height << endl;
	getchar();
	return 0;
}
