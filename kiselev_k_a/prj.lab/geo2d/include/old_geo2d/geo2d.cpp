#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<utility>
#include<tuple>

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

class Figure {

public:
	Figure(std::string);
	Figure() = default;
	~Figure() = default;

	Figure(const Figure&);

	//virtual void WriteTo(std::ostream& ostream) const = 0;
	//virtual void ReadFrom(std::istream& istream) = 0;

	Figure& operator=(const Figure&);
	virtual void asTex(std::ofstream& texfile) = 0;
	std::string getName() const { return name_; }

private:
	std::string name_{ "figure" };
};

Figure::Figure(std::string figure): name_(figure)
{
}

Figure::Figure(const Figure& rhs) {
	if (this == &rhs) {
		return;
	}
	name_ = rhs.name_;
}

Figure& Figure::operator=(const Figure& rhs) {
	if (this == &rhs) {
		return *this;
	}
	name_ = rhs.name_;
	return *this;
}


//std::ostream& operator<<(std::ostream& ostream, const Figure& figure);
//std::istream& operator>>(std::istream& istream, Figure& figure);



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

Point::Point(const Point& rhs):Figure("point"),x_(rhs.x_), y_(rhs.y_) 
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

Point::Point(const int x, const int y):Figure("point"), x_(x),y_(y) 
{
}

const int& Point::x()const{
	return x_;
}
const int& Point::y()const{
	return y_;
}

void Point::x(const int v) {
	x_ = v;
}
void Point::y(const int v) {
	y_ = v;
}


template<bool closed_ = true>
class Polyline : public Figure {
public:
	static constexpr bool closed = closed_;
public:
	Polyline();
	Polyline(std::initializer_list<std::tuple<int, int >> il);
	~Polyline() = default;

	void FormatingOutput(std::string& points) {
		points = "";
		for (auto point : points_) {
			points += "(" + std::to_string(std::get<0>(point)) + "," + std::to_string(std::get<1>(point)) + ") -- ";
		}
		if (points.size() >= 4)
			points.resize(points.size() - 4);
		points += ";\n";
	}

	void asTex(std::ofstream& texfile) override {
		std::string formating_output = "";
		FormatingOutput(formating_output);
		texfile << "\\draw " + formating_output;
	}

private:
	std::vector<std::tuple<int,int>> points_;
	ptrdiff_t size_{ 0 };
};

template<bool closed_>
Polyline<closed_>::Polyline():size_(0)
{
}

template<bool closed_>
Polyline<closed_>::Polyline(std::initializer_list<std::tuple<int,int>> il) : size_(il.size()) {
	for (auto point : il)
		points_.push_back(point);
}


int main() {
	std::string filename = "drawing.tex";
	std::ofstream texfile;
	texfile.open(filename);
	texfile << "\\documentclass{article}\n\\usepackage{tikz}\n\\begin{document}\n\\begin{tikzpicture}\n";

	Point p(1, 1);
	p.asTex(texfile);

	std::tuple<int, int> a{ 2,3 };
	std::tuple<int, int> b{ 5,4 };
	std::tuple<int, int> c{ 1,2 };

	Polyline<false> line{ a,b,c };
	line.asTex(texfile);

	texfile << "\\end{tikzpicture}\n\\end{document}\n";
	texfile.close();
	return 0;
}
