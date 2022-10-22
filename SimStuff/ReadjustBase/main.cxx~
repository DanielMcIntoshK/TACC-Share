#include "Matrix.h"
#include "Molecule.h"
#include "SimulatorSetup.h"
#include <iostream>
#include <cmath>

int main(int argc, char** argv){
	double PI=3.1415926;
	
	//Molecule mol;
	//mol.loadMolecule("../Prod.xyz");
	//mol.adjust(0,-2,3);
	//mol.addAtom("Br",std::vector<double>{1,1,1},3.0,4);
	//mol.addStructure("../benzo.xyz", std::vector<double>{-1,-1,3},5,PI/4,PI/4+PI/2, mol.getCount());
	//mol.outputxyz("../test.xyz");
	
	SimulatorSetup ss;
	if(ss.loadMolecules(std::string(argv[argc-1]))!=0){
		return 0;
	}
	ss.createSimulations();

	return 0;
}
