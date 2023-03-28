#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include<arrayt/arrayt.hpp>

#include <doctest/doctest.h>

#include<iostream>




const double EPS = std::numeric_limits<double>::epsilon();

TEST_CASE("checking constuct") {
    ArrayT<double> a(3);
    CHECK(a[1] == 0);

    ArrayT<double> b(3, 1);
    ArrayT<double> c(b);

    CHECK_THROWS(ArrayT<double>(-1));

    for (ptrdiff_t i = 0; i < 3; i += 1) {
        CHECK(a[i] == b[i]-1);
    }

    for (ptrdiff_t i = 0; i < 3; i += 1) {
        CHECK(b[i] == c[i]);
    }

    a = b;
    for (ptrdiff_t i = 0; i < 3; i += 1) {
        CHECK(a[i] == c[i]);
    }
    
}

TEST_CASE("checking methods") {
    ArrayT<double> a(5, 0);
    a[1] = 1.0;
    a[2] = 2.0;
    a[3] = 3.0;
    a[4] = 4.0;
    CHECK(a[0] - 0 <= EPS);
    CHECK(a[1] - 1 <= EPS);
    CHECK(a[2] - 2 <= EPS);
    CHECK(a[3] - 3 <= EPS);
    CHECK(a[4] - 4 <= EPS);

    CHECK(a.ssize() == 5);

    a.resize(7);
    CHECK(a[5] - 0 <= EPS);
    CHECK(a[6] - 0 <= EPS);
    CHECK(a.ssize() == 7);

    a.insert(1, 3);
    CHECK(a[3] - 1 <= EPS);
    CHECK(a[4] - 3 <= EPS);
    CHECK(a.ssize() == 8);

    a.remove(3);
    CHECK(a[3] - 3 <= EPS);
    CHECK(a.ssize() == 7);

    a.push_back(10);
    CHECK(a[6] - 10 <= EPS);

    a.pop_back();
    CHECK_THROWS(a[7]);
    CHECK_THROWS(a[15]);
    CHECK_THROWS(a[-1]);

}
