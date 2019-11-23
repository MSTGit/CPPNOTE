#include <iostream>
using namespace std;
class Car {
public:
	//const int m_price = 10;
	int m_price;
	//Car() :m_price(0) {
	//}
	void run() const{
		cout << "run() const" << endl;
		//m_price = 0;//这种方式是不允许的
		//test();//这种调用方式是不允许的
	}

	void run() {

		cout << "run()" << endl;
	}

	static void test() {
	}
};
int main() {
	Car car;
	car.run();//调用普通的成员函数


	const Car car2;
	car2.run();//调用const修饰的静态成员函数
	car2.test();
	getchar();
	return 0;
}
