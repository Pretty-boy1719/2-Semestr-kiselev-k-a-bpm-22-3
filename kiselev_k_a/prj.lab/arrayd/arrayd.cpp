#include<arrayd/arrayd.hpp>

#include<iostream>


ArrayD::ArrayD() {
	memory_ = nullptr;
	size_ = 0;
	capacity_ = 0;
}

ArrayD::ArrayD(const std::ptrdiff_t len) {
	if (len < 0) {
		throw std::invalid_argument("Expected non-negative value");
	}

	size_ = len;
	capacity_ = size_ + 5;
	memory_ = new double[capacity_] {};

	for (std::ptrdiff_t i = 0; i < size_; i += 1) {
		memory_[i] = 0.0;
	}
}

ArrayD::ArrayD(const std::ptrdiff_t len, const double num) {
	if (len < 0) {
		throw std::invalid_argument("Expected non-negative value");
	}

	size_ = len;
	capacity_ = size_ + 5;
	memory_ = new double[capacity_] {};

	for (std::ptrdiff_t i = 0; i < size_; i += 1) {
		memory_[i] = num;
	}
}

ArrayD::ArrayD(const ArrayD& rhs) {
	if (this == &rhs) {
		return;
	}

	size_ = rhs.size_;
	capacity_ = rhs.capacity_;
	memory_ = new double[capacity_] {};

	if (rhs.memory_ == nullptr) {
		memory_ = nullptr;
	}

	std::copy(rhs.memory_, rhs.memory_ + rhs.size_, memory_);
}

ArrayD::~ArrayD() {
	delete[] memory_;
	memory_ = nullptr;
}

ArrayD& ArrayD::operator=(const ArrayD& rhs) {
	if (this == &rhs) {
		return *this;
	}

	size_ = rhs.size_;
	capacity_ = rhs.capacity_;


	if (memory_ != nullptr)
		delete[] memory_;

	memory_ = new double[capacity_] {};

	for (std::ptrdiff_t i = 0; i < size_; i += 1) {
		memory_[i] = rhs.memory_[i];
	}
	return *this;
}

double& ArrayD::operator[](const std::ptrdiff_t i) {
	if (i < 0 || i >= size_) {
		throw std::out_of_range("Index out of range1");
	}

	return memory_[i];
}

const double& ArrayD:: operator[](const std::ptrdiff_t i) const {
	if (i < 0 || i >= size_) {
		throw std::out_of_range("Index out of range2");
	}
	return memory_[i];
}

std::ptrdiff_t ArrayD::ssize() const noexcept {
	return size_;
}

void ArrayD::resize(const std::ptrdiff_t new_size) {
	if (new_size <= 0) {
		throw std::invalid_argument("Value out of range");
	}

	if (new_size < capacity_) {
		size_ = new_size;
		return;
	}

	capacity_ = new_size + 5;
	double* new_memory = new double[capacity_] {};

	for (std::ptrdiff_t i = 0; i < size_; i += 1) {
		new_memory[i] = memory_[i];
	}

	delete[] memory_;
	size_ = new_size;
	memory_ = new_memory;
}

void ArrayD::insert(const std::ptrdiff_t i, const double value) {
	if (i < 0 || i > size_) {
		throw std::out_of_range("Index out of range3");
	}

	if (size_ + 1 < capacity_)
		resize(size_ + 1);
	else
		size_ += 1;

	for (std::ptrdiff_t j = size_; j > i; j -= 1) {
		memory_[j] = memory_[j - 1];
	}
	memory_[i] = value;
}

void ArrayD::remove(const std::ptrdiff_t i) {
	if (i < 0 || i >= size_) {
		throw std::out_of_range("Index out of range4");
	}

	for (std::ptrdiff_t j = i; j < size_ - 1; j += 1) {
		memory_[j] = memory_[j + 1];
	}
	size_ -= 1;
}

void ArrayD::push_back(const double value) {
	insert(size_, value);
}

void ArrayD::pop_back() {
	remove(size_ - 1);
}

std::istream& ArrayD::readFrom(std::istream& istrm) {
	std::ptrdiff_t num_inp(0);

	istrm >> num_inp;
	if (num_inp < 0) {
		throw std::invalid_argument("Expected positive value");
	}

	double temp_num = 0;
	for (std::ptrdiff_t i = 0; i < num_inp; i += 1) {
		istrm >> temp_num;
		insert(size_, temp_num);
	}

	return istrm;
}

std::ostream& ArrayD::writeTo(std::ostream& ostrm) const {
	ostrm << '[';
	for (std::ptrdiff_t i = 0; i < size_ - 1; i += 1) {
		ostrm << memory_[i] << separator_;
	}
	ostrm << memory_[size_ - 1] << ']';
	return ostrm;
}

std::istream& operator>>(std::istream& istrm, ArrayD& rhs) {
	return rhs.readFrom(istrm);
}

std::ostream& operator<<(std::ostream& ostrm, const ArrayD& rhs) {
	return rhs.writeTo(ostrm);
}