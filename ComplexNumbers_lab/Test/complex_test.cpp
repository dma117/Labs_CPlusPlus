#include "../catch.hpp"
#include "../Numbers/complex.h"
#include "../Numbers/rational.h"
#include <sstream>
#define TEST_PREFIX "Complex::"


TEST_CASE(TEST_PREFIX "constructors", "[complex]") {
    SECTION("Rational") {
        {
            const Complex c(Rational(288, 108));
            REQUIRE(c.GetRealPart() == Rational(288, 108));
            REQUIRE(c.GetImaginaryPart() == Rational(0));
        }
        {
            const Complex c(Rational(-177777, 98888));
            REQUIRE(c.GetRealPart() == Rational(-177777, 98888));
            REQUIRE(c.GetImaginaryPart() == Rational(0));
        }
        {
            const Complex c(Rational(0));
            REQUIRE(c.GetRealPart() == Rational(0));
            REQUIRE(c.GetImaginaryPart() == Rational(0));
        }
        {
            const Complex c(Rational(-1777779999));
            REQUIRE(c.GetRealPart() == Rational(-1777779999));
            REQUIRE(c.GetImaginaryPart() == Rational(0));
        }
    }
    SECTION("Rational and Rational") {
        {
            const Complex c(Rational(1555, 7878), Rational(9000, 12333));
            REQUIRE(c.GetRealPart() == Rational(1555, 7878));
            REQUIRE(c.GetImaginaryPart() == Rational(9000, 12333));
        }
        {
            const Complex c(Rational(-255, 1444), Rational(8989, -9999));
            REQUIRE(c.GetRealPart() == Rational(-255, 1444));
            REQUIRE(c.GetImaginaryPart() == Rational(8989, -9999));
        }
        {
            const Complex c(Rational(155), Rational(-8989));
            REQUIRE(c.GetRealPart() == Rational(155));
            REQUIRE(c.GetImaginaryPart() == Rational(-8989));
        }
    }
    SECTION("int64_t") {
        {
            const Complex c(55555);
            REQUIRE(c.GetRealPart() == Rational(55555));
            REQUIRE(c.GetImaginaryPart() == Rational(0));
        }
        {
            const Complex c(-119158);
            REQUIRE(c.GetRealPart() == Rational(-119158));
            REQUIRE(c.GetImaginaryPart() == Rational(0));
        }
    }
    SECTION("int64_t and int64_t") {
        {
            const Complex c(144, 52);
            REQUIRE(c.GetRealPart() == Rational(144));
            REQUIRE(c.GetImaginaryPart() == Rational(52));
        }
        {
            const Complex c(-33, 66);
            REQUIRE(c.GetRealPart() == Rational(-33));
            REQUIRE(c.GetImaginaryPart() == Rational(66));
        }
    }
    SECTION("double") {
        {
            const Complex c(144.222);
            REQUIRE(c.GetRealPart() == Rational(144.222));
            REQUIRE(c.GetImaginaryPart() == Rational(0));
        }
        {
            const Complex c(-3.4);
            REQUIRE(c.GetRealPart() == Rational(-3.4));
            REQUIRE(c.GetImaginaryPart() == Rational(0));
        }
    }
    SECTION("double and double") {
        {
            const Complex c(-3.4, 199.99);
            REQUIRE(c.GetRealPart() == Rational(-3.4));
            REQUIRE(c.GetImaginaryPart() == Rational(199.99));
        }
        {
            const Complex c(3.4, -199.99);
            REQUIRE(c.GetRealPart() == Rational(3.4));
            REQUIRE(c.GetImaginaryPart() == Rational(-199.99));
        }
    }
}

TEST_CASE(TEST_PREFIX "operator ostream", "[complex]") {
    {
        ostringstream output;
        output << Complex({ -15, 8923 }, { 88, 19999 });
        REQUIRE(output.str() == ("-15/8923 + 88/19999i"));
    }
    {
        ostringstream output;
        output << Complex(5, { -88, 19999 });
        REQUIRE(output.str() == ("5/1 - 88/19999i"));
    }
    {
        ostringstream output;
        output << Complex(-11);
        REQUIRE(output.str() == ("-11/1"));
    }
    {
        ostringstream output;
        output << Complex({ 1, 2 }, -11.99);
        REQUIRE(output.str() == ("1/2 - 1199/100i"));
    }
    {
        ostringstream output;
        output << Complex(-67.123);
        REQUIRE(output.str() == ("-67123/1000"));
    }
}

