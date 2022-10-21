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
	
	void loadMolecules(std::string setupFile);
	void createSimulations(std::string folderBase);
	
	void outputBasisSetInfo(std::ofstream & outFile);
	private:
	int simCount;
	std::vector<std::array<Molecule,2>> molecules;
};


#endif

