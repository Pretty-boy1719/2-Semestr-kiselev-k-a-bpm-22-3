#pragma once


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

Figure::Figure(std::string figure) : name_(figure)
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