TEST_CASE(TEST_PREFIX "set real part", "[complex]") {
    {
        Complex c(144);
        c.SetRealPart(22.5);
        REQUIRE(c.GetRealPart() == Rational(22.5));
    }
    {
        Complex c({ 1499, 1239 }, { 12,444 });
        c.SetRealPart(22.5);
        REQUIRE(c.GetRealPart() == Rational(22.5));
    }
    {
        Complex c({ 1499, 1239 }, 12.444);
        c.SetRealPart(4.5);
        REQUIRE(c.GetRealPart() == Rational(4.5));
    }
    {
        Complex c(1, 222);
        c.SetRealPart(22.5);
        REQUIRE(c.GetRealPart() == Rational(22.5));
    }
    {
        Complex c(144.77);
        c.SetRealPart({14, 5});
        REQUIRE(c.GetRealPart() == Rational(14, 5));
    }
    {
        Complex c(144.777);
        c.SetRealPart(-7123.11);
        REQUIRE(c.GetRealPart() == Rational(-7123.11));
    }
}

TEST_CASE(TEST_PREFIX "set imaginary part", "[complex]") {
    {
        Complex c(144);
        c.SetImaginaryPart(22.5);
        REQUIRE(c.GetImaginaryPart() == Rational(22.5));
    }
    {
        Complex c({ 1499, 1239 }, { 12,444 });
        c.SetImaginaryPart(22.5);
        REQUIRE(c.GetImaginaryPart() == Rational(22.5));
    }
    {
        Complex c({ 1499, 1239 }, 12.444);
        c.SetImaginaryPart(4.5);
        REQUIRE(c.GetImaginaryPart() == Rational(4.5));
    }
    {
        Complex c(1, 222);
        c.SetImaginaryPart(22.5);
        REQUIRE(c.GetImaginaryPart() == Rational(22.5));
    }
    {
        Complex c(144.77);
        c.SetImaginaryPart({ 14, 5 });
        REQUIRE(c.GetImaginaryPart() == Rational(14, 5));
    }
    {
        Complex c(144.777);
        c.SetImaginaryPart(-7123.11);
        REQUIRE(c.GetImaginaryPart() == Rational(-7123.11));
    }
}

