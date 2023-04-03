#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include<rational/rational.hpp>

#include<iostream>


TEST_CASE("checking constructors") {
    Rational a;
    Rational b(5);
    Rational c(10, 15);
    Rational d(c);
    Rational h(0, 5);

    CHECK_THROWS(Rational(5, 0));

    CHECK(a.get().first == 0);
    CHECK(a.get().second == 1);

    CHECK(b.get().first == 5);
    CHECK(b.get().second == 1);

    CHECK(c.get().first == 2);
    CHECK(c.get().second == 3);
    
    CHECK(d.get().first == 2);
    CHECK(d.get().second == 3);

    CHECK(h == 0);
}

TEST_CASE("internal operators") {
    Rational a(1, 2);
    Rational b = a;
    
    CHECK(b==a);

    b += 1;
    Rational c(3, 2);
    CHECK(b == c);

    b -= Rational(a*2);
    CHECK(b == a);

    b *= 2;
    CHECK(b == 1);

    b /= 2;
    CHECK(b == a);

    CHECK_THROWS(a /= 0);
    CHECK_THROWS(a /= Rational(0, 1));

    a++;
    CHECK(a == c);
    a--;
    CHECK(a == b);
}

TEST_CASE("logical operators") {
    Rational a(1, 2);
    Rational b = a;
    Rational c(1);
    CHECK(a == b);

    b += 1;
    CHECK(a<b);
    CHECK(b>a);
    CHECK(a<=b);
    CHECK(b>=a);

    b -= 1;
    CHECK(a<=b);
    CHECK(a>=b);

    b += 3;
    CHECK(a!=b);

    int32_t i = 1;
    int32_t j = 50;
    CHECK(b > i);
    CHECK(b >= i);
    CHECK(b < j);
    CHECK(b <= j);
    CHECK(i < b);
    CHECK(i <= b);
    CHECK(j > b);
    CHECK(j >= b);
    CHECK(c >= i);
    CHECK(c <= i);
    CHECK(c <= 1);
    CHECK(c >= 1);
    CHECK(c == 1);
    CHECK(b != j);
}

TEST_CASE("checking arithmetics") {
    Rational a(1, 2);
    Rational b(1);

    CHECK(a + b == Rational(3, 2));
    CHECK(a + 1 == Rational(3, 2));

    CHECK(a - b == Rational(-1, 2));
    
    Rational c(2, 3);
    CHECK(a + c == Rational(7, 6));

    CHECK(a * 2 == 1);
    CHECK(a * 3 == Rational(3, 2));

    CHECK(a / 2 == Rational(1, 4));
    CHECK_THROWS(a / 0);
    CHECK_THROWS(a / Rational(0,5));
}
 
