#include "../catch.hpp"
#include "../Numbers/complex.h"
#include "../Numbers/rational.h"
#include <sstream>
#define TEST_PREFIX "Rational::"


TEST_CASE(TEST_PREFIX "constructors works correctly", "[rational]") {
    SECTION("default") {
        const Rational r;
        REQUIRE(r.Numerator() == 0);
        REQUIRE(r.Denominator() == 1);
    }
    SECTION("int") {
        {
            const Rational r(133);
            REQUIRE(r.Numerator() == 133);
            REQUIRE(r.Denominator() == 1);
        }
        {
            const Rational r(-4);
            REQUIRE(r.Numerator() == -4);
            REQUIRE(r.Denominator() == 1);
        }
    }
    SECTION("int64_t") {
        {
            const Rational r(1999);
            REQUIRE(r.Numerator() == 1999);
            REQUIRE(r.Denominator() == 1);
        }
        {
            const Rational r(-372);
            REQUIRE(r.Numerator() == -372);
            REQUIRE(r.Denominator() == 1);
        }
    }
    SECTION("int64_t and int64_t") {
        {
            const Rational r(5, 7);
            REQUIRE(r.Numerator() == 5);
            REQUIRE(r.Denominator() == 7);
        }

        {
            const Rational r(5, 25);
            REQUIRE(r.Numerator() == 1);
            REQUIRE(r.Denominator() == 5);
        }
        {
            const Rational r(-9, 12);
            REQUIRE(r.Numerator() == -3);
            REQUIRE(r.Denominator() == 4);
        }
        {
            const Rational r(-9, -12);
            REQUIRE(r.Numerator() == 3);
            REQUIRE(r.Denominator() == 4);
        }
        {
            const Rational r(9, -13);
            REQUIRE(r.Numerator() == -9);
            REQUIRE(r.Denominator() == 13);
        }
        {
            const Rational r(7, -5);
            REQUIRE(r.Numerator() == -7);
            REQUIRE(r.Denominator() == 5);
        }
        {
            const Rational r(0, -5);
            REQUIRE(r.Numerator() == 0);
            REQUIRE(r.Denominator() == 1);
        } 
        {
            const Rational r(0, 123331);
            REQUIRE(r.Numerator() == 0);
            REQUIRE(r.Denominator() == 1);
        }
        SECTION("double"){
            {
                const Rational r(1999.9999);
                REQUIRE(r.Numerator() == 19999999);
                REQUIRE(r.Denominator() == 10000);
            }
            {
                const Rational r(-5.9);
                REQUIRE(r.Numerator() == -59);
                REQUIRE(r.Denominator() == 10);
            }
            {
                const Rational r(-9888.144);
                REQUIRE(r.Numerator() == -1236018);
                REQUIRE(r.Denominator() == 125);
            }
        }
    }
}

TEST_CASE(TEST_PREFIX "checking ostream", "[rational]") {
    {
        ostringstream output;
        output << Rational(5, 8);
        REQUIRE(output.str() == "5/8");
    }

    {
        ostringstream output;
        output << Rational(-5, 8);
        REQUIRE(output.str() == "-5/8");
    }

    {
        ostringstream output;
        output << Rational(-5, -8);
        REQUIRE(output.str() == "5/8");
    }

    {
        ostringstream output;
        output << Rational(5, -8);
        REQUIRE(output.str() == "-5/8");
    }

    {
        ostringstream output;
        output << Rational(5, 8);
        REQUIRE(output.str() == "5/8");
    }
}

TEST_CASE(TEST_PREFIX "operator ==", "[rational]") {
    {
        const Rational r1(5, 7);
        const Rational r2(9, 7);
        REQUIRE((r1 == r2) == false);
    }
    {
        const Rational r1(-5, 7);
        const Rational r2(9, 7);
        REQUIRE((r1 == r2) == false);
    }
    {
        const Rational r1(-5, 7);
        const Rational r2(5, -7);
        REQUIRE((r1 == r2) == true);
    }
    {
        const Rational r1(0, 7);
        const Rational r2(9, 7);
        REQUIRE((r1 == r2) == false);
    }
    {
        const Rational r1(1800, 100);
        const Rational r2(18, 1);
        REQUIRE((r1 == r2) == true);
    }
}

