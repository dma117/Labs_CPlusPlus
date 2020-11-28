#include "complex.h"
#include <cmath>

Complex::Complex(const Rational& real) : Complex(real, 0) { }

Complex::Complex(const Rational& real, const Rational& imaginary) {
    r_ = real;
    img_ = imaginary;
}

Complex::Complex(int real, int imaginary) : Complex((int64_t)real, (int64_t)imaginary) { }

Complex::Complex(int64_t real, int64_t imaginary) {
    r_ = real;
    img_ = imaginary; 
}

Complex::Complex(double real, double imaginary) {
    r_ = real;
    img_ = imaginary;
}

Rational Complex::GetRealPart() const {
    return this->r_;
}

Rational Complex::GetImaginaryPart() const {
    return this->img_;
}

void Complex::SetRealPart(const Rational& new_rational) {
    this->r_ = new_rational;
}

void Complex::SetImaginaryPart(const Rational& new_rational) {
    this->img_ = new_rational;
}

Complex Complex::operator+(const Complex& other) const {
    return { this->r_ + other.r_, this->img_ + other.img_ };
}

Complex Complex::operator-(const Complex& other) const {
    return { this->r_ - other.r_, this->img_ - other.img_ };
}

Complex Complex::operator*(const Complex& other) const {
    return { this->r_ * other.r_ - this->img_ * other.img_,
            this->r_ * other.img_ + other.r_ * this->img_ };
}

Complex Complex::operator/(const Complex& other) const {
    Rational denominator = other.r_ * other.r_ + other.img_ * other.img_;

    if (denominator == 0) throw invalid_argument("Cannot divide by zero");

    return { (this->r_ * other.r_ + this->img_ * other.img_) / denominator,
            (other.r_ * this->img_ - this->r_ * other.img_) / denominator };
}

Complex& Complex::operator=(const Complex& other) {
    this->r_ = other.r_;
    this->img_ = other.img_;

    return *this;
}

bool Complex::operator==(const Complex& other) const {
    return this->r_ == other.r_ && this->img_ == other.img_;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

ostream& operator<<(ostream& stream, const Complex& complex_number) {
    char sign = '+';

    if (complex_number.img_.Numerator() < 0) {
        sign = '-';
    }

    if (complex_number.img_ == 0) {
        return stream << complex_number.r_;
    }

    return stream << complex_number.r_ << ' ' << sign << ' ' << complex_number.img_.abs() << 'i';
}
Complex Complex::operator-() {
    return {-this->r_, -this->img_};
}

Complex& Complex::operator+=(const Complex& other) {
    *this = *this + other;

    return *this;
}
Complex& Complex::operator*=(const Complex& other) {
    *this = *this * other;

    return *this;
}
Complex& Complex::operator-=(const Complex& other) {
    *this = *this - other;

    return *this;
}
Complex& Complex::operator/=(const Complex& other) {
    *this = *this / other;

    return *this;
}

Complex Complex::pow(int power) const {
    if (power <= 0) throw invalid_argument("The value of power should be natural");

    auto result = *this;

    for (int i = 0; i < power - 1; i++) {
        result *= *this;
    }

    return result;
}

double Complex::abs() const {
    return sqrt((this->r_ * this->r_ + this->img_ * this->img_).ToDouble());
}

double Complex::arg() const {
    if (*this == 0) throw invalid_argument("arg of zero value is not defined");

    return atan2(this->img_.ToDouble(), this->r_.ToDouble());
}
