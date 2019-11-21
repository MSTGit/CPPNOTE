#include <iostream>
using namespace std;

//struct Person {
//	int m_age;
//};
//
//struct Student : Person {
//	int m_score;
//};
//
//struct Worker : Person {
//	int m_salary;
//};

struct Person {
	int m_age;
};

struct Student : virtual Person {
	int m_score;
};

struct Worker :virtual Person {
	int m_salary;
};

struct Undergraduate : Student, Worker {
	int m_grade;
};
int main() {

	Undergraduate ug;
	ug.m_age;
	cout << "Hello World!" << endl;
	getchar();
	return 0;
}
