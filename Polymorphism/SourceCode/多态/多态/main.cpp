#include <iostream>
using namespace std;

struct Person {
	int m_age;
};

struct Student : Person {
	int m_score;
};

struct Animal {
	virtual void speak() {
		cout << "Animal::speak()" << endl;
	}

	virtual void run() {
		cout << "Animal::run()" << endl;
	}
};

struct Pig : Animal{
	void speak() {
		cout << "Pig::speak()" << endl;
	}

	void run() {
		cout << "Pig::run()" << endl;
	}
};

struct Dog : Animal {
	void speak() {
		cout << "Dog::speak()" << endl;
	}

	void run() {
		cout << "Dog::run()" << endl;
	}
};

struct Cat : Animal {
	void speak() {
		cout << "Cat::speak()" << endl;
	}

	void run() {
		cout << "Cat::run()" << endl;
	}
};

//void liu(Dog* p) {
//	p->speak();
//	p->run();
//}
//
//void liu(Cat* p) {
//	p->speak();
//	p->run();
//}
//
//void liu(Pig* p) {
//	p->speak();
//	p->run();
//}
void liu(Animal* p) {
	p->speak();
	p->run();
}

void test(){
	//Person* p = new Student;

	Student* p = (Student*)new Person;
	p->m_age = 10;
	p->m_score = 100;
}

int main() {
	Animal* p = new Dog();
	p->run();
	p->speak();
	liu(new Dog());
	getchar();
	return 0;
}
