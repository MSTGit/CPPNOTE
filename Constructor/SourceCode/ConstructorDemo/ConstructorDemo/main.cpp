#include <iostream>
using namespace std;

struct Person {
	int m_age;
	
	Person() {
		cout << "Person()" << endl;
	};

	Person(int age) {
		cout << "Person(int age)" << endl;
	};
};

Person g_person0;
Person g_person1();
Person g_person2(10);
int main() {
	Person person0;
	Person person1();
	Person person2(20);

	Person* p0 = new Person;
	Person* p1 = new Person();
	Person* p2 = new Person(30);
	getchar();
	return 0;
}

//int main() {
//	Person* p = (Person*)malloc(sizeof(Person));
//	p->m_age = 10;
//	getchar();
//	return 0;
//}
//int main() {
//	Person person;
//	person.m_age = 0;
//
//	Person person2;
//	person2.m_age = 0;
//
//	Person person3;
//	person2.m_age = 0;
//	getchar();
//	return 0;
//}

//struct Person {
//	int m_age;
//	Person(int age) {
//		m_age = 0;
//	}
//};
//int main() {
//	Person person;
//
//	Person person2;
//
//	Person person3;
//	getchar();
//	return 0;
//}