#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include<matrixs/matrixs.hpp>

#include<iostream>

TEST_CASE("checking constructs") {
    MatrixS a({ 5,5 });
    a.at({ 1, 1 }) = 2;
    a.at(1, 2) = 3;

    MatrixS c(5, 5);
    c.at({ 1, 1 }) = 2;
    c.at(1, 2) = 3;

    CHECK(a.at({ 1, 1 }) == c.at(1, 1));
    CHECK(a.at(1, 2) == c.at({ 1, 2 }));
    
    MatrixS b(a);
    CHECK(b.at({ 1,1 }) == 2);
    CHECK(b.at({ 1,2 }) == 3);
    MatrixS::SizeType size_b = b.ssize();
    CHECK(get<0>(size_b) == 5);
    CHECK(get<1>(size_b) == 5);
    CHECK(get<0>(size_b) == b.nRows());
    CHECK(get<1>(size_b) == b.nCols());

    MatrixS d = a;
    CHECK(d.at({ 1,1 }) == 2);
    CHECK(d.at({ 1,2 }) == 3);
    MatrixS::SizeType size_d = d.ssize();
    CHECK(get<0>(size_d) == 5);
    CHECK(get<1>(size_d) == 5);

    a.resize(7,8);
    a.at(6, 7) = 5;
    CHECK(a.at(6, 7) == 5);

    a.resize({ 8,9 });
    a.at(7, 8) = 9;
    CHECK(a.at(7, 8) == 9);

    CHECK(a.nRows() == 8);
    CHECK(a.nCols() == 9);

    CHECK_THROWS(a.at(8, 9));
    CHECK_THROWS(a.at({ 8, 9 }));
    CHECK_THROWS(a.resize(0, 9));
    CHECK_THROWS(a.resize({ 0, 9 }));
    CHECK_THROWS(a.resize(9, 0));
    CHECK_THROWS(a.resize({ 9, 0 }));
}