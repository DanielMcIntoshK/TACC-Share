#ifndef SIMULATORSETUP__H_
#define SIMULATORSETUP__H_
#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include "Molecule.h"

class SimulatorSetup{
	public:
	SimulatorSetup();
	
	int loadMolecules(std::string setupFile);
	void createSimulations();
	
	void outputBasisSetInfo(std::ofstream & outFile);
	private:
	int simCount;
	std::string folderBase;
	std::vector<std::array<Molecule,2>> molecules;
};


#endif

