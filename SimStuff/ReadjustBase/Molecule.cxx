#include "Molecule.h"
#include <fstream>
#include <iostream>
#include <cmath>

Molecule::Molecule():atomCount{0}{}

void Molecule::operator*(const MyMatrix & mm){
	molecule=molecule*mm;
}

void Molecule::loadMolecule(std::string fileName){
	std::ifstream inFile;
	inFile.open(fileName);

	atoms.clear();
	atomCount=0;
	
	std::string input;
	std::getline(inFile, input);
	atomCount=std::stoi(input);
	std::getline(inFile, input);

	molecule=MyMatrix(atomCount,4);
	atoms.resize(atomCount);

	for(int a = 0; a < atomCount;a++){
		getline(inFile, input);
		std::string atomName=input.substr(0,input.find_first_of(' '));
		
		std::vector<std::string> coordStr;

		for(int n = 0; n < 3; n++){
			input=input.substr(input.find_first_of(' '));
			input=input.substr(input.find_first_not_of(' '));
			coordStr.push_back(input.substr(0,input.find_first_of(' ')));
		}

		atoms[a]=atomName;
		molecule.setRow(a,{std::stod(coordStr[0]),std::stod(coordStr[1]),std::stod(coordStr[2]),1.0});
		
	}
	inFile.close();
}

void Molecule::output(std::ostream & out){
	for(int a = 0; a < atomCount; a++){
		std::string atomLine=atoms[a];
		atomLine.resize(10,' ');
		for(int num=0; num<3;num++){
			std::string numStr;
			numStr=std::to_string(molecule(a,num));
			if(numStr[0]!='-'){numStr=" "+numStr;}
			if(num!=2) numStr.resize(16,' ');
			atomLine+=numStr;
		}
		out << atomLine << std::endl;
	}
}

void Molecule::outputxyz(std::string outputName,std::string message){
	std::ofstream outFile;
	outFile.open(outputName);

	outFile << atomCount << std::endl;
	outFile << message << std::endl;

	for(int a = 0; a < atomCount; a++){
		std::string atomLine=atoms[a];
		atomLine.resize(10,' ');
		for(int num=0;num<3;num++){
			std::string numStr;
			numStr=std::to_string(molecule(a,num));
			if(numStr[0]!='-'){numStr=" "+numStr;}
			if(num!=2) numStr.resize(16,' ');
			atomLine+=numStr;
		}
		outFile << atomLine << std::endl;
	}
}

void Molecule::adjust(int origin, int z, int x){
	MyMatrix oAt=molecule.getRow(origin);

	//(-oAt).print();
	oAt=-oAt;
	oAt.setNum(0,3,1);
	
	MyMatrix transMat(4,4);
	transMat.emplace(0,3,oAt);

	MyMatrix diffBefore=molecule.getRow(47)+oAt;
	diffBefore.setNum(0,3,0);

	molecule=molecule*transMat;
	
	diffBefore=molecule.getRow(47);
	diffBefore.setNum(0,3,0);
	
	if(z==origin){
		return;
	}
	MyMatrix zAt=molecule.getRow(std::abs(z));
	
	double angle = -std::atan2(zAt(0,1),zAt(0,0));
	MyMatrix rotMat(4,4);
	rotMat.setData({cos(angle), sin(angle), 0,0,
			-sin(angle), cos(angle), 0, 0,
			0,0,1,0,
			0,0,0,1});
	
	zAt=zAt*rotMat;
	
	molecule=molecule*rotMat;
	
	angle = -std::atan2(zAt(0,0),zAt(0,2));
	if(z<0){
		angle=3.1415926535898+angle;
	}	
	rotMat.setData({cos(angle), 0, -sin(angle),0,
			0, 1, 0, 0,
			sin(angle),0,cos(angle),0,
			0,0,0,1});
	
	molecule=molecule*rotMat;


	if(x==origin) return;

	MyMatrix xAt=molecule.getRow(std::abs(x));
	angle = -std::atan2(xAt(0,1),xAt(0,0));
	if(x<0) angle=3.1415926535898+angle;
	rotMat.setData({cos(angle), sin(angle),0,0,
			-sin(angle), cos(angle),0,0,
			0,0,1,0,
			0,0,0,1});
	molecule=molecule*rotMat;
}

void Molecule::addStructure(std::string structFile, std::vector<double> dir, double rad, double flip, double twist,int insertPos){
	Molecule tempM;
	tempM.loadMolecule(structFile);

	double mag = 0; 
	for(auto a: dir){mag+=a*a;}
	mag = rad/std::sqrt(mag);
	for(auto &a:dir){a*=mag;}

	MyMatrix flipMat(4,4), twistMat(4,4), transMat(4,4);
	flipMat.setData({1, 0, 0, 0,
			0,cos(flip), sin(flip), 0,
			0,-sin(flip), cos(flip),0,
			0,0,0,1});
	twistMat.setData({cos(twist),sin(twist),0,0,
			-sin(twist),cos(twist),0,0,
			0,0,1,0,
			0,0,0,1});
	transMat.setData({1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			dir[0],dir[1],dir[2],1});

	tempM.molecule=tempM.molecule*(flipMat*twistMat*transMat);

	auto atItr=atoms.begin();
	for(int i = 0; i < insertPos; i++){atItr++;}

	atoms.insert(atItr,tempM.atoms.begin(),tempM.atoms.end());
	molecule.insertRow(insertPos, tempM.molecule.getData());
	atomCount+=tempM.atomCount;
}

void Molecule::addAtom(std::string atomName, std::vector<double> dir, double rad, int insertPos){
	double mag=0;
	for(auto a:dir){mag+=a*a;}
	mag=rad/std::sqrt(mag);
	for(int i = 0; i < dir.size();i++){
		dir[i]=dir[i]*mag;
	}
	dir.push_back(1.0);
	auto atPos=atoms.begin();
	for(int i =0; i < insertPos; i++){atPos++;}
	atoms.insert(atPos,atomName);
	molecule.insertRow(insertPos, dir);
	atomCount++;
}

