#pragma once
#include "rational.h"

class Complex {
public:
	Complex(const Rational&);
	Complex(const Rational&, const Rational&);
	Complex(int real, int imaginary = 0);
	Complex(int64_t real, int64_t imaginary = 0);
	Complex(double real, double imaginary = 0);

	Rational GetRealPart() const;
	Rational GetImaginaryPart() const;

	void SetRealPart(const Rational&);
	void SetImaginaryPart(const Rational&);

	Complex operator+(const Complex&) const;
	Complex operator-(const Complex&) const;
	Complex operator*(const Complex&) const;
	Complex operator/(const Complex&) const;

	Complex& operator=(const Complex&);
	bool operator==(const Complex&) const;
	bool operator!=(const Complex&) const;
	Complex operator-();

	Complex& operator+=(const Complex&);
	Complex& operator*=(const Complex&);
	Complex& operator-=(const Complex&);
	Complex& operator/=(const Complex&);

	Complex pow(int) const;
	double abs() const;
	double arg() const;

	friend ostream& operator<<(ostream&, const Complex&);

private:
	Rational r_, img_;
};

