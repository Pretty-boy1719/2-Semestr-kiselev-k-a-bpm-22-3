#pragma once


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
		points += " -- cycle;\n";
	}

	void asTex(std::ofstream& texfile) override {
		std::string formating_output = "";
		FormatingOutput(formating_output);
		texfile << "\\draw " + formating_output;
	}

private:
	std::vector<std::tuple<int, int>> points_;
	ptrdiff_t size_{ 0 };
};

template<bool closed_>
Polyline<closed_>::Polyline() :size_(0)
{
}

template<bool closed_>
Polyline<closed_>::Polyline(std::initializer_list<std::tuple<int, int>> il) : size_(il.size()) {
	for (auto point : il)
		points_.push_back(point);
}