#pragma once
#ifndef ARRAYT_ARRAYT_HPP_20231303 
#define ARRAYT_ARRAYT_HPP_20231303

#include <iosfwd>
#include <cstddef>
#include <iostream>
template<typename T>
class ArrayT {
public:

	ArrayT();
	explicit ArrayT(const std::ptrdiff_t len);
	ArrayT(const std::ptrdiff_t len, const T num);
	ArrayT(const ArrayT& rhs);
	~ArrayT();

	std::ptrdiff_t ssize() const noexcept;
	void resize(const std::ptrdiff_t new_size);
	void insert(std::ptrdiff_t i, const T value);
	void remove(const std::ptrdiff_t i);
	void push_back(const T value);
	void pop_back();

	std::istream& readFrom(std::istream& istrm);
	std::ostream& writeTo(std::ostream& ostrm) const;

	ArrayT& operator=(const ArrayT& rhs);
	[[nodiscard]]T& operator[](const std::ptrdiff_t i);
	[[nodiscard]]const T operator[](const std::ptrdiff_t i) const;

private:
	std::ptrdiff_t size_{ 0 };
	std::ptrdiff_t capacity_{ 0 };
	T* memory_{ nullptr };

	static const char separator_{ ',' };
};

template<typename T>
ArrayT<T>::ArrayT() {
	memory_ = nullptr;
	size_ = 0;
	capacity_ = 0;
}

template<typename T>
ArrayT<T>::ArrayT(const std::ptrdiff_t len) {
	if (len < 0) {
		throw std::invalid_argument("Expected non-negative value");
	}

	size_ = len;
	capacity_ = size_ + 5;
	memory_ = new T[capacity_]{};

	for (std::ptrdiff_t i = 0; i < size_; i += 1) {
		memory_[i] = 0;
	}
}

template<typename T>
ArrayT<T>::ArrayT(const std::ptrdiff_t len, const T num) {
	if (len < 0) {
		throw std::invalid_argument("Expected non-neative value");
	}

	size_ = len;
	capacity_ = size_ + 5;
	memory_ = new T[capacity_]{};

	for (std::ptrdiff_t i = 0; i < size_; i += 1) {
		memory_[i] = num;
	}
}

template<typename T>
ArrayT<T>::ArrayT(const ArrayT& rhs) {
	size_ = rhs.size_;
	capacity_ = rhs.capacity_;
	memory_ = new T[capacity_]{};

	for (std::ptrdiff_t i = 0; i < size_; i += 1) {
		memory_[i] = rhs.memory_[i];
	}
}

template<typename T>
ArrayT<T>::~ArrayT() {
	delete[] memory_;
	memory_ = nullptr;
}

template<typename T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT& rhs) {
	size_ = rhs.size_;
	capacity_ = rhs.capacity_;
	if (memory_ != nullptr)
		delete[] memory_;
	memory_ = new T[capacity_]{};

	for (std::ptrdiff_t i = 0; i < size_; i += 1) {
		memory_[i] = rhs.memory_[i];
	}
	return *this;
}

template<typename T>
T& ArrayT<T>::operator[](const std::ptrdiff_t i) {
	if (i < 0 || i >= size_) {
		throw std::out_of_range("Index out of range");
	}

	return memory_[i];
}

template<typename T>
const T ArrayT<T>:: operator[](const std::ptrdiff_t i) const {
	if (i < 0 || i >= size_) {
		throw std::out_of_range("Index out of range");
	}
	return memory_[i];
}

template<typename T>
std::ptrdiff_t ArrayT<T>::ssize() const noexcept {
	return size_;
}

template<typename T>
void ArrayT<T>::resize(const std::ptrdiff_t new_size) {
	if (new_size <= 0) {
		throw std::invalid_argument("Value out of range");
	}

	if (new_size < capacity_) {
		size_ = new_size;
		return;
	}

	capacity_ = new_size + 5;
	T* new_memory = new T[capacity_]{};

	for (std::ptrdiff_t i = 0; i < size_; i += 1) {
		new_memory[i] = memory_[i];
	}

	delete[] memory_;
	size_ = new_size;
	memory_ = new_memory;
}

template<typename T>
void ArrayT<T>::insert(std::ptrdiff_t i, const T value) {
	if (i < 0 || i > size_) {
		throw std::out_of_range("Index out of range");
	}

	if (size_ + 1 < capacity_)
		resize(size_ + 1);
	else
		size_ += 1;

	for (std::ptrdiff_t j = size_-1; j > i; j -= 1) {
		memory_[j] = memory_[j - 1];
	}
	memory_[i] = value;
}

template<typename T>
void ArrayT<T>::remove(const std::ptrdiff_t i) {
	if (i < 0 || i >= size_) {
		throw std::out_of_range("Index out of range");
	}

	for (std::ptrdiff_t j = i; j < size_ - 1; j += 1) {
		memory_[j] = memory_[j + 1];
	}
	size_ -= 1;
}

template<typename T>
void ArrayT<T>::push_back(const T value) {
	insert(size_, value);
}

template<typename T>
void ArrayT<T>::pop_back() {
	remove(size_ - 1);
}

template<typename T>
std::istream& ArrayT<T>::readFrom(std::istream& istrm) {
	std::ptrdiff_t num_inp(0);

	istrm >> num_inp;
	if (num_inp < 0) {
		throw std::invalid_argument("Expected positive value");
	}

	T temp_num = 0;
	for (std::ptrdiff_t i = 0; i < num_inp; i += 1) {
		istrm >> temp_num;
		insert(size_, temp_num);
	}

	return istrm;
}

template<typename T>
std::ostream& ArrayT<T>::writeTo(std::ostream& ostrm) const {
	ostrm << '[';
	for (std::ptrdiff_t i = 0; i < size_ - 1; i += 1) {
		ostrm << memory_[i] << separator_;
	}
	ostrm << memory_[size_ - 1] << ']';
	return ostrm;
}

template<typename T>
std::istream& operator>>(std::istream& istrm, ArrayT<T>& rhs) {
	return rhs.readFrom(istrm);
}

template<typename T>
std::ostream& operator<<(std::ostream& ostrm, const ArrayT<T>& rhs) {
	return rhs.writeTo(ostrm);
}

#endif

