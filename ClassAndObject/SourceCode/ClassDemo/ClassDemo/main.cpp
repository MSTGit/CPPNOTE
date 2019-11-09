#include <iostream>
using namespace std;

struct Person {
	int m_id;
	int m_age;
	int m_height;
	void display() {
		cout << "id =" << m_id 
			<< ",age =" << m_age 
			<< ",height =" << m_height << endl;
	}
};

int main() {
	Person person;
	person.m_id = 1;
	person.m_age = 2;
	person.m_height = 3;
	cout << "&person == " << &person << endl;
	cout << "&perosn.m_id == " << &person.m_id << endl;
	cout << "&perosn.m_age == " << &person.m_age << endl;
	cout << "&perosn.m_height == " << &person.m_height << endl;
	//cout << sizeof(Person) << endl;
	return 0;
}


