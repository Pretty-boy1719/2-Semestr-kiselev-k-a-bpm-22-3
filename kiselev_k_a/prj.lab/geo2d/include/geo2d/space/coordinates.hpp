#pragma once

class Coordinates {
public:
	static constexpr std::size_t dimension = 2;
public:
	Coordinates() :x_(0), y_(0) {}
	~Coordinates() = default;
	Coordinates(const Coordinates& rhs) :x_(rhs.x_), y_(rhs.y_) {}
	Coordinates& operator=(const Coordinates& rhs) { x_ = rhs.x_; y_ = rhs.y_; }
	Coordinates(std::initializer_list<int> il) {
		std::vector<int> v;
		for (auto coordinate : il)
			v.push_back(coordinate);
		x_ = v[0];
		y_ = v[1];
	}

	std::tuple<int, int> get() const { return std::make_tuple(x_, y_); }
	const int& get(const int n)const {
		if (n == 0) return x_;
		else return y_;
	}


private:
	int x_{ 0 };
	int y_{ 0 };
};
