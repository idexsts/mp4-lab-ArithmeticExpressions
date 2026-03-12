#include <iostream>
using namespace std;

#include "Calc.h"


int main() {
	setlocale(LC_ALL, "Rus");
	string str = "9*9*9-(-9)";
	Calc c(str);
	try {
		c.Calculate();
		cout << "Result is: " << c.getRes() << endl;
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}

	return 0;
}
