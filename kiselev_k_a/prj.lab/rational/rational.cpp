#include<rational/rational.hpp>

#include<iostream>


Rational& Rational::operator=(const Rational& rhs) {
	num = rhs.num;
	denom = rhs.denom;
	return *this;
}

Rational& Rational::operator+=(const Rational& rhs) {
	int32_t coef = rhs.denom / gcd(std::abs(denom), rhs.denom);
	num *= coef;
	denom *= coef;
	num += denom / rhs.denom * rhs.num;
	norm();
	return *this;
}
Rational& Rational::operator-=(const Rational& rhs) {
	int32_t coef = rhs.denom / gcd(denom, rhs.denom);
	num *= coef;
	denom *= coef;
	num -= denom / rhs.denom * rhs.num;
	norm();
	return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
	num *= rhs.num;
	denom *= rhs.denom;
	norm();
	return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
	if (rhs.num == 0 || rhs.denom == 0)
		throw std::overflow_error("Divide by zero exception");

	num *= rhs.denom;
	denom *= rhs.num;
	norm();
	return *this;
}


Rational operator+(Rational lhs, Rational rhs) {
	lhs += rhs;
	return lhs;
}

Rational operator-(Rational lhs, Rational rhs) {
	lhs -= rhs;
	return lhs;
}

Rational operator*(Rational lhs, Rational rhs) {
	lhs *= rhs;
	return lhs;
}

Rational operator/(Rational lhs, Rational rhs) {
	lhs /= rhs;
	return lhs;
}

Rational& Rational::operator++() {
	*this += Rational(1);
	return *this;
}

Rational& Rational::operator--() {
	*this -= Rational(1);
	return *this;
}

Rational& Rational::operator++(int32_t) {
	Rational temp(*this);
	++(*this);

	return temp;
}Rational& Rational::operator--(int32_t) {
	Rational temp(*this);
	--(*this);

	return temp;
}


bool operator==(Rational lhs, Rational rhs) {
	lhs -= rhs;
	if (lhs.get().first == 0)
		return true;
	else
		return false;
}

bool operator>(Rational lhs, Rational rhs) {
	lhs -= rhs;
	if (lhs.get().first > 0)
		return true;
	else
		return false;
}

bool operator<(Rational lhs, Rational rhs) {
	lhs -= rhs;
	if (lhs.get().first < 0)
		return true;
	else
		return false;
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
	if (lhs > rhs || lhs == rhs)
		return true;
	else
		return false;
}

bool operator <=(const Rational& lhs, const Rational& rhs) {
	if (lhs > rhs)
		return false;
	else
		return true;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
	if (lhs == rhs)
		return false;
	else
		return true;
}

void Rational::norm() {
	if (denom == 0)
		throw std::overflow_error("Divide by zero exception");

	int32_t Gcd = gcd(std::abs(num), std::abs(denom));
	num /= Gcd;
	denom /= Gcd;
}

int32_t gcd(int32_t a, int32_t b) {
	while (b) {
		a %= b;
		std::swap(a, b);
	}
	return a;
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) {
	return rhs.writeTo(ostrm);
}

std::istream& operator>>(std::istream& istrm, Rational& rhs) {
	return rhs.readFrom(istrm);
}

std::ostream& Rational::writeTo(std::ostream& ostrm) const
{
	ostrm << num << separator << denom;
	return ostrm;
}


std::istream& Rational::readFrom(std::istream& istrm)
{
	int32_t numInp(0);
	char separator(0);
	int32_t denomInp(0);
	istrm >> numInp >> separator >> denomInp;
	if (istrm.good()) {
		if (Rational::separator == separator) {
			if (denomInp <= 0) {
				throw std::invalid_argument("Expected positive denominator");
			}
			num = numInp;
			denom = denomInp;
			norm();
		}
		else {
			istrm.setstate(std::ios_base::failbit);
		}
	}
	return istrm;
}

std::pair<int32_t, int32_t> Rational ::get() {
	return std::make_pair(num, denom);
}


Rational::Rational() {
	num = 0;
	denom = 1;
}

Rational::Rational(const int32_t intNumber)
	:Rational(intNumber, 1)
{
}

Rational::Rational(const int32_t numInp, const int32_t denomInp)
{
	if (denomInp <= 0)
		throw std::invalid_argument("Expected positive number");

	num = numInp;
	denom = denomInp;
	norm();
}

Rational::Rational(const Rational& myRational)
	:num(myRational.num)
	, denom(myRational.denom)
{
}