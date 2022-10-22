#include "SimulatorSetup.h"
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

SimulatorSetup::SimulatorSetup(){
	simCount=0;
}

int SimulatorSetup::loadMolecules(std::string setupFile){
	std::ifstream inFile;
	inFile.open(setupFile);

	if(!inFile){
		std::cout << "INVALID SETUP FILE\n";
		return -1;
	}
	
	std::string firstLine;
	std::getline(inFile, firstLine);

	folderBase=firstLine;

	std::getline(inFile, firstLine);

	double Pi = 3.14159265358979;
	
	int spacePos = firstLine.find_first_of(' ');
	simCount=std::stoi(firstLine.substr(0,spacePos));
	firstLine=firstLine.substr(spacePos+1);
	spacePos=firstLine.find_first_of(' ');
	std::string ReactName=firstLine.substr(0,spacePos);
	firstLine=firstLine.substr(spacePos+1);
	std::string ProdName=firstLine;

	molecules.resize(simCount);

	for(int i = 0; i < simCount; i++){
		molecules[i][0].loadMolecule(ReactName);
		molecules[i][0].adjust(0,-2,3);

		molecules[i][1].loadMolecule(ProdName);
		molecules[i][1].adjust(0,-2,3);

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
		molecules[i][1].addStructure("benzo.xyz", {values[4],values[5],values[6]},values[7],Pi*values[8],Pi*values[9]+Pi/2,molecules[i][1].getCount());
	}
	return 0;
}

void SimulatorSetup::createSimulations(){
	int folderCutOff=folderBase.find_last_of("/");
	
	fs::create_directory(folderBase.substr(0,folderCutOff));

	for(int i =0; i < simCount; i++){
		std::string simName=folderBase.substr(folderCutOff+1);
		int hashPos=simName.find("#");
		simName=simName.substr(0,hashPos)+std::to_string(i)+simName.substr(hashPos+1);
		std::ofstream outFile;
		
		if(fs::exists(folderBase.substr(0,folderCutOff)+"/"+simName)){
			fs::remove_all(folderBase.substr(0,folderCutOff)+"/"+simName);
		}
		fs::create_directory(folderBase.substr(0,folderCutOff)+"/"+simName);

		outFile.open(folderBase.substr(0,folderCutOff)+"/"+simName+"/"+simName+".config");
		fs::create_directory(folderBase.substr(0,folderCutOff)+"/"+simName);

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

		outFile.open(folderBase.substr(0,folderCutOff)+"/"+simName+"/RunScript");
		outFile << "#!/bin/bash" << std::endl <<
			"#SBATCH -J MN_TRANS_SEARCH_"+simName << std::endl <<
			"#SBATCH -o output.%j" << std::endl <<
			"#SBATCH -e error.%j" << std::endl <<
			"#SBATCH -N 1 -n 1" << std::endl <<
			"#SBATCH -p normal" << std::endl <<
			"#SBATCH -t 42:00:00" << std::endl <<
			std::endl <<
			"module load gaussian" << std::endl <<
			std::endl <<
			"g16 < " << simName << ".config > " << simName << "_output.log";
		outFile.close();

		molecules[i][0].outputxyz(folderBase.substr(0,folderCutOff)+"/"+simName+"/"+simName+"_React.xyz");
		molecules[i][1].outputxyz(folderBase.substr(0,folderCutOff)+"/"+simName+"/"+simName+"_Prod.xyz");
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

