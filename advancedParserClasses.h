#ifndef ADVANCEDPARSERCLASSES_H_
#define ADVANCEDPARSERCLASSES_H_

/*
All the code written by
Choong Jin Ng (301226977)
Steven Luu    (301150253)
*/

#include <string>
#include <cctype>
#include "lexemesTypes.h"

using namespace std;

namespace ensc251_advancedparserclass
{
	// Public Constants and Arrays


	// Class Identify checks the assignment statements, and for functions 
	class Identify
	{
	private:
	public:
		Identify();
		void AssignmentStatements();
		void FunctionStatements();

	}; // end of class Identify

	// Class Clippy checks for errors and analyzes the input code
	class Clippy
	{
	private:
	public:
	}; // end of Class Clippy

} // end of namespace ensc251_advancedparserclass

#endif /* ADVANCEDPARSERCLASSES_H_ */