TEST_CASE(TEST_PREFIX "operator +", "[rational]") {
    SECTION("positive (zero) + positive (zero)") {
        {
            const Rational r1(5, 7);
            const Rational r2(9, 7);
            REQUIRE((r1 + r2) == Rational(2, 1));
        }
        {
            const Rational r1(5678292929, 7);
            const Rational r2(828282, 13452);
            REQUIRE((r1 + r2) == Rational(12730733713147, 15694));
        }
        {
            const Rational r1(0, 123781239172);
            const Rational r2(828282, 13452);
            REQUIRE((r1 + r2) == Rational(828282, 13452));
        }
    }
    SECTION("negative (zero) + negative (zero)") {
        {
            const Rational r1(-2555, 135);
            const Rational r2(-6753289, 1998273);
            REQUIRE(r1 + r2 == Rational(-401152102, 17984457));
        }
        {
            const Rational r1(144, -100);
            const Rational r2(9877, -765);
            REQUIRE(r1 + r2 == Rational(-3229, 225));
        }
        {
            const Rational r1(-29, 25);
            const Rational r2(90, -25);
            REQUIRE((r1 + r2) == Rational(-119, 25));
        }
        {
            const Rational r1(-5678292929, 7);
            const Rational r2(828282, -13452);
            REQUIRE((r1 + r2) == Rational(-12730733713147, 15694));
        }
    }
    SECTION("different signs") {
        {
            const Rational r1(-5, 7);
            const Rational r2(9, 7);
            REQUIRE((r1 + r2) == Rational(4, 7));
        }
        {
            const Rational r1(0, 7);
            const Rational r2(9, 7);
            REQUIRE((r1 + r2) == Rational(9, 7));
        }
        {
            const Rational r1(1800, 100);
            const Rational r2(-18, 1);
            REQUIRE((r1 + r2) == Rational(0, 1));
        }
        {
            const Rational r1(1876541234, 100000);
            const Rational r2(987123, -188712300);
            REQUIRE((r1 + r2) == Rational(590210522667797, 31452050000));
        }
    }
}

TEST_CASE(TEST_PREFIX "binary operator - ", "[rational]") {
    SECTION("positive (zero) - positive (zero)") {
        {
            const Rational r1(25, 35);
            const Rational r2(5665, 9090);
            REQUIRE((r1 - r2) == Rational(1159, 12726));
        }
        {
            const Rational r1(8971263123, 73321231);
            const Rational r2(0, 13452);
            REQUIRE((r1 - r2) == Rational(8971263123, 73321231));
        }
        {
            const Rational r1(0, 123781239172);
            const Rational r2(828282, 13452);
            REQUIRE((r1 - r2) == Rational(-828282, 13452));
        }
    }
    SECTION("negative (zero) - negative (zero)") {
        {
            const Rational r1(-2555, 135);
            const Rational r2(-6753289, 1998273);
            REQUIRE((r1 - r2) == Rational(-279592900, 17984457));
        }
        {
            const Rational r1(-17, 14);
            const Rational r2(-29, 14);
            REQUIRE((r1 - r2) == Rational(6, 7));
        }
        {
            const Rational r1(-29, 25);
            const Rational r2(0, -25);
            REQUIRE((r1 - r2) == Rational(-29, 25));
        }
        {
            const Rational r1(-5678292929, 7);
            const Rational r2(828282, -13452);

            REQUIRE((r1 - r2) == Rational(-12730731780489, 15694));
        }
    }
    SECTION("different signs") {
        {
            const Rational r1(-5, 29);
            const Rational r2(9, 29);
            REQUIRE((r1 - r2) == Rational(-14, 29));
        }
        {
            const Rational r1(0, 7);
            const Rational r2(9, 7);
            REQUIRE((r1 - r2) == Rational(-9, 7));
        }
        {
            const Rational r1(1800, 1001111);
            const Rational r2(-18, 12);
            REQUIRE((r1 - r2) == Rational(3006933, 2002222));
        }
        {
            const Rational r1(-1876541234, 1000);
            const Rational r2(987123, 1887123);
            REQUIRE((r1 - r2) == Rational(-590210851708797, 314520500));
        }
    }
}

