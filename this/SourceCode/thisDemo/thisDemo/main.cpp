#include <iostream>
using namespace std;

//struct Person {
//	int m_age;
//	void run(Person *person) {
//		cout << "Person :: run() " << person->m_age << endl;
//	}
//};
//struct Person {
//	int m_age;
//	void run() {
//		cout << "Person :: run() " << m_age << endl;
//	}
//};
void func() {

}

struct Person {
	int m_id;
	int m_age;
	int m_height;
	void display() {
		cout << "id =  " << m_id
			<< ", age = " << m_age 
			<< ", height = " << m_height << endl;
	}
};

int main() {
	Person person;
	person.m_id = 10;
	person.m_age = 20;
	person.m_height = 30;
	Person* p = (Person*)&person.m_age;
	p->m_id = 40;
	p->m_age = 50;
	person.display();
	getchar();
	return 0;
}
//int main() {
//	Person person;
//	person.m_id = 10;
//	person.m_age = 20;
//	person.m_height = 30;
//	person.display();
//
//	Person* p = &person;
//	p->m_id = 10;
//	p->m_age = 20;
//	p->m_height = 30;
//	getchar();
//	return 0;
//}

//int main() {
//	func();
//	Person person1;
//	person1.m_age = 10;
//	person1.run();
//
//	Person person2;
//	person2.m_age = 20;
//	person2.run();
//	getchar();
//	return 0;
//}