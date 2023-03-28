#include<matrixs/matrixs.hpp>

#include<iostream>


MatrixS::MatrixS(const size_type& size)
{
	if (size.first <= 0 || size.second < 0) {
		throw std::invalid_argument("Expected positive value");
	}
	m_ = size.first;
	n_ = size.second;
	data_ = new int* [m_];
	for (ptrdiff_t i = 0; i < m_; i += 1) {
		data_[i] = new int[n_];
	}
}

MatrixS::MatrixS(const MatrixS& rhs) {
	*this = rhs;
}

MatrixS::~MatrixS() {
	for (ptrdiff_t i = 0; i < m_; i += 1) {
		delete[] data_[i];
	}
	delete[] data_;

	data_ = nullptr;
	m_ = -1;
	n_ = -1;
}

MatrixS& MatrixS::operator=(const MatrixS& rhs) {
	for (ptrdiff_t i = 0; i < m_; i += 1) {
		delete[] data_[i];
	}
	delete[] data_;

	m_ = rhs.m_;
	n_ = rhs.n_;

	data_ = new int* [m_];
	for (ptrdiff_t i = 0; i < m_; i += 1) {
		data_[i] = new int[n_];
	}

	for (ptrdiff_t i = 0; i < m_; i += 1) {
		for (ptrdiff_t j = 0; j < n_; j += 1) {
			data_[i][j] = rhs.data_[i][j];
		}
	}
	return *this;
}

const MatrixS::size_type& MatrixS::ssize() const noexcept {
	return std::make_pair(m_, n_);
}

int& MatrixS::at(const size_type& elem) {
	if (elem.first < 0 || elem.first>=m_ ||
		elem.second < 0 || elem.second >= n_) {
		throw std::invalid_argument("Index out of range");
	}

	return data_[elem.first][elem.second];
}

const int MatrixS::at(const size_type& elem) const {
	if (elem.first < 0 || elem.first >= m_ ||
		elem.second < 0 || elem.second >= n_) {
		throw std::invalid_argument("Index out of range");
	}

	return data_[elem.first][elem.second];
}

void MatrixS::resize(const size_type& new_size) {
	if (new_size.first <= 0 || new_size.second <= 0) {
		throw std::invalid_argument("Expected positive value");
	}
	if (new_size.first <= m_ && new_size.second <= n_)
	{
		m_ = new_size.first;
		n_ = new_size.second;
		return;
	}

	int** new_data = new int* [new_size.first];
	for (ptrdiff_t i = 0; i < new_size.first; i += 1) {
		new_data[i] = new int[new_size.second]{};
	}

	for (ptrdiff_t i = 0; i < std::min(m_, new_size.first); i += 1) {
		for(ptrdiff_t j = 0; j < std::min(n_, new_size.second); j += 1){
			new_data[i][j] = data_[i][j];
		}
	}

	for (ptrdiff_t i = 0; i < m_; i += 1) {
		delete[] data_[i];
	}
	delete[] data_;

	
	data_ = new_data;
	m_ = new_size.first;
	n_ = new_size.second;
}

ptrdiff_t MatrixS::getRows() const noexcept {
	return m_;
}

ptrdiff_t MatrixS::getCols() const noexcept {
	return n_;
}
