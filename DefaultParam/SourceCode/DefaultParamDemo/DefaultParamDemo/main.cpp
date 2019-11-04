#include <iostream>
using namespace std;

//int sum(int v1 = 5, int v2 = 6);


void test(int a) {
	cout << "test(int) - " << a << endl;
}

void func(int v1, void(*p)(int) = test) {
	p(v1);
}


//
void display(int a, int b = 20) {
	cout << "a is " << a << endl;
}

void display(int a) {
	cout << "a is " << a << endl;
}

int sum(int v1, int v2 = 4) {
	return v1 + v2;
}

int main() {

	sum(1);
	sum(1, 4);

	/*void(*p)(int) = test;
	p(10);

	func(20,test);
	func(30);
	cout << sum(10, 20) << endl;


	sum(1, 20);
	sum(2, 20);
	sum(3, 20);
	sum(4, 20);
	sum(5, 20);
	sum(6, 15);
	sum(7, 20)*/;

	//display(10);
	getchar();
	return 0;
}