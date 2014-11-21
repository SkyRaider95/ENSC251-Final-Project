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
	const string keyWords_logic [] = { "if", "else if", "else", "for", "while" };
	const string keyWords_function [] = {"hello"};

	const int numElements_keyWords_logic = 5;
	const int numElements_keyWords_function = 1;

	// Class Identify checks the assignment statements, and for functions 
	class Identify
	{
	private:
	public:
		Identify();
		void AssignmentStatements();
		void FunctionStatements();
		void LogicStatements();

	}; // end of class Identify

	// Class Clippy checks for errors and analyzes the input code
	class Clippy
	{
	private:
	public:
		void checkLogicStatement();
		bool includeStatement(const string &str);
	}; // end of Class Clippy

} // end of namespace ensc251_advancedparserclass

#endif /* ADVANCEDPARSERCLASSES_H_ */