TEST_CASE(TEST_PREFIX "operator +", "[complex]") {
    {
        Complex c1(1899, 5);
        Complex c2(10, 55);
        REQUIRE(c1 + c2 == Complex(1909, 60));
    }
    {
        Complex c1(637373, 1231);
        Complex c2(31444444, 12);
        REQUIRE(c1 + c2 == Complex(32081817, 1243));
    }
    {
        Complex c1(-1899, 5);
        Complex c2(10, 55);
        REQUIRE(c1 + c2 == Complex(-1889, 60));
    }
    {
        Complex c1(19, 0);
        Complex c2(-10, 99);
        REQUIRE(c1 + c2 == Complex(9, 99));
    }
    {
        Complex c1(-17238, 12333);
        Complex c2(-10000, 55111);
        REQUIRE(c1 + c2 == Complex(-27238, 67444));
    }
    {
        Complex c1(-8823, 122);
        Complex c2(-100, 100);
        REQUIRE(c1 + c2 == Complex(-8923, 222));
    }
    {
        Complex c1(8823, -122);
        Complex c2(100, 100);
        REQUIRE(c1 + c2 == Complex(8923, -22));
    }
    {
        Complex c1(8823, 122);
        Complex c2(100, -100);
        REQUIRE(c1 + c2 == Complex(8923, 22));
    }
    {
        Complex c1(8823, -122);
        Complex c2(100, -100);
        REQUIRE(c1 + c2 == Complex(8923, -222));
    }
    {
        Complex c1(8823, -122);
        Complex c2(-100, -100);
        REQUIRE(c1 + c2 == Complex(8723, -222));
    }
    {
        Complex c1(-8823, -122);
        Complex c2(-100, -100);
        REQUIRE(c1 + c2 == Complex(-8923, -222));
    }
    {
        Complex c1(-8823, -122);
        Complex c2(-100, 100);
        REQUIRE(c1 + c2 == Complex(-8923, -22));
    }
    {
        Complex c1(8823);
        Complex c2(-100, 100);
        REQUIRE(c1 + c2 == Complex(8723, 100));
    }
    {
        Complex c1(-8823);
        Complex c2(-100, 100);
        REQUIRE(c1 + c2 == Complex(-8923, 100));
    }
    {
        Complex c1(8823);
        Complex c2(100);
        REQUIRE(c1 + c2 == Complex(8923));
    }
    {
        Complex c1(8823.99, 123.53333);
        Complex c2(100.11, 123123.2);
        REQUIRE(c1 + c2 == Complex(8924.1, 123246.73333));
    }
    {
        Complex c1(-8823.99, 123.53333);
        Complex c2(-100.11, 123123.2);
        auto result = c1 + c2;
        REQUIRE(result.GetRealPart().ToDouble() == (Approx(-8924.1).epsilon(0.01)));
        REQUIRE(result.GetImaginaryPart().ToDouble() == (Approx(123246.73333).epsilon(0.01)));
    }
    {
        Complex c1(999.2, 1231.0);
        Complex c2(-100.11, 123123.2);
        REQUIRE(c1 + c2 == Complex(899.09, 124354.2));
    }
    {
        Complex c1(999.2, -1231.0);
        Complex c2(-100.11, 123123.2);
        REQUIRE(c1 + c2 == Complex(899.09, 121892.2));
    }
    {
        Complex c1(5);
        Complex c2(-100.11, 123123.2);
        REQUIRE(c1 + c2 == Complex(-95.11, 123123.2));
    }
    {
        Complex c1(5);
        Complex c2(-100.11, 3.0);
        REQUIRE(c1 + c2 == Complex(-95.11, 3.0));
    }
}

