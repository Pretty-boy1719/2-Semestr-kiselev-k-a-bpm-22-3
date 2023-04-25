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
	if (denomInp == 0) {
		throw std::invalid_argument("Expected non-zero denominator");
	}
		
	num_ = numInp;
	denom_ = denomInp;

	if (denom_ < 0) {
		num_ *= -1;
		denom_ *= -1;
	}
	
	norm();
}

Rational::Rational(const Rational& myRational)
	:num_(myRational.num_)
	, denom_(myRational.denom_)
{
	norm();
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

std::pair<int32_t, int32_t> Rational::get() const {
	return std::make_pair(num_, denom_);
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) {
	return rhs.WriteTo(ostrm);
}

std::istream& operator>>(std::istream& istrm, Rational& rhs) {
	return rhs.ReadFrom(istrm);
}

std::ostream& Rational::WriteTo(std::ostream& ostrm) const noexcept
{
	ostrm << num_ << separator << denom_;
	return ostrm;
}


std::istream& Rational::ReadFrom(std::istream& istrm)
{
	char sym('-');
	while (std::isspace(istrm.peek())) {
		sym = istrm.get();
	}
	int32_t numInp_(0);
	int32_t denomInp_(0);
	sym = '-';
	bool isNeg(false);
	if (istrm.peek() == '-') {
		isNeg = true;
		sym = istrm.get();
	}

	while (std::isdigit(istrm.peek())) {
		sym = istrm.get();
		numInp_ *= 10;
		numInp_ += static_cast<int>(sym - '0');
	}
	if (sym == '-') {
		istrm.setstate(std::ios_base::failbit);
		return istrm;
	}

	if (istrm.peek() != '/') {
		istrm.setstate(std::ios_base::failbit);
		return istrm;
	}
	sym = istrm.get();

	while (std::isdigit(istrm.peek())) {
		sym = istrm.get();
		denomInp_ *= 10;
		denomInp_ += static_cast<int>(sym - '0');
	}
	if (sym == '/') {
		istrm.setstate(std::ios_base::failbit);
		return istrm;
	}

	if (istrm.good() || istrm.eof()) {
		if (denomInp_ == 0) {
			istrm.setstate(std::ios_base::failbit);
			return istrm;
		}
		num_ = numInp_;
		denom_ = denomInp_;
		if (isNeg) {
			num_ *= -1;
		}
		norm();
	}
	return istrm;
}





Rational& Rational::operator=(const Rational& rhs) {
	num_ = rhs.num_;
	denom_ = rhs.denom_;
	norm();
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

Rational& Rational::operator=(const int32_t& rhs) {
	*this = Rational(rhs);
	return *this;
}
Rational& Rational::operator+=(const int32_t& rhs) {
	*this += Rational(rhs);
	return *this;
}
Rational& Rational::operator-=(const int32_t& rhs) {
	*this -= Rational(rhs);
	return *this;
}
Rational& Rational::operator*=(const int32_t& rhs) {
	*this *= Rational(rhs);
	return *this;
}
Rational& Rational::operator/=(const int32_t& rhs) {
	*this /= Rational(rhs);
	return *this;
}





Rational& Rational::operator++() {
	*this += Rational(1);
	return *this;
}

Rational& Rational::operator--() {
	*this -= Rational(1);
	return *this;
}

Rational Rational::operator++(int32_t) {
	Rational temp(*this);
	++(*this);

	return temp;
}Rational Rational::operator--(int32_t) {
	Rational temp(*this);
	--(*this);

	return temp;
}

Rational Rational::operator-() const {
	Rational temp;
	temp.num_ = -num_;
	temp.denom_ = denom_;

	return temp;
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

Rational operator+(Rational lhs, int32_t rhs) { return Rational(lhs) + Rational(rhs); }
Rational operator+(int32_t lhs, Rational rhs) { return Rational(lhs) + Rational(rhs); }

Rational operator-(Rational lhs, int32_t rhs) { return Rational(lhs) - Rational(rhs); }
Rational operator-(int32_t lhs, Rational rhs) { return Rational(lhs) - Rational(rhs); }

Rational operator*(Rational lhs, int32_t rhs) { return Rational(lhs) * Rational(rhs); }
Rational operator*(int32_t lhs, Rational rhs) { return Rational(lhs) * Rational(rhs); }

Rational operator/(Rational lhs, int32_t rhs) { return Rational(lhs) / Rational(rhs); }
Rational operator/(int32_t lhs, Rational rhs) { return Rational(lhs) / Rational(rhs); }




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

bool operator==(int32_t lhs, Rational rhs) { return Rational(lhs) == Rational(rhs); }
bool operator==(Rational lhs, int32_t rhs) { return Rational(lhs) == Rational(rhs); }

bool operator>(int32_t lhs, Rational rhs) { return Rational(lhs) > Rational(rhs); }
bool operator>(Rational lhs, int32_t rhs) { return Rational(lhs) > Rational(rhs); }

bool operator<(int32_t lhs, Rational rhs) { return Rational(lhs) < Rational(rhs); }
bool operator<(Rational lhs, int32_t rhs) { return Rational(lhs) < Rational(rhs); }

bool operator>=(const int32_t& lhs, const Rational& rhs) { return Rational(lhs) >= Rational(rhs); }
bool operator>=(const Rational& lhs, const int32_t& rhs) { return Rational(lhs) >= Rational(rhs); }

bool operator <=(const int32_t& lhs, const Rational& rhs) { return Rational(lhs) <= Rational(rhs); }
bool operator <=(const Rational& lhs, const int32_t& rhs) { return Rational(lhs) <= Rational(rhs); }

bool operator!=(const int32_t& lhs, const Rational& rhs) { return Rational(lhs) != Rational(rhs); }
bool operator!=(const Rational& lhs, const int32_t& rhs) { return Rational(lhs) != Rational(rhs); }







