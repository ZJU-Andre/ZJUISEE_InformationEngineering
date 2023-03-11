#ifndef FRACTION_H_
#define FRACTION_H_
#include <string>
#include <iostream>
using namespace std;

class Fraction{
protected :
	int denominator; //
	int numerator; //
	Fraction reverse() const;
public :
	Fraction();
	Fraction(const int &, const int &);
	Fraction(const Fraction &);
	~Fraction();
	friend Fraction operator + (const Fraction &, const Fraction &);
	friend Fraction operator - (const Fraction &, const Fraction &);
	friend Fraction operator * (const Fraction &, const Fraction &);
	friend Fraction operator / (const Fraction &, const Fraction &);
	friend bool operator < (const Fraction &, const Fraction &);
	friend bool operator <= (const Fraction &, const Fraction &);
	friend bool operator == (const Fraction &, const Fraction &);
	friend bool operator != (const Fraction &, const Fraction &);
	friend bool operator >= (const Fraction &, const Fraction &);
	friend bool operator > (const Fraction &, const Fraction &);
	friend ostream & operator << (ostream &, const Fraction &);
	friend istream & operator >> (istream &, Fraction &);
	operator string() const;
	operator double() const;

};

int gcd(int, int);
int lcm(int, int);

#endif