#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;

class Rational {
public:
	Rational();
	Rational(int);
	Rational(int64_t);
	Rational(int64_t, int64_t);
	Rational(double);

	int64_t Numerator() const;
	int64_t Denominator() const;

	bool operator==(const Rational&) const;

	Rational operator+(const Rational&) const;
	Rational operator-(const Rational&) const;
	Rational operator*(const Rational&) const;
	Rational operator/(const Rational&) const;

	Rational operator-();

	double ToDouble() const;
	Rational abs() const;

	friend ostream& operator<<(ostream&, const Rational&);
private:
	int64_t numerator_, denominator_;
	int64_t GCD(int64_t, int64_t) const;
};

