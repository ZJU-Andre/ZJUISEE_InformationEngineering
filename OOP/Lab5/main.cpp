#include "fraction.h"
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	Fraction a(1, 2);
	Fraction b(2, 3);
	Fraction c = a / b;
	cout<<(double)c;
	system("pause");
	return 0;
}