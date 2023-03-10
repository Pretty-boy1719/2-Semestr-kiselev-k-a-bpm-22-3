#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include<rational/rational.hpp>

#include<iostream>


Rational a(10, 15);
Rational b(4, 18);

Rational sum(8, 9);
Rational dif(4, 9);
Rational mul(4, 27);
Rational division(3, 1);


TEST_CASE("checking arithmetic") {
    CHECK(a + b == sum);
    CHECK(a - b == dif);
    CHECK(a * b == mul);
    CHECK(a / b == division);
}


bool less = false;
bool equal = false;
bool bigger = true;

TEST_CASE("checking boolean") {
    CHECK((a < b) == less);
    CHECK((a == b) == equal);
    CHECK((a > b) == bigger);
}
