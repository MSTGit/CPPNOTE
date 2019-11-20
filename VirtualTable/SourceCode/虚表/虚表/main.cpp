#include <iostream>
using namespace std;

struct Animal {
	int m_age;
	void speak() {
		cout << "Animal::speak()" << endl;
	}

	void run() {
		cout << "Animal::run()" << endl;
	}

	Animal() {
		cout << "Animal::Animal()" << endl;
	}
	virtual ~Animal() {
		cout << "Animal::~Animal()" << endl;
	}
};

struct Cat : Animal {
	int m_life;
	void speak() {
		cout << "Cat::speak()" << endl;
	}

	void run() {
		cout << "Cat::run()" << endl;
	}

	Cat() {
		cout << "Cat::Cat()" << endl;
	}
	~Cat() {
		cout << "Cat::~Cat()" << endl;
	}
};

int main() {

	/*cout << sizeof(Cat) << endl;*/
	Animal* cat = new Cat();

	cat->m_age = 20;
	cat->speak();
	cat->run();
	delete cat;
	getchar();
	return 0;
}