TEST_CASE(TEST_PREFIX "operator +=", "[complex]") {
    {
        Complex c1(1899, 5);
        Complex c2(10, 55);
        c1 += c2;
        REQUIRE(c1 == Complex(1909, 60));
        REQUIRE(c2 == Complex(10, 55));
    }
    {
        Complex c1(637373, 1231);
        Complex c2(31444444, 12);
        c1 += c2;
        REQUIRE(c1 == Complex(32081817, 1243));
        REQUIRE(c2 == Complex(31444444, 12));
    }
    {
        Complex c1(-1899, 5);
        Complex c2(10, 55);
        c1 += c2;
        REQUIRE(c1 == Complex(-1889, 60));
        REQUIRE(c2 == Complex(10, 55));
    }
    {
        Complex c1(19, 0);
        Complex c2(-10, 99);
        c1 += c2;
        REQUIRE(c1 == Complex(9, 99));
        REQUIRE(c2 == Complex(-10, 99));
    }
    {
        Complex c1(-17238, 12333);
        Complex c2(-10000, 55111);
        c1 += c2;
        REQUIRE(c1 == Complex(-27238, 67444));
        REQUIRE(c2 == Complex(-10000, 55111));
    }
    {
        Complex c1(-8823, 122);
        Complex c2(-100, 100);
        c1 += c2;
        REQUIRE(c1 == Complex(-8923, 222));
        REQUIRE(c2 == Complex(-100, 100));
    }
    {
        Complex c1(8823, -122);
        Complex c2(100, 100);
        c1 += c2;
        REQUIRE(c1 == Complex({8923, -22}));
        REQUIRE(c2 == Complex({100, 100}));
    }
    {
        Complex c1(8823, 122);
        Complex c2(100, -100);
        c1 += c2;
        REQUIRE(c1 == Complex(8923, 22));
        REQUIRE(c2 == Complex({100, -100}));
    }
    {
        Complex c1(8823, -122);
        Complex c2(100, -100);
        c1 += c2;
        REQUIRE(c1 == Complex(8923, -222));
        REQUIRE(c2 == Complex({100, -100}));
    }
    {
        Complex c1(8823, -122);
        Complex c2(-100, -100);
        c1 += c2;
        REQUIRE(c1 == Complex(8723, -222));
        REQUIRE(c2 == Complex({-100, -100}));
    }
    {
        Complex c1(-8823, -122);
        Complex c2(-100, -100);
        c1 += c2;
        REQUIRE(c1 == Complex(-8923, -222));
        REQUIRE(c2 == Complex(-100, -100));
    }
    {
        Complex c1(-8823, -122);
        Complex c2(-100, 100);
        c1 += c2;
        REQUIRE(c1 == Complex(-8923, -22));
        REQUIRE(c2 == Complex(-100, 100));
    }
    {
        Complex c1(8823);
        Complex c2(-100, 100);
        c1 += c2;
        REQUIRE(c1 == Complex(8723, 100));
        REQUIRE(c2 == Complex(-100, 100));
    }
    {
        Complex c1(-8823);
        Complex c2(-100, 100);
        c1 += c2;
        REQUIRE(c1 == Complex(-8923, 100));
        REQUIRE(c2 == Complex(-100, 100));
    }
    {
        Complex c1(8823);
        Complex c2(100);
        c1 += c2;
        REQUIRE(c1 == Complex(8923));
        REQUIRE(c2 == Complex(100));
    }
    {
        Complex c1(8823.99, 123.53333);
        Complex c2(100.11, 123123.2);
        c1 += c2;
        REQUIRE(c1 == Complex(8924.1, 123246.73333));
        REQUIRE(c2 == Complex(100.11, 123123.2));
    }
    {
        Complex c1(999.2, 1231.0);
        Complex c2(-100.11, 123123.2);
        c1 += c2;
        REQUIRE(c1 == Complex(899.09, 124354.2));
        REQUIRE(c2 == Complex(-100.11, 123123.2));
    }
    {
        Complex c1(999.2, -1231.0);
        Complex c2(-100.11, 123123.2);
        c1 += c2;
        REQUIRE(c1 == Complex(899.09, 121892.2));
        REQUIRE(c2 == Complex(-100.11, 123123.2));
    }
    {
        Complex c1(5);
        Complex c2(-100.11, 123123.2);
        c1 += c2;
        REQUIRE(c1 == Complex(-95.11, 123123.2));
        REQUIRE(c2 == Complex(-100.11, 123123.2));
    }
    {
        Complex c1(5);
        Complex c2(-100.11, 3.0);
        c1 += c2;
        REQUIRE(c1 == Complex(-95.11, 3.0));
        REQUIRE(c2 == Complex(-100.11, 3.0));
    }
   {
        Complex c1({ 5, 1 }, { -6, 1 });
        Complex c2({ -3, 1 }, { 2, 1 });

        c1 += c2;

        REQUIRE(c1.GetRealPart() == Rational(2, 1));
        REQUIRE(c1.GetImaginaryPart() == Rational(-4, 1));
        REQUIRE(c2.GetRealPart() == Rational(-3, 1));
        REQUIRE(c2.GetImaginaryPart() == Rational(2, 1));
    }
}

