#include<rational/rational.hpp>

#include<iostream>


Rational::Rational()
	:num_(0),
	denom_(1)
{
}

Rational::Rational(const int32_t intNumber) noexcept
	:Rational(intNumber, 1) 
{
}

Rational::Rational(const int32_t numInp, const int32_t denomInp)
{
	if (denomInp <= 0)
		throw std::invalid_argument("Expected positive number");

	num_ = numInp;
	denom_ = denomInp;
	norm();
}

Rational::Rational(const Rational& myRational)
	:num_(myRational.num_)
	, denom_(myRational.denom_)
{
}

Rational& Rational::operator=(const Rational& rhs) {
	num_ = rhs.num_;
	denom_ = rhs.denom_;
	return *this;
}

Rational& Rational::operator+=(const Rational& rhs) {
	int32_t coef = rhs.denom_ / gcd(std::abs(denom_), rhs.denom_);
	num_ *= coef;
	denom_ *= coef;
	num_ += denom_ / rhs.denom_ * rhs.num_;
	norm();
	return *this;
}
Rational& Rational::operator-=(const Rational& rhs) {
	int32_t coef = rhs.denom_ / gcd(denom_, rhs.denom_);
	num_ *= coef;
	denom_ *= coef;
	num_ -= denom_ / rhs.denom_ * rhs.num_;
	norm();
	return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
	num_ *= rhs.num_;
	denom_ *= rhs.denom_;
	norm();
	return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
	if (rhs.num_ == 0 || rhs.denom_ == 0)
		throw std::overflow_error("Divide by zero exception");

	num_ *= rhs.denom_;
	denom_ *= rhs.num_;
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
	if (denom_ == 0)
		throw std::overflow_error("Divide by zero exception");

	int32_t Gcd = gcd(std::abs(num_), std::abs(denom_));
	num_ /= Gcd;
	denom_ /= Gcd;
}

int32_t gcd(int32_t a, int32_t b) {
	while (b) {
		a %= b;
		std::swap(a, b);
	}
	return a;
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) {
	return rhs.WriteTo(ostrm);
}

std::istream& operator>>(std::istream& istrm, Rational& rhs) {
	return rhs.ReadFrom(istrm);
}

std::ostream& Rational::WriteTo(std::ostream& ostrm) const noexcept
{
	ostrm << num_ << separator_ << denom_;
	return ostrm;
}


std::istream& Rational::ReadFrom(std::istream& istrm)
{
	int32_t numInp(0);
	char separator(0);
	int32_t denomInp(0);
	istrm >> numInp >> separator >> denomInp;
	if (istrm.good()) {
		if (Rational::separator_ == separator) {
			if (denomInp <= 0) {
				istrm.setstate(std::ios_base::failbit);
			}
			else {
				num_ = numInp;
				denom_ = denomInp;
				norm();
			}
		}
		else {
			istrm.setstate(std::ios_base::failbit);
		}
	}
	return istrm;
}

std::pair<int32_t, int32_t> Rational::get() const {
	return std::make_pair(num_, denom_);
}


