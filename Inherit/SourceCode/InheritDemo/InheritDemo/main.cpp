#include <iostream>
using namespace std;

//struct Person {
//	int m_age;
//	void run() {
//
//	}
//};
//
//struct Student : Person {
//	int m_score;
//
//
//	void study() {
//	
//	}
//};

struct Person {
	int m_age;

};

struct Student : Person {
	int m_no;
};

struct GoodStudent : Student {
	int m_money;
};

struct Worker : Person {
	int m_salary;
	void work() {
	
	}
};
int main() {
	Student student;
	student.m_age = 20;
	student.m_score = 100;
	student.run();
	student.study();
	getchar();
	return 0;
}