TEST_CASE(TEST_PREFIX "binary operator -", "[complex]") {
    {
        Complex c1(1899, 5);
        Complex c2(10, 55);
        REQUIRE(c1 - c2 == Complex(1889, -50));
    }
    {
        Complex c1(637373, 1231);
        Complex c2(31444444, 12);
        REQUIRE(c1 - c2 == Complex(-30807071, 1219));
    }
    {
        Complex c1(-1899, 5);
        Complex c2(10, 55);
        REQUIRE(c1 - c2 == Complex(-1909, -50));
    }
    {
        Complex c1(19, 0);
        Complex c2(-10, 99);
        REQUIRE(c1 - c2 == Complex(29, -99));
    }
    {
        Complex c1(17238, 12333);
        Complex c2(17238, 12333);
        REQUIRE(c1 - c2 == Complex(0));
    }
    {
        Complex c1(-8823, 122);
        Complex c2(-100, 100);
        REQUIRE(c1 - c2 == Complex(-8723, 22));
    }
    {
        Complex c1(8823, -122);
        Complex c2(100, 100);
        REQUIRE(c1 - c2 == Complex(8723, -222));
    }
    {
        Complex c1(8823, 122);
        Complex c2(100, -100);
        REQUIRE(c1 - c2 == Complex(8723, 222));
    }
    {
        Complex c1(8823, -122);
        Complex c2(100, -100);
        REQUIRE(c1 - c2 == Complex(8723, -22));
    }
    {
        Complex c1(8823, -122);
        Complex c2(-100, -100);
        REQUIRE(c1 - c2 == Complex(8923, -22));
    }
    {
        Complex c1(-8823, -122);
        Complex c2(-100, -100);
        REQUIRE(c1 - c2 == Complex(-8723, -22));
    }
    {
        Complex c1(-8823, -122);
        Complex c2(-100, 100);
        REQUIRE(c1 - c2 == Complex(-8723, -222));
    }
    {
        Complex c1(8823);
        Complex c2(-100, 100);
        REQUIRE(c1 - c2 == Complex(8923, -100));
    }
    {
        Complex c1(-8823);
        Complex c2(-100, 100);
        REQUIRE(c1 - c2 == Complex(-8723, -100));
    }
    {
        Complex c1(8823);
        Complex c2(100);
        REQUIRE(c1 - c2 == Complex(8723));
    }
    {
        Complex c1(8823.99, 123.533);
        Complex c2(100.11, 123123.2);
        REQUIRE(c1 - c2 == Complex(8723.88, -122999.667));
    }
    {
        Complex c1(999.2, -1231.0);
        Complex c2(-100.11, 123123.2);
        REQUIRE(c1 - c2 == Complex(1099.31, -124354.2));
    }
    {
        Complex c1(5);
        Complex c2(-100.11, 123123.2);
        REQUIRE(c1 - c2 == Complex(105.11, -123123.2));
    }
}

TEST_CASE(TEST_PREFIX "operator -=", "[complex]") {
    {
        Complex c1(1899, 5);
        Complex c2(10, 55);
        c1 -= c2;
        REQUIRE(c1 == Complex(1889, -50));
    }
    {
        Complex c1(-1899, 5);
        Complex c2(10, 55);
        c1 -= c2;
        REQUIRE(c1 == Complex(-1909, -50));
    }
    {
        Complex c1(-8823, 122);
        Complex c2(-100, 100);
        c1 -= c2;
        REQUIRE(c1 == Complex(-8723, 22));
    }
    {
        Complex c1(8823, -122);
        Complex c2(-100, -100);
        c1 -= c2;
        REQUIRE(c1 == Complex(8923, -22));
    }
    {
        Complex c1(8823.99, 123.533);
        Complex c2(100.11, 123123.2);
        c1 -= c2;
        REQUIRE(c1 == Complex(8723.88, -122999.667));
    }
    {
        Complex c1(5);
        Complex c2(-100.11, 123123.2);
        c1 -= c2;
        REQUIRE(c1 == Complex(105.11, -123123.2));
    }
}

