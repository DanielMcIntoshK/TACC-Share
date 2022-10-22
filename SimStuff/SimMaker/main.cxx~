#include <iostream>
#include <fstream>

int main(){
	std::ofstream outFile;
	outFile.open("SimTry1.dsmt");

	outFile << "./MnTransSearch_#" << std::endl <<
		"20 React.xyz Prod.xyz" << std::endl;

	for(int i = 0; i < 4; i++){
		double x = (double)i/4;
		outFile << "1 1 1 ";
		outFile << 3+2*x;
		outFile << " -1 -1 3 ";
		outFile << 4+2*x;
		outFile << " 0 .25";
		outFile << std::endl;
	}
	for(int i = 0; i < 4; i++){
		double x = (double)i/4;
		outFile << "1 1 1 ";
		outFile << 3+2*x;
		outFile << " -1 -1 3 ";
		outFile << 4+2*x;
		outFile << " .0625 .25";
		outFile << std::endl;
	}	

	for(int i = 0; i < 4; i++){
		double x = (double)i/4;
		outFile << "1 1 1 ";
		outFile << 3+2*x;
		outFile << " -1 -1 3 ";
		outFile << 4+2*x;
		outFile << " .125 .25";
		outFile << std::endl;
	}

	for(int i = 0; i < 4; i++){
		double x = (double)i/4;
		outFile << "1 1 1 ";
		outFile << 3+2*x;
		outFile << " -1 -1 3 ";
		outFile << 4+2*x;
		outFile << " .25 .25";
		outFile << std::endl;
	}

	for(int i = 0; i < 4; i++){
		double x = (double)i/4;
		std::cout << x << std::endl;
		outFile << "1 1 1 ";
		outFile << 3+2*x;
		outFile << " -1 -1 3 ";
		outFile << 4+2*x;
		outFile << " .333333 .25";
		outFile << std::endl;
	}

	outFile.close();

	return 0;
}
