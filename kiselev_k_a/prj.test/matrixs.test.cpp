#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include<matrixs/matrixs.hpp>

#include<iostream>

TEST_CASE("checking constructs") {
    MatrixS a({ 5,5 });
    a.at({ 1, 1 }) = 2;
    MatrixS b(a);

    MatrixS::size_type size = b.ssize();
    CHECK(a.at({ 1,1 }) == 2);
    CHECK(size.first == 5);
    CHECK(size.second == 5);

   a.resize({7,8});
   CHECK(a.at({ 6,6 }) == 0);
   CHECK(a.getRows() == 7);
   CHECK(a.getCols() == 8);
   
    
    

}