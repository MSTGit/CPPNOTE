#include <iostream>
using namespace std;
//struct Student {
//	int m_score;
//	Student(int score) :m_score(score) {}
//	void study() {
//		cout << "Student::study()" << m_score << endl;
//	}
//};
//
//struct Worker {
//	int m_salary;
//	Worker(int salary) :m_salary(salary) {}
//	void work() {
//		cout << "Worker::work()" << m_salary << endl;
//	}
//};
//
//struct Undergraduate : Student ,Worker {
//	int m_grade;
//	Undergraduate(int score , int salary ,int grade) :Student(score) , Worker(salary) ,m_grade(grade) {}
//	void play() {
//		cout << "Undergraduate::play()" << m_grade << endl;
//	}
//};

//class Student{
//public:
//	virtual void study() {
//		cout << "Student::study()" << endl;
//	}
//};
//
//class Worker {
//public:
//	virtual void work() {
//		cout << "Worker::work()" << endl;
//	}
//};
//
//class Undergraduate : Student, Worker {
//	void play() {
//		cout << "Undergraduate::play()" << endl;
//	}
//
//	void study() {
//		cout << "Undergraduate::study()" << endl;
//	}
//
//	void work() {
//		cout << "Undergraduate::work()" << endl;
//	}
//};

//class Student {
//public:
//	void eat() {
//		cout << "Student::eat()" << endl;
//	}
//};
//
//class Worker {
//public:
//	void eat() {
//		cout << "Worker::eat()" << endl;
//	}
//};
//
//class Undergraduate : public Student, public Worker {
//public:
//	void eat() {
//		cout << "Undergraduate::eat()" << endl;
//	}
//};
class Student {
public:
	int m_age;
};

class Worker {
public:
	int m_age;
};

class Undergraduate : public Student, public Worker {
public:
	int m_age;
};

int main() {
	Undergraduate ug;
	ug.m_age = 10;
	ug.Student::m_age = 20;
	ug.Worker::m_age = 30;
	/*Undergraduate ug;
	ug.eat();
	ug.Student::eat();
	ug.Worker::eat();*/

	//Undergraduate ug;
	//ug.m_score = 100;
	//ug.m_salary = 2000;
	//ug.m_grade = 4;
	//ug.study();
	//ug.work();
	//ug.play();
	getchar();
	return 0;
}
