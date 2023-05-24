//случайно удалил версию с контрольной из-за git push -f, повторно заливаю

#include <iostream>
#include<tuple>
#include<vector>
#include<fstream>
#include<string>

class Quad {
public:
	Quad() :x_(0), y_(0) {}
	Quad(double x, double y) :x_(x), y_(y) {}

  /*  virtual void Draw(std::ofstream& texfile) = 0;

    virtual void Scale(double scale = 1) = 0;

	*/
protected:
	double x_{ 0 };
	double y_{ 0 };
};

class Rect :public Quad {
public:
	Rect():width_(0),length_(0){}
	Rect(double length, double width):Quad(),length_(length), width_(width) {}
	Rect(double x, double y, double length, double width):Quad(x,y),length_(length), width_(width) {}

    void Scale(double scale) {
        width_ *= scale;
        length_ *= scale;
    }

	void FormatingOutput(std::string& points) {
		points = "";
		points += "(" + std::to_string(x_ + length_ / 2) + "," + std::to_string(y_ + width_ / 2) + ")" + " -- ";
		points += "(" + std::to_string(x_ + length_ / 2) + "," + std::to_string(y_ - width_ / 2) + ")" + " -- ";
		points += "(" + std::to_string(x_ - length_ / 2) + "," + std::to_string(y_ - width_ / 2) + ")" + " -- ";
		points += "(" + std::to_string(x_ - length_ / 2) + "," + std::to_string(y_ + width_ / 2) + ") -- cycle";
	}

	void Draw(std::ofstream& texfile)  {
		std::string points = "";
		FormatingOutput(points);
		texfile << "\\draw " << points << ";\n";
	}

    //cycle
private:
    double width_{ 0 };
    double length_{ 0 };
};

class Square :public Quad {
public:
    void Scale(double scale) {
        side_ *= scale;
    }
private:
    double side_{ 0 };
};


int main()
{
 
	std::string filename = "drawing.tex";
	std::ofstream texfile;
	texfile.open(filename);
	texfile << "\\documentclass{article}\n\\usepackage{tikz}\n\\begin{document}\n\\begin{tikzpicture}\n";

	
	Rect a(0.0, 0.0, 4.0, 5.0);
	a.Draw(texfile);

	a.Scale(3);
	a.Draw(texfile);

	texfile << "\\end{tikzpicture}\n\\end{document}\n";
	texfile.close();
	return 0;
}


