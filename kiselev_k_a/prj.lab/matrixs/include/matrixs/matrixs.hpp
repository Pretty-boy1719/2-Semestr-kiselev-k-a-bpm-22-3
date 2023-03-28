#pragma once
#ifndef matrixs_matrixs_HPP_20231503 
#define matrixs_matrixs_HPP_20231503

#include <iosfwd>
#include <cstddef>
#include <utility>
#include <iostream>

class MatrixS {
public:
	using size_type = std::pair<std::ptrdiff_t, std::ptrdiff_t>;

public:
	MatrixS(const size_type& size);
	MatrixS(const MatrixS& rhs);
	~MatrixS();


	MatrixS& operator=(const MatrixS& rhs);

	const size_type& ssize() const noexcept;
	int& at(const size_type& elem);
	const int at(const size_type& elem) const;
	void resize(const size_type& new_size);
	ptrdiff_t getRows() const noexcept;
	ptrdiff_t getCols() const noexcept;

private:
	int** data_{ nullptr };
	ptrdiff_t n_{ 0 };
	ptrdiff_t m_{ 0 };
	size_type size_{ 0,0 };
};



#endif