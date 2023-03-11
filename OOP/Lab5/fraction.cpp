#include "fraction.h"
#include <sstream>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

Fraction::Fraction() 
{
	this->denominator	= 1;
	this->numerator		= 1;
};
Fraction::Fraction(const int &numerator, const int &denominator)
{
	this->denominator	= denominator;
	this->numerator		= numerator;
}
Fraction::Fraction(const Fraction &x)
{
	this->denominator	= x.denominator;
	this->numerator		= x.numerator;
}

Fraction::~Fraction(){};

int gcd(int a, int b)
{
	if (b == 0)
		return 1;
	int c = a % b;
	while (c)
	{
		a = b;
		b = c;
		c = a % b;
	}
	return b;
}

int lcm(int a, int b)
{
	return a / gcd(a, b) * b;
}

Fraction Fraction::reverse () const
{
	Fraction f;
	f.denominator	= this->numerator;
	f.numerator		= this->denominator;
	return f;
}

Fraction operator+ (const Fraction &a, const Fraction &b)
{
	Fraction f;
	int l			=	lcm(a.denominator, b.denominator);
	f.denominator	=	l;
	f.numerator		=	l / a.denominator * a.numerator + l / b.denominator * b.numerator;
	if (f.numerator == 0)
		return f;
	int g			=	gcd(f.denominator, f.numerator);
	f.denominator	/=	g;
	f.numerator		/=	g;
	return f;
}

Fraction operator- (const Fraction &a, const Fraction &b)
{
	Fraction f;
	int l			=	lcm(a.denominator, b.denominator);
	f.denominator	=	l;
	f.numerator		=	l / a.denominator * a.numerator - l / b.denominator * b.numerator;
	if (f.numerator == 0)
		return f;
	int g			=	gcd(f.denominator, f.numerator);
	f.denominator	/=	g;
	f.numerator		/=	g;
	return f;
}

Fraction operator * (const Fraction &a, const Fraction &b)
{
	Fraction f;
	f.denominator	= a.denominator * b.denominator;
	f.numerator		= a.numerator * b.numerator;
	int l			= gcd(f.denominator, f.numerator);
	f.denominator	/= l;
	f.numerator		/= l;
	return f;
}

Fraction operator / (const Fraction &a, const Fraction &b)
{
	Fraction f = b.reverse();
	return a * f;
}

bool operator < (const Fraction &a, const Fraction &b)
{
	int l = lcm(a.denominator, b.denominator);
	Fraction fa(l / a.denominator * a.numerator, l), fb(l / b.denominator * b.numerator, l);
	return fa.numerator < fb.numerator;
}

bool operator <= (const Fraction &a, const Fraction &b)
{
	int l = lcm(a.denominator, b.denominator);
	Fraction fa(l / a.denominator * a.numerator, l), fb(l / b.denominator * b.numerator, l);
	return fa.numerator <= fb.numerator;
}

bool operator == (const Fraction &a, const Fraction &b)
{
	int l = lcm(a.denominator, b.denominator);
	Fraction fa(l / a.denominator * a.numerator, l), fb(l / b.denominator * b.numerator, l);
	return fa.numerator == fb.numerator;
}

bool operator != (const Fraction &a, const Fraction &b)
{
	int l = lcm(a.denominator, b.denominator);
	Fraction fa(l / a.denominator * a.numerator, l), fb(l / b.denominator * b.numerator, l);
	return fa.numerator != fb.numerator;
}

bool operator >= (const Fraction &a, const Fraction &b)
{
	int l = lcm(a.denominator, b.denominator);
	Fraction fa(l / a.denominator * a.numerator, l), fb(l / b.denominator * b.numerator, l);
	return fa.numerator >= fb.numerator;
}

bool operator > (const Fraction &a, const Fraction &b)
{
	int l = lcm(a.denominator, b.denominator);
	Fraction fa(l / a.denominator * a.numerator, l), fb(l / b.denominator * b.numerator, l);
	return fa.numerator > fb.numerator;
}

ostream& operator << (ostream &os, const Fraction &a)
{
	os<<static_cast<string>(a);
	return os;
}

istream & operator >> (istream &is, Fraction &a)
{
	is>>a.numerator>>a.denominator;
	return is;
}

Fraction::operator string() const
{
	stringstream s;
	if (this->numerator == 0)
	{
		s << '0';
		return s.str();
	}
	s << this->numerator << " / " << this->denominator;
	return s.str();
}

Fraction::operator double() const
{
	return (double)this->numerator / this->denominator;
}