TEST_CASE(TEST_PREFIX "operator *", "[complex]") {
    {
        Complex c1(1899, 5);
        Complex c2(10, 55);
        REQUIRE(c1 * c2 == Complex(18715, 104495));
    }
    {
        Complex c1(637373, 1231);
        Complex c2(31444444, 12);
        REQUIRE(c1 * c2 == Complex(20041839590840, 38715759040));
    }
    {
        Complex c1(-1899, 5);
        Complex c2(10, 55);
        REQUIRE(c1 * c2 == Complex(-19265, -104395));
    }
    {
        Complex c1(19, 0);
        Complex c2(-10, 99);
        REQUIRE(c1 * c2 == Complex(-190, 1881));
    }
    {
        Complex c1(17238, 12333);
        Complex c2(17238, 12333);
        REQUIRE(c1 * c2 == Complex(145045755, 425192508));
    }
    {
        Complex c1(-8823, 122);
        Complex c2(-100, 100);
        REQUIRE(c1 * c2 == Complex(870100, -894500));
    }
    {
        Complex c1(8823, -122);
        Complex c2(100, 100);
        REQUIRE(c1 * c2 == Complex(894500, 870100));
    }
    {
        Complex c1(8823, 122);
        Complex c2(100, -100);
        REQUIRE(c1 * c2 == Complex(894500, -870100));
    }
    {
        Complex c1(8823, -122);
        Complex c2(-100, -100);
        REQUIRE(c1 * c2 == Complex(-894500, -870100));
    }
    {
        Complex c1(-8823, -122);
        Complex c2(-100, -100);
        REQUIRE(c1 * c2 == Complex(870100, 894500));
    }
    {
        Complex c1(8823);
        Complex c2(-100, 100);
        REQUIRE(c1 * c2 == Complex(-882300, 882300));
    }
    {
        Complex c1(-8823);
        Complex c2(-100, 100);
        REQUIRE(c1 * c2 == Complex(882300, -882300));
    }
    {
        Complex c1(8823);
        Complex c2(100);
        REQUIRE(c1 * c2 == Complex(882300));
    }
    {
        Complex c1(999.2, 1231.0);
        Complex c2(-100.11, 123123.2);
        REQUIRE(c1 * c2 == Complex(-151664689.112, 122901466.03));
    }
    {
        Complex c1(999.2, -1231.0);
        Complex c2(-100.11, 123123.2);
        REQUIRE(c1 * c2 == Complex(151464629.288, 123147936.85));
    }
    {
        Complex c1(5);
        Complex c2(-100.11, 123123.2);
        REQUIRE(c1 * c2 == Complex(-500.55, 615616.0));
    }
}

TEST_CASE(TEST_PREFIX "operator *=", "[complex]") {
    {
        Complex c1(1899, 5);
        Complex c2(10, 55);
        c1 *= c2;
        REQUIRE(c1 == Complex(18715, 104495));
    }
    {
        Complex c1(637373, 1231);
        Complex c2(31444444, 12);
        c1 *= c2;
        REQUIRE(c1 == Complex(20041839590840, 38715759040));
    }
    {
        Complex c1(-1899, 5);
        Complex c2(10, 55);
        c1 *= c2;
        REQUIRE(c1 == Complex(-19265, -104395));
    }
    {
        Complex c1(19, 0);
        Complex c2(-10, 99);
        c1 *= c2;
        REQUIRE(c1 == Complex(-190, 1881));
    }
    {
        Complex c1(17238, 12333);
        Complex c2(17238, 12333);
        c1 *= c2;
        REQUIRE(c1 == Complex(145045755, 425192508));
    }
    {
        Complex c1(-8823, 122);
        Complex c2(-100, 100);
        c1 *= c2;
        REQUIRE(c1 == Complex(870100, -894500));
    }
    {
        Complex c1(8823, -122);
        Complex c2(100, 100);
        c1 *= c2;
        REQUIRE(c1 == Complex(894500, 870100));
    }
    {
        Complex c1(8823, 122);
        Complex c2(100, -100);
        c1 *= c2;
        REQUIRE(c1 == Complex(894500, -870100));
    }
    {
        Complex c1(8823, -122);
        Complex c2(-100, -100);
        c1 *= c2;
        REQUIRE(c1 == Complex(-894500, -870100));
    }
    {
        Complex c1(-8823, -122);
        Complex c2(-100, -100);
        c1 *= c2;
        REQUIRE(c1 == Complex(870100, 894500));
    }
    {
        Complex c1(-8823);
        Complex c2(-100, 100);
        c1 *= c2;
        REQUIRE(c1 == Complex(882300, -882300));
    }
    {
        Complex c1(88.23, 12.35);
        Complex c2(100.11, 123123.2);
        c1 *= c2;
        REQUIRE(c1 == Complex(-1511738.8147, 10864396.2945));
    }
    {
        Complex c1(999.2, -1231.0);
        Complex c2(-100.11, 123123.2);
        c1 *= c2;
        REQUIRE(c1 == Complex(151464629.288, 123147936.85));
    }
}

