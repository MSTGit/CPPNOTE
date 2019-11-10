#include <iostream>
using namespace std;

struct Person {
private:
	int m_age;
public:
	void setAge(int age) {
		if (age <= 0) {
			return;
		}
		m_age = age;
	}

	int getAge() {
		return m_age;
	}
};

int main() {
	Person person;
	person.setAge(10);
	int age = person.getAge();
	getchar();
	return 0;
}