#include <iostream>
using namespace std;

//void swap(int* v1, int* v2) {
//	int tmp = *v1;
//	*v2 = *v1;
//	*v1 = tmp;
//}
void swap(int& v1, int& v2) {
	int tmp = v1;
	v2 = v1;
	v1 = tmp;
}

struct Student {
	int age;
};

//int main() {
//	//cout << sizeof(Student) << endl;
//	int age = 10;
//	
//	int* p = &age;
//	*p = 30;
//
//	int& ref = age;
//	ref = 40;
//
//	//int a = 10;
//	//int b = 20;
//	//swap(a, b);
//	//int age = 10;
//	////定义了一个age的引用
//	//int& refAge = age;
//	//refAge = 20;
//	//cout << age << endl;
//	getchar();
//	return 0;
//}

int main() {
	int age = 10;
	int* p = &age;
	*p = 30;

	/*int& ref = age;
	ref = 40;*/
	getchar();
	return 0;
}
