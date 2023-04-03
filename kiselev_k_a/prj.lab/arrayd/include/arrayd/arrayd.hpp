#pragma once
#ifndef arrayd_arrayd_HPP_20231303 
#define arrayd_arrayd_HPP_20231303

#include <iosfwd>
#include <cstddef>


class ArrayD {
public:
	ArrayD();
	explicit ArrayD(const std::ptrdiff_t len);
	ArrayD(const std::ptrdiff_t len, const double num);
	explicit ArrayD(const ArrayD& rhs);
	~ArrayD();

	[[nodiscard]]std::ptrdiff_t ssize() const noexcept;
	void resize(const std::ptrdiff_t new_size);
	void insert(const std::ptrdiff_t i, const double value);
	void remove(const std::ptrdiff_t i);
	void push_back(const double value);
	void pop_back();

	std::istream& readFrom(std::istream& istrm);
	std::ostream& writeTo(std::ostream& ostrm) const;

	ArrayD& operator=(const ArrayD& rhs);
	[[nodiscard]]double& operator[](const std::ptrdiff_t i);
	[[nodiscard]]const double& operator[](const std::ptrdiff_t i) const;



private:
	std::ptrdiff_t size_{ 0 };
	std::ptrdiff_t capacity_{ 0 };
	double* memory_{ nullptr };

	static const char separator_{ ',' };
};

std::istream& operator>>(std::istream& istrm, ArrayD& rhs);
std::ostream& operator<<(std::ostream& ostrm, const ArrayD& rhs);
#endif




