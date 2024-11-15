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
        CHECK(std::abs(a[i]- b[i]+1)<=EPS);
    }

    for (ptrdiff_t i = 0; i < 3; i += 1) {
        CHECK(std::abs(b[i] - c[i])<=EPS);
    }

    a = b;
    for (ptrdiff_t i = 0; i < 3; i += 1) {
        CHECK(std::abs(a[i] - c[i])<=EPS);
    }
    
}

TEST_CASE("checking methods") {
    ArrayT<double> a(5, 0);
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

    ArrayT<double> h(0);
    CHECK_THROWS(h.remove(0));

}

TEST_CASE_TEMPLATE("numeric variable", ArrayT, int, double, long long, ptrdiff_t) {
    ArrayT var = ArrayT();
    var -= 1;
    CHECK(var == -1);
}

using T = double;

TEST_CASE("CONSTRUCTORS") {
	SUBCASE("CONSTRUCTOR WITHOUT PARAMETRS") {
		ArrayT<T> a;
		CHECK(a.ssize() == 0);
	}
	SUBCASE("CONSTRUCTOR WITH SIZE") {
		size_t size = 5;
		ArrayT<T> a(size);
		a[1] = 2;
		a[2] = 3;
		SUBCASE("SIZE") {
			CHECK(a.ssize() == size);
		}
		SUBCASE("ArrayD VALUES") {
			CHECK(a[1] == 2);
			CHECK(a[2] == 3);
		}
		SUBCASE("CHANGE VALUE") {
			a[1] = 10;
			CHECK(a[1] == 10);
		}
		SUBCASE("DEFAULT VALUE") {
			CHECK(a[0] == 0);
		}
	}
	SUBCASE("CONSTRUCTOR FROM ANOTHER INSTANCE") {
		size_t size = 3;
		ArrayT<T> b(size);
		b[0] = 1;
		b[1] = 2;
		b[2] = -3;
		ArrayT<T> a(b);
		SUBCASE("SIZE") {
			CHECK(a.ssize() == b.ssize());
			CHECK(a.ssize() == size);
		}
		SUBCASE("ArrayD VALUES") {
			CHECK(a[0] == b[0]);
			CHECK(a[0] == 1);
			CHECK(a[2] == b[2]);
			CHECK(a[2] == -3);
		}
		SUBCASE("CHANGE VALUES") {
			b[0] = 10;
			CHECK(a[0] != b[0]);
			CHECK(b[0] == 10);
			CHECK(a[0] == 1);
		}
	}
}
TEST_CASE("INTERFACE")
{
	SUBCASE("EQUIVALENCE") {
		size_t size = 4;
		ArrayT<T> b(size);
		b[0] = 1;
		b[1] = 2;
		b[2] = -3;
		ArrayT<T> a = b;
		SUBCASE("SIZE") {
			CHECK(a.ssize() == b.ssize());
			CHECK(a.ssize() == size);
		}
		SUBCASE("ArrayD VALUES") {
			CHECK(a[0] == b[0]);
			CHECK(a[0] == 1);
			CHECK(a[2] == b[2]);
			CHECK(a[2] == -3);
		}
		SUBCASE("CHANGE VALUES") {
			b[0] = 10;
			CHECK(a[0] != b[0]);
			CHECK(b[0] == 10);
			CHECK(a[0] == 1);
			a[0] = 3;
			CHECK(a[0] != b[0]);
			CHECK(b[0] == 10);
			CHECK(a[0] == 3);
		}
	}
	SUBCASE("A=A") {
		size_t size = 4;
		ArrayT<T> b(size);
		SUBCASE("0") {
			CHECK(b[0] == 0);
		}
		b = b;
		b[2] = 2;
		SUBCASE("SIZE") {
			CHECK(b.ssize() == size);
		}
		SUBCASE("ArrayD VALUES") {
			CHECK(b[2] == 2);
			CHECK(b[0] == 0);
		}
		SUBCASE("CHANGE VALUES") {
			b[0] = 10;
			CHECK(b[0] == 10);
		}
	}
	SUBCASE("INDEX") {
		size_t size = 4;
		ArrayT<T> a(size);
		a[0] = 1.2;
		SUBCASE("LHS") {
			double b = 3.14;
			a[1] = b;
			CHECK(a[1] == b);
		}
		SUBCASE("RHS") {
			double b = 3.14;
			b = a[0];
			CHECK(b == 1.2);
		}
		SUBCASE("INDEX OUT OF RANGE(>=SIZE)") {
			double b = 3.14;
			CHECK_THROWS_AS(a[size] = b, std::out_of_range);
		}
		SUBCASE("INDEX OUT OF RANGE(<=0)") {
			double b = 3.14;
			CHECK_THROWS_AS(a[-1] = b, std::out_of_range);
		}
	}
	SUBCASE("SIZE AND CAPACITY") {
		SUBCASE("SSIZE") {
			size_t size = 3;
			ArrayT<T> a(size);
			CHECK(a.ssize() == size);
		}
		SUBCASE("RESIZE>SIZE") {
			size_t size = 3;
			ArrayT<T> a(size);
			a[2] = 5.2;
			size_t new_size = 5;
			a.resize(new_size);
			CHECK(a.ssize() == new_size);
			CHECK(a[2] == 5.2);
			CHECK(a[0] == 0);
			CHECK(a[new_size - 1] == 0);
			CHECK_THROWS_AS(a[new_size] = 1, std::out_of_range);
		}
		SUBCASE("RESIZE<SIZE") {
			size_t size = 4;
			ArrayT<T> a(size);

			a[1] = 5.2;
			size_t new_size = 3;
			a.resize(new_size);
			CHECK(a.ssize() == new_size);
			CHECK(a[1] == 5.2);
			CHECK(a[0] == 0);
			CHECK(a[new_size - 1] == 0);
			CHECK_THROWS_AS(a[new_size] = 1, std::out_of_range);
		}
		SUBCASE("RESIZE 0") {
			size_t size = 3;
			ArrayT<T> a(size);
			CHECK_THROWS_AS(a.resize(0), std::invalid_argument);
		}
	}
	SUBCASE("INSERT") {
		size_t size = 3;
		ArrayT<T> a(size);
		a[1] = 2.5;
		SUBCASE("IN RANGE") {
			a.insert(1, 3.14);
			CHECK(a[1] == 3.14);
			CHECK(a[2] == 2.5);
			CHECK(a.ssize() == size + 1);
		}
		SUBCASE("IN SIZE") {
			CHECK_NOTHROW(a.insert(size, 3.14));
			CHECK(a[size] == 3.14);
			CHECK(a.ssize() == size + 1);
		}
		SUBCASE("OUT OF RANGE(>SIZE)") {
			CHECK_THROWS_AS(a.insert(size + 1, 3.14), std::out_of_range);
		}
		SUBCASE("OUT OF RANGE(<=0)") {
			CHECK_THROWS_AS(a.insert(-1, 3.14), std::out_of_range);
		}
	}
	SUBCASE("REMOVE") {
		size_t size = 3;
		ArrayT<T> a(size);
		a[2] = 2.5;
		SUBCASE("IN RANGE") {
			a.remove(1);
			CHECK(a[1] == 2.5);
			CHECK(a[0] == 0);
			CHECK(a.ssize() == size - 1);
		}
		SUBCASE("OUT OF RANGE(>SIZE)") {
			CHECK_THROWS_AS(a.remove(size + 1), std::out_of_range);
		}
		SUBCASE("OUT OF RANGE(<=0)") {
			CHECK_THROWS_AS(a.remove(-1), std::out_of_range);
		}
	}
}
