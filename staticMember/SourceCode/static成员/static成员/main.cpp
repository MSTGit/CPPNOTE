#include <iostream>
using namespace std;

class Car {
public:
	int m_age;
	static int m_price;
	static void run() {
		cout << "run()" << endl;
	}
};

int Car::m_price = 0;
void test() {
	//Car car;
//car.run();

//Car* p = &car;
//car.run();
//
//Car::run();

	//Car car2;
//car2.m_price = 200;

//Car::m_price = 300;

//Car* p = new Car();
//p->m_price = 400;
//delete p;
}
int g_age;
int main() {


	Car car;
	car.m_age = 1;
	car.m_price = 2;
	g_age = 3;

	getchar();
	return 0;
}
