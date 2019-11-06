#include <iostream>
using namespace std;


struct Date {
	int year;
	int month;
	int day;
};

//int main() {
//
//	//const Date d = {2011, 2, 5};
//	//d.year = 2015;
//
//	//const int age;
//	//age = 20;
//
	//int age = 10;
	//const int* p0 = &age;
	//int const* p1 = &age;
	//int* const p2 = &age;
	//const int* const p3 = &age;
	//int const* const p4 = &age;
//	getchar();
//	return 0;
//}

int main() {
	int age = 10;
	int height = 30;
	int age = 10;
	const int* p0 = &age;
	int const* p1 = &age;
	int* const p2 = &age;
	const int* const p3 = &age;
	int const* const p4 = &age;
	*p0 = 20;
	p0 = &height;
	*p0 = 40;
	getchar();
	return 0;
}