TEST_CASE(TEST_PREFIX "operator /", "[complex]") {
    {
        Complex c1(1899, 5);
        Complex c2(10, 55);
        auto result = c1 / c2;
        REQUIRE((Approx(result.GetRealPart().ToDouble()).epsilon(0.01)) == 6.1648);
        REQUIRE((Approx(result.GetImaginaryPart().ToDouble()).epsilon(0.01)) == -33.4064);
    }
    {
        Complex c1(17238, 12333);
        Complex c2(17238, 12333);
        REQUIRE(c1 / c2 == Complex(1));
    }
    {
        Complex c1(-8823, 122);
        Complex c2(-100, 100);
        REQUIRE(c1 / c2 == Complex(44.725, 43.505));
    }
    {
        Complex c1(8823, -122);
        Complex c2(100, 100);
        REQUIRE(c1 / c2 == Complex(43.505, -44.725));
    }
    {
        Complex c1(999.2, 1231.0);
        Complex c2(-100.11, 123123.2);
        auto result = c1 / c2;
        REQUIRE((Approx(result.GetRealPart().ToDouble()).epsilon(0.01)) == 0.00999);
        REQUIRE((Approx(result.GetImaginaryPart().ToDouble()).epsilon(0.01)) == -0.00812);
    }
}

TEST_CASE(TEST_PREFIX "operator /=", "[complex]") {
    {
        Complex c1(1899, 5);
        Complex c2(10, 55);
        c1 /= c2;
        REQUIRE((Approx(c1.GetRealPart().ToDouble()).epsilon(0.01)) == 6.1648);
        REQUIRE((Approx(c1.GetImaginaryPart().ToDouble()).epsilon(0.01)) == -33.4064);
    }
    {
        Complex c1(-1899, 5);
        Complex c2(10, 55);
        c1 /= c2;
        REQUIRE((Approx(c1.GetRealPart().ToDouble()).epsilon(0.01)) == -5.9888);
        REQUIRE((Approx(c1.GetImaginaryPart().ToDouble()).epsilon(0.01)) == 33.4384);
    }
    {
        Complex c1(17238, 12333);
        Complex c2(17238, 12333);
        c1 /= c2;
        REQUIRE(c1 == Complex(1));
    }
    {
        Complex c1(-8823, 122);
        Complex c2(-100, 100);
        c1 /= c2;
        REQUIRE(c1 == Complex(44.725, 43.505));
    }
    {
        Complex c1(8823, -122);
        Complex c2(100, 100);
        c1 /= c2;
        REQUIRE(c1 == Complex(43.505, -44.725));
    }
}

TEST_CASE(TEST_PREFIX "operator =", "[complex]") {
    {
        Complex c(144);
        c = Complex(22.5);
        REQUIRE(c.GetRealPart() == Rational(22.5));
        REQUIRE(c.GetImaginaryPart() == Rational(0));
    }
    {
        Complex c({ 1499, 1239 }, { 12, 444 });
        c = Complex({ 44.55 }, { -123, 22 });
        REQUIRE(c.GetRealPart() == Rational(44.55));
        REQUIRE(c.GetImaginaryPart() == Rational(-123, 22));
    }
    {
        Complex c({ 1499, 1239 }, 12.444);
        c = Complex(-555.6, -90123.111);
        REQUIRE(c.GetRealPart() == Rational(-555.6));
        REQUIRE(c.GetImaginaryPart() == Rational(-90123.111));
    }
    {
        Complex c(1, {144, -7});
        c = Complex(-9);
        REQUIRE(c.GetRealPart() == Rational(-9));
        REQUIRE(c.GetImaginaryPart() == Rational(0));
    }
}

TEST_CASE(TEST_PREFIX "operator ==", "[complex]") {
    {
        const Complex c1(155, 999);
        const Complex c2(155, 999);
        REQUIRE((c1 == c2) == true);
    }
    {
        const Complex c1(-155, 999);
        const Complex c2(155, 999);
        REQUIRE((c1 == c2) == false);
    }
    {
        const Complex c1(155, -999);
        const Complex c2(155, -999);
        REQUIRE((c1 == c2) == true);
    }
    {
        const Complex c1(155.0, 999.0);
        const Complex c2(155, 999);
        REQUIRE((c1 == c2) == true);
    }
    {
        const Complex c1({15, 77774}, {89, -123});
        const Complex c2({ 15, 77774 }, { 89, -123 });
        REQUIRE((c1 == c2) == true);
    }
    {
        const Complex c1({ 15 }, { 89, -123 });
        const Complex c2({ 15, 77774 }, { 89, -123 });
        REQUIRE((c1 == c2) == false);
    }
}

