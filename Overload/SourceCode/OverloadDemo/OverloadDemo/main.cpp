#include <iostream>
using namespace std;

int sum(int v1, int v2) {
	return v1 + v2;
}

int sum(int v1, int v2, int v3) {
	return v1 + v2 + v3;
}

void func(int v1, double v2) {
	cout << "func(int v1, double v2)" << endl;
}

//double func(int v1, double v2) {
//	cout << "func(int v1, double v2)" << endl;
//	return 0;
//}

void func(double v1, int v2) {
	cout << "func(double v1, int v2)" << endl;
}


void display(long a) {
	cout << "display(long) -" << a << endl;
}

void display(double a) {
	cout << "display(double) -" << a << endl;
}

void display(int a) {
	cout << "display(int) -" << a << endl;
}

void display() {
	cout << "display() -"<< endl;
}

int main() {
	//cout << sum(10, 20) << endl;
	//cout << sum(10, 20,30) << endl;

	//func(10, 10.5);
	//func(10.5, 10);

	display();
	display(10);
	display(10L);
	display(10.0);
	
	getchar();
	return 0;
}