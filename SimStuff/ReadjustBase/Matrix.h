#ifndef MATRIX__H_
#define MATRIX__H_
#include <vector>
#include <ostream>

class MyMatrix{
	public:
		MyMatrix():rows{0},cols{0}{}
		MyMatrix(const MyMatrix & mm);
		MyMatrix(int, int);

		MyMatrix  transpose();

		double operator()(int, int);
		MyMatrix operator*(const MyMatrix & mm);
		MyMatrix operator*(const double & s);
		MyMatrix operator-() const;
		MyMatrix operator+(const MyMatrix & mm) const;
		MyMatrix operator-(const MyMatrix & mm) const;
		void print();

		void setData(std::vector<double> dt);
		void setRow(int x, std::vector<double> r);
		void setCol(int y, std::vector<double> c);
		void setNum(int x, int y, double d);
		void emplace(int x, int y, MyMatrix);

		void insertRow(int x, std::vector<double> r);

		std::vector<double> getData(){return data;}
		
		int getRows(){return rows;}
		int getCols(){return cols;}

		MyMatrix getRow(int) const;
		MyMatrix getCol(int) const;
	private:
		int rows, cols;
		std::vector<double> data;
};



#endif

