#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include<arrayd/arrayd.hpp>

#include <doctest/doctest.h>

#include<iostream>




const double EPS = std::numeric_limits<double>::epsilon();

TEST_CASE("checking constuct") {
    ArrayD a(3);
    CHECK(a[1] == 0);

    ArrayD b(3, 1);
    ArrayD c(b);

    CHECK_THROWS(ArrayD(-1));

    for (ptrdiff_t i = 0; i < 3; i += 1) {
        CHECK(std::abs(a[i] - b[i] + 1) <= EPS);
    }

    for (ptrdiff_t i = 0; i < 3; i += 1) {
        CHECK(std::abs(b[i] - c[i]) <= EPS);
    }

    a = b;
    for (ptrdiff_t i = 0; i < 3; i += 1) {
        CHECK(std::abs(a[i] - c[i]) <= EPS);
    }

}

TEST_CASE("checking methods") {
    ArrayD a(5, 0);
    a[1] = 1.0;
    a[2] = 2.0;
    a[3] = 3.0;
    a[4] = 4.0;
    CHECK(std::abs(a[0] - 0) <= EPS);
    CHECK(std::abs(a[1] - 1) <= EPS);
    CHECK(std::abs(a[2] - 2) <= EPS);
    CHECK(std::abs(a[3] - 3) <= EPS);
    CHECK(std::abs(a[4] - 4) <= EPS);

    CHECK(a.ssize() == 5);

    a.resize(7);
    CHECK(std::abs(a[5] - 0) <= EPS);
    CHECK(std::abs(a[6] - 0) <= EPS);
    CHECK(a.ssize() == 7);

    a.insert(3, 1);
    CHECK(std::abs(a[3] - 1) <= EPS);
    CHECK(std::abs(a[4] - 3) <= EPS);
    CHECK(a.ssize() == 8);

    a.remove(3);
    CHECK(std::abs(a[3] - 3) <= EPS);
    CHECK(a.ssize() == 7);

    a.push_back(10);
    CHECK(std::abs(a[7] - 10) <= EPS);
    
    a.insert(8, 11);
    CHECK(a[8] - 11 <= EPS);
    a.pop_back();
    a.pop_back();
    
    CHECK_THROWS(a[7]);
    CHECK_THROWS(a[15]);
    CHECK_THROWS(a[-1]);
    CHECK_THROWS(a.resize(0));
    CHECK_THROWS(a.insert(8, 2));
    CHECK_THROWS(a.insert(-1, 2));
    CHECK_THROWS(a.remove(-1));
    CHECK_THROWS(a.remove(7));

    ArrayD h(0);
    CHECK_THROWS(h.remove(0));
   
}
