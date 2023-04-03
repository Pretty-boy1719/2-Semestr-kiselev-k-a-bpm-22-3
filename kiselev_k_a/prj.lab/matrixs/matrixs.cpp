#include<matrixs/matrixs.hpp>

#include<iostream>


MatrixS::MatrixS(const SizeType& size)
{
	if (get<0>(size) <= 0 || get<1>(size) <= 0) {
		throw std::invalid_argument("Expected positive value");
	}
	m_ = get<0>(size);
	n_ = get<1>(size);
	data_ = new int* [m_];
	for (ptrdiff_t i = 0; i < m_; i += 1) {
		data_[i] = new int[n_];
	}
}

MatrixS::MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n): MatrixS(std::make_tuple(m, n))
{
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



int& MatrixS::at(const SizeType& elem) {
	if (get<0>(elem) < 0 || get<0>(elem)>=m_ ||
		get<1>(elem) < 0 || get<1>(elem) >= n_) {
		throw std::out_of_range("Index out of range");
	}

	return data_[get<0>(elem)][get<1>(elem)];
}

const int& MatrixS::at(const SizeType& elem) const{
	if (get<0>(elem) < 0 || get<0>(elem) >= m_ ||
		get<1>(elem) < 0 || get<1>(elem) >= n_) {
		throw std::out_of_range("Index out of range");
	}

	return data_[get<0>(elem)][get<1>(elem)];
}

int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) {
	return this->at(std::make_tuple(i, j));
}

const int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) const {
	return this->at(std::make_tuple(i, j));
}

void MatrixS::resize(const SizeType& new_size) {
	if (get<0>(new_size) <= 0 || get<1>(new_size) <= 0) {
		throw std::invalid_argument("Expected positive value");
	}
	if (get<0>(new_size) <= m_ && get<1>(new_size) <= n_)
	{
		m_ = get<0>(new_size);
		n_ = get<1>(new_size);
		return;
	}

	int** new_data = new int* [get<0>(new_size)];
	for (ptrdiff_t i = 0; i < get<0>(new_size); i += 1) {
		new_data[i] = new int[get<1>(new_size)]{};
	}

	for (ptrdiff_t i = 0; i < std::min(m_, get<0>(new_size)); i += 1) {
		for(ptrdiff_t j = 0; j < std::min(n_, get<1>(new_size)); j += 1){
			new_data[i][j] = data_[i][j];
		}
	}

	for (ptrdiff_t i = 0; i < m_; i += 1) {
		delete[] data_[i];
	}
	delete[] data_;

	
	data_ = new_data;
	m_ = get<0>(new_size);
	n_ = get<1>(new_size);
}

void MatrixS::resize(const std::ptrdiff_t i, const std::ptrdiff_t j) {
	this->resize(std::make_tuple(i, j));
}


const MatrixS::SizeType& MatrixS::ssize() const noexcept {
	return std::make_tuple(m_, n_);
}

std::ptrdiff_t MatrixS::nRows() const noexcept {
	return m_;
}
std::ptrdiff_t MatrixS::nCols() const noexcept {
	return n_;
}
