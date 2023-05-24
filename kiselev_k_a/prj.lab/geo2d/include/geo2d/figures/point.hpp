#pragma once


class Point :public Figure {
public:
	Point();
	~Point() = default;

	Point(const Point&);
	Point& operator=(const Point&);

	Point(const int x, const int y);

	// void WriteTo(std::ostream& ostream) const override;
	 //void ReadFrom(std::istream& istream) override;

	const int& x() const;
	const int& y() const;

	void x(const int v);
	void y(const int v);

	void asTex(std::ofstream& texfile) override {
		texfile << "\\draw (" << x_ << "," << y_ << ") circle (" << 2 << "pt" << ");\n";
	}

private:
	int x_{ 0 };
	int y_{ 0 };
};

Point::Point() :Figure("point"), x_(0), y_(0)
{
}

Point::Point(const Point& rhs) :Figure("point"), x_(rhs.x_), y_(rhs.y_)
{
	if (this == &rhs) {
		return;
	}
}

Point& Point::operator=(const Point& rhs) {
	x_ = rhs.x_;
	y_ = rhs.y_;
	return *this;
}

Point::Point(const int x, const int y) :Figure("point"), x_(x), y_(y)
{
}

const int& Point::x()const {
	return x_;
}
const int& Point::y()const {
	return y_;
}

void Point::x(const int v) {
	x_ = v;
}
void Point::y(const int v) {
	y_ = v;
}