TEST_CASE(TEST_PREFIX "operator !=", "[complex]") {
    {
        const Complex c1(155, 999);
        const Complex c2(155, -999);
        REQUIRE((c1 != c2) == true);
    }
    {
        const Complex c1(155, 999);
        const Complex c2(155, 999);
        REQUIRE((c1 != c2) == false);
    }
    {
        const Complex c1(155, -999);
        const Complex c2(-155, -999);
        REQUIRE((c1 != c2) == true);
    }
    {
        const Complex c1(155.1, 999.0);
        const Complex c2(155, 999);
        REQUIRE((c1 != c2) == true);
    }
    {
        const Complex c1({ 15, 77774 }, { 89, -123 });
        const Complex c2({ 15, -77774 }, { 89, -123 });
        REQUIRE((c1 != c2) == true);
    }
    {
        const Complex c1({ 15 }, { 89, 123 });
        const Complex c2({ 15 }, { 89, 123 });
        REQUIRE((c1 != c2) == false);
    }
}

TEST_CASE(TEST_PREFIX "unar operator -", "[complex]") {
    {
        Complex c({ 144, 113 }, { 998, 1919 });
        REQUIRE((-c) == Complex({ -144, 113 }, { -998, 1919 }));
    }
    {
        Complex c({ -144, 113 }, { 998, 1919 });
        REQUIRE((-c) == Complex({ 144, 113 }, { -998, 1919 }));
    }
    {
        Complex c({ -1446, -1136 }, { 9986, -19196 });
        REQUIRE((-c) == Complex({ -1446, 1136 }, { 9986, 19196 }));
    }
    {
        Complex c(666.774, -881.2);
        REQUIRE((-c) == Complex(-666.774, 881.2));
    }
    {
        Complex c(0., 666.774);
        REQUIRE((-c) == Complex(0., -666.774));
    }
}

TEST_CASE(TEST_PREFIX "pow", "[complex]") {
    {
        Complex c(1, -1);
        auto result = c.pow(3);
        REQUIRE(result.GetRealPart() == Rational(-2));
        REQUIRE(result.GetImaginaryPart() == Rational(-2));
    }
    {
        Complex c({79, 100}, -4);
        auto result = c.pow(5);
        REQUIRE(result.GetRealPart().ToDouble() == (Approx(932.62146).epsilon(0.01)));
        REQUIRE(result.GetImaginaryPart().ToDouble() == (Approx(-632.36601).epsilon(0.01)));
    }
    {
        Complex c(-145, -8);
        auto result = c.pow(5);
        REQUIRE(result.GetRealPart() == Rational(-62149190225));
        REQUIRE(result.GetImaginaryPart() == Rational(-17574409768));
    }
}

TEST_CASE(TEST_PREFIX "abs", "[complex]") {
    {
        Complex c(6, 6);
        REQUIRE(c.abs() == (Approx(8.48528).epsilon(0.01)));
    }
    {
        Complex c({-1, 5 }, 44.5);
        REQUIRE(c.abs() == (Approx(44.50044).epsilon(0.01)));
    }
    {
        Complex c(88.9, 123.0);
        REQUIRE(c.abs() == (Approx(151.76366).epsilon(0.01)));
    }
}

TEST_CASE(TEST_PREFIX "arg", "[complex]") {
    {
        Complex c(6, 6);
        REQUIRE(c.arg() == (Approx(0.78539).epsilon(0.01)));
    }
    {
        Complex c({ -1, 5 }, { 44.5 });
        REQUIRE(c.arg() == (Approx(1.57529).epsilon(0.01)));
    }
    {
        Complex c(88.9, 123.0);
        REQUIRE(c.arg() == (Approx(0.94495).epsilon(0.01)));
    }
    {
        Complex c(-88.9, -123.0);
        REQUIRE(c.arg() == (Approx(-2.19663).epsilon(0.01)));
    }
}
