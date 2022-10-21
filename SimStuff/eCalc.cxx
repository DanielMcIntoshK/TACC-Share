#include <iostream>
#include <cmath>

#define E_CLOSE 2.7182818284590452353602874713526624977572470936999595749669676

int main(int argc, char** argv){
	
	for(int k=1; k <= 10; k++){
		float n = std::pow(10,k);
		float frac = 1+1/n;
		float e = std::pow(frac,n);
		float percentError=std::abs(e-E_CLOSE)/E_CLOSE*100; 
		std::cout << std::fixed << frac << " " << n << ": " << e << "---" << "PERCENT ERROR: " << percentError<<std::endl;
	}

	std::cout << "POWERSERIES METHOD\n";
	int factorial=1;
	float e=0;
	for(int k=1; k <=20; k++){
		e+=1/(float)factorial;
		factorial*=k;
		float percentError = std::abs(e-E_CLOSE)/E_CLOSE*100;
		std::cout << factorial <<  ": " << e << "---" << "PERCENT ERROR: " << percentError << std::endl;
	}

	return 0;
}