TEST_CASE(TEST_PREFIX "operator *", "[rational]") {
    SECTION("positive (zero) * positive (zero)") {
        {
            const Rational r1(10, 35);
            const Rational r2(6, 90);
            REQUIRE(r1 * r2 == Rational(2, 105));
        }
        {
            const Rational r1(897126, 733);
            const Rational r2(0, 13452);
            REQUIRE(r1 * r2 == Rational(0, 1));
        }
    }
    SECTION("negative (zero) * negative (zero)") {
        {
            const Rational r1(-10, 35);
            const Rational r2(6, -90);
            REQUIRE(r1 * r2 == Rational(2, 105));
        }
        {
            const Rational r1(-897126, 733);
            const Rational r2(0, -13452);
            REQUIRE(r1 * r2 == Rational(0, 1));
        }
    }
    SECTION("different signs") {
        {
            const Rational r1(-10, 35);
            const Rational r2(6, 90);
            REQUIRE(r1 * r2 == Rational(-2, 105));
        }
        {
            const Rational r1(897126, 733);
            const Rational r2(-50, 13452);
            REQUIRE(r1 * r2 == Rational(-3738025, 821693));
        }
        {
            const Rational r1(12345, -13355);
            const Rational r2(1423, 1551);
            REQUIRE(r1 * r2 == Rational(1171129, -1380907));
        }
    }
}

TEST_CASE(TEST_PREFIX "operator /", "[rational]") {
    SECTION("positive (zero) / positive (zero)") {
        {
            const Rational r1(10, 35);
            const Rational r2(6, 90);
            REQUIRE(r1 / r2 == Rational(30, 7));
        }
        {
            const Rational r1(0, 13452);
            const Rational r2(897126, 733);
            REQUIRE(r1 * r2 == Rational(0, 1));
        }
        {
            const Rational r1(13455, 312335);
            const Rational r2(61, 912);
            REQUIRE(r1 / r2 == Rational(2454192, 3810487));
        }
    }
    SECTION("negative (zero) / negative (zero)") {
        {
            const Rational r1(10, 35);
            const Rational r2(6, 90);
            REQUIRE(r1 / r2 == Rational(30, 7));
        }
        {
            const Rational r1(0, 13452);
            const Rational r2(897126, 733);
            REQUIRE(r1 * r2 == Rational(0, 1));
        }
        {
            const Rational r1(-13455, 312335);
            const Rational r2(-61, 912);
            REQUIRE(r1 / r2 == Rational(2454192, 3810487));
        }
    }
    SECTION("different signs") {
        {
            const Rational r1(-11230, 35111);
            const Rational r2(6232, 903);
            REQUIRE(r1 / r2 == Rational(-5070345, 109405876));
        }
        {
            const Rational r1(11, 11);
            const Rational r2(-11, 11);
            REQUIRE(r1 / r2 == Rational(-1, 1));
        }
    }
}

TEST_CASE(TEST_PREFIX "unar operator -", "[rational]") {
    {
        Rational r(14);
        REQUIRE((-r) == Rational(-14));
    }
    {
        Rational r(-14222);
        REQUIRE((-r) == Rational(14222));
    }
    {
        Rational r(1902323, 1111);
        REQUIRE((-r) == Rational(-1902323, 1111));
    }
    {
        Rational r(1902323, -1111);
        REQUIRE((-r) == Rational(1902323, 1111));
    }
}

TEST_CASE(TEST_PREFIX "function ToDouble", "[rational]") {
    {
        Rational r(1555676555, 123333222);
        REQUIRE(r.ToDouble() == Approx(12.613605075524582).epsilon(0.01));
    }
    {
        Rational r(-9999999, 1223);
        REQUIRE(r.ToDouble() == Approx(-8176.614063777596).epsilon(0.01));
    }
    {
        Rational r(1555676555, 12331222);
        REQUIRE(r.ToDouble() == Approx(126.15753369779573).epsilon(0.01));
    }
    {
        Rational r(1555676555);
        REQUIRE(r.ToDouble() == 1555676555.0);
    }
}

TEST_CASE(TEST_PREFIX "abs", "[rational]") {
    {
        Rational r(-999, 2);
        REQUIRE(r.abs() == Rational(999, 2));
    }
    {
        Rational r(1, 55);
        REQUIRE(r.abs() == Rational(1, 55));
    }
}
