#include<iostream>

#include<geo2d/geo2d.hpp>

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