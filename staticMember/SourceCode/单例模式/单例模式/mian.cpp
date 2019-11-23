#include <iostream>
using namespace std;


class Rocket {

private :
	Rocket() {};
	static Rocket* g_rocket;
public:
	static Rocket* sharedRocket() {
		if (g_rocket == NULL) {
			g_rocket = new Rocket();
		}
		return g_rocket;
	}

};
Rocket* Rocket::g_rocket = NULL;
int main() {
	Rocket* p1 = Rocket::sharedRocket();
	Rocket* p2 = Rocket::sharedRocket();
	Rocket* p3 = Rocket::sharedRocket();
	Rocket* p4 = Rocket::sharedRocket();
	Rocket* p5 = Rocket::sharedRocket();
	cout << p1 <<endl;
	cout << p2 << endl;
	cout << p3 << endl;
	cout << p4 << endl;
	cout << p5 << endl;
	getchar();
	return 0;
}
