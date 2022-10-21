#include "SimulatorSetup.h"
#include <sstream>
#include <sys/stat.h>
#include <sys/type.h>

SimulatorSetup::SimulatorSetup(){
	simCount=0;
}

void SimulatorSetup::loadMolecules(std::string setupFile){
	std::ifstream inFile;
	inFile.open(setupFile);
	
	std::string firstLine;
	std::getline(inFile, firstLine);

	double Pi = 3.14159265358979;
	
	int spacePos = firstLine.find_first_of(' ');
	std::cout << firstLine << " " << firstLine.substr(0,spacePos) << std::endl;
	simCount=std::stoi(firstLine.substr(0,spacePos));
	firstLine=firstLine.substr(spacePos+1);
	spacePos=firstLine.find_first_of(' ');
	std::cout << firstLine << " " << firstLine.substr(0,spacePos)<< std::endl;
	std::string ReactName=firstLine.substr(0,spacePos);
	firstLine=firstLine.substr(spacePos+1);
	std::string ProdName=firstLine;
	std::cout << ProdName << std::endl;

	molecules.resize(simCount);

	for(int i = 0; i < simCount; i++){
		molecules[i][0].loadMolecule(ReactName);
		molecules[i][1].loadMolecule(ProdName);
		
		std::string inputLine;
		std::getline(inFile, inputLine);
		
		std::vector<double> values;
		std::stringstream numberStream(inputLine);
		for(std::string inv;numberStream>>inv;){
			values.push_back(std::stod(inv));
		}		
		
		if(values.size()!=10){
			std::cout << i << ": INVALID SIM\n";
		}

		molecules[i][0].addAtom("Br", {values[0],values[1],values[2]}, values[3],4);
		molecules[i][1].addStructure("../benzo.xyz", {values[4],values[5],values[6]},values[7],Pi*values[8],Pi*values[9],molecules[i][1].getCount());
	}
}

void SimulatorSetup::createSimulations(std::string folderBase){
	int folderCutOff=folderBase.find_last_of("/");
	for(int i =0; i < simCount; i++){
		std::string simName=folderBase.substr(folderCutOff+1);
		std::cout << simName << "\n";
		int hashPos=simName.find("#");
		simName=simName.substr(0,hashPos)+std::to_string(i)+simName.substr(hashPos+1);
		std::cout << simName << " " << hashPos <<"\n";
		std::ofstream outFile;
		
		std::mkdir(folderBase.substr(0,folderCutOff)+"/"+simName);

		outFile.open(folderBase.substr(0,folderCutOff)+"/"+simName+"/"+simName);
		
		outFile << "HELLO WORLD! " << i << std::endl;
		outFile << "%Chk=checkpoint.chk" << std::endl <<
			"%NProcShared=12" << std::endl << 
			"# wB97XD Gen Opt=(QST2) SCRF=(Solvent=TetraHydroFuran)" << std::endl << 
			std::endl <<
			"Mn Transition State Reactant" << std::endl <<
			std::endl <<
			"0 1" << std::endl;
		molecules[i][0].output(outFile);
		outFile << std::endl <<
				"Mn Transition State Product" << std::endl <<
			std::endl <<
			"0 1" << std::endl;
		molecules[i][1].output(outFile);
		outFile << std::endl;

		outputBasisSetInfo(outFile);	
		
		outFile << std::endl;

			
		outFile.close();

		molecules[i][0].outputxyz(folderBase.substr(0,folderCutOff)+"/React.xyz");
		molecules[i][1].outputxyz(folderBase.substr(0,folderCutOff)+"/Prod.xyz");
	}
}

void SimulatorSetup::outputBasisSetInfo(std::ofstream & outFile){
	std::ifstream basisSetInfo;
	basisSetInfo.open("BasisSet.dbsi");
	std::string inputStr;
	for(std::string inputStr; std::getline(basisSetInfo,inputStr);){
		outFile << inputStr<<std::endl;
	}
}

