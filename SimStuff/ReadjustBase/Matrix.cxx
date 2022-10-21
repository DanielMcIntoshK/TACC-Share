#include "Matrix.h"
#include <iostream>

MyMatrix::MyMatrix(const MyMatrix & mm):data{mm.data},rows{mm.rows},cols{mm.cols} {

}

MyMatrix::MyMatrix(int _rows, int _cols): rows{_rows},cols{_cols} {
	data.resize(rows*cols);
	for(int n = 0; n < rows*cols;n++){
		data[n]=(n/cols==n%cols)?1.0:0.0;
	}
}

MyMatrix MyMatrix::transpose(){
	MyMatrix mm(cols,rows);
	for(int r = 0; r <rows;r++){
		for(int c = 0; c < cols; c++){
			mm.data[c*mm.cols+r]=data[r*cols+c];
		}
	}
	return mm;
}

double MyMatrix::operator()(int r, int c){
	if(r>=rows || c >= cols) {
		std::cout << "ATTEMPT TO ACCESS INVALID INDEX\n";
		return 0;
	}
	return data[r*cols+c];
}

MyMatrix MyMatrix::operator*(const MyMatrix&mm){
	if(cols!=mm.rows){
		std::cout << "INVALID MATRIX MULTIPLICATION " << rows << "X"<<cols << "  " << mm.rows << "X" << mm.cols <<"\n";
		return MyMatrix(0,0);
	}
	if(cols*rows*mm.rows*mm.cols==0){
		return MyMatrix(0,0);
	}
	MyMatrix nm(rows, mm.cols);
	if(rows*mm.cols==1){
		nm.data[0]=0;
		for(int x=0; x < cols; x++){
			nm.data[0]+=data[x]*mm.data[x];
		}	
	}
	else{
		for(int x=0; x < rows; x++){
			for(int y = 0; y < mm.cols; y++){
				int index=x*mm.cols+y;
				nm.data[index]=(getRow(x)*mm.getCol(y)).data[0];
			}
		}
	}
	return nm;
}

MyMatrix MyMatrix::operator*(const double & s){
	MyMatrix mm(rows,cols);
	for(int n = 0; n < rows*cols;n++){
		mm.data[n]=data[n]*s;
	}
	return mm;
}

MyMatrix MyMatrix::operator-() const{
	MyMatrix mm(*this);
	return mm*-1;
}

MyMatrix MyMatrix::operator+(const MyMatrix & mm) const{
	if(rows!=mm.rows || cols!=mm.cols){
		return MyMatrix(0,0);
	}
	MyMatrix sum(rows,cols);
	for(int n =0; n < rows*cols;n++){
		sum.data[n]=data[n]+mm.data[n];
	}
	return sum;
}

MyMatrix MyMatrix::operator-(const MyMatrix &mm) const{
	return *this+(-mm);
}

void MyMatrix::print(){
	for(int x =0; x < rows; x++){
		for(int y = 0; y < cols; y++){
			std::string dataStr=std::to_string(data[x*cols+y]);
			if(dataStr[0]!='-') dataStr=" "+dataStr;
			dataStr.resize(12, ' ');
			std::cout << dataStr;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void MyMatrix::setData(std::vector<double> dt){
	if(dt.size() == rows*cols){
		data=dt;
	}
	else{
		std::cout << "INVALID DATA SET\n";
	}
}

void MyMatrix::setRow(int x, std::vector<double> r){
	if(r.size() == cols){
		for(int c = 0; c<cols;c++){
			data[x*cols+c]=r[c];
		}
	}
	else{
		std::cout << "INVALID ROW SET\n";
	}
}

void MyMatrix::setCol(int y, std::vector<double> c){
	if(c.size() == rows){
		for( int r = 0; r < rows;r++){
			data[r*cols+y]=c[r];
		}
	}
	else{
		std::cout << "INVALID COL SET\n";
	}
}

void MyMatrix::setNum(int x, int y, double d){
	data[x*cols+y]=d;
}

void MyMatrix::emplace(int x, int y, MyMatrix mm){
	for(int r=0; r+y <rows &&r<mm.rows;r++){
		for(int c=0;c+x<cols&&c<mm.cols;c++){
			data[(r+y)*cols+(c+x)]=mm.data[r*mm.cols+c];
		}
	}
}

void MyMatrix::insertRow(int x, std::vector<double> r){
	int multi = r.size()%cols;
	if(multi != 0) return;
	rows+=r.size()/cols;
	auto dataItr=data.begin();
	for(int n = 0; n < x*cols; n++) dataItr++;
	data.insert(dataItr,r.begin(),r.end());
}

MyMatrix MyMatrix::getRow(int x) const{
	MyMatrix rm(1,cols);
	for(int c = 0; c < cols; c++){
		rm.data[c]=data[x*cols+c];
	}
	return rm;
}

MyMatrix MyMatrix::getCol(int y) const{
	MyMatrix cm(rows,1);
	for(int r = 0; r < rows; r++){
		cm.data[r]=data[r*cols+y];
	}
	return cm;
}

