#include "rational.h"

Rational::Rational() : Rational((int64_t)0) { }

Rational::Rational(int num) : Rational((int64_t)num) { }

Rational::Rational(int64_t num) {
    numerator_ = num;
    denominator_ = 1;
}

Rational::Rational(int64_t numerator, int64_t denominator) {
    if (denominator == 0) throw invalid_argument("Invalid syntax: denominator equals to zero");

    int64_t gcd_of_numbers = GCD(std::abs(numerator), std::abs(denominator));

    numerator_ = numerator / gcd_of_numbers;
    denominator_ = denominator / gcd_of_numbers;

    if (denominator_ < 0) {
        denominator_ = -denominator_;
        numerator_ = -numerator_;
    }
}

Rational::Rational(double num) {
    auto max_size = 1000000;
    numerator_ = (int64_t)(num * max_size);
    denominator_ = max_size;

    *this = Rational(numerator_, denominator_);
}

int64_t Rational::Numerator() const {
    return numerator_;
}

int64_t Rational::Denominator() const {
    return denominator_;
}

bool Rational::operator==(const Rational& other) const {
    return this->numerator_ == other.numerator_ && this->denominator_ == other.denominator_;
}

Rational Rational::operator+(const Rational& other) const {
    return { this->numerator_ * other.denominator_ + other.numerator_ * this->denominator_,
            this->denominator_ * other.denominator_ };
}

Rational Rational::operator-(const Rational& other) const {
    return { this->numerator_ * other.denominator_ - other.numerator_ * this->denominator_,
            this->denominator_ * other.denominator_ };
}

Rational Rational::operator*(const Rational& other) const {
    return { numerator_ * other.numerator_,
            denominator_ * other.denominator_ };
}

Rational Rational::operator/(const Rational& other) const {
    if (other.numerator_ == 0) throw domain_error("Domain error: division by zero");

    return { numerator_ * other.denominator_,
            denominator_ * other.numerator_ };
}

Rational Rational::operator-() {
    return { -this->numerator_, this->denominator_ };
}

ostream& operator<<(ostream& stream, const Rational& rational_number) {
    stream << rational_number.numerator_ << '/' << rational_number.denominator_;

    return stream;
}

int64_t Rational::GCD(int64_t a, int64_t b) const {
    while (a != 0 && b != 0) {
        if (a >= b) {
            a %= b;
        }
        else {
            b %= a;
        }
    }

    return a + b;
}

double Rational::ToDouble() const {
    return this->numerator_ / (double)this->denominator_;
}

Rational Rational::abs() const {
    return { std::abs(this->numerator_), this->denominator_ };
}
