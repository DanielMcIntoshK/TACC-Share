#ifndef MOLECULE__H_
#define MOLECULE__H_
#include "Matrix.h"
#include <vector>
#include <string>

class Molecule{
	public:
		Molecule();

		void loadMolecule(std::string);
		void output(std::ostream&);
		void outputxyz(std::string, std::string="");

		void adjust(int origin, int z, int x);
		void addStructure(std::string structFile, std::vector<double> dir, double rad, double flip, double twist, int insertPos);
		void addAtom(std::string atomName, std::vector<double> dir, double rad,int insertPos);

		void operator*(const MyMatrix &);

		int getCount(){return atomCount;}
	protected:
		int atomCount;
		MyMatrix molecule;
		std::vector<std::string> atoms;
};


#endif

