#ifndef ADVANCEDPARSERCLASSES_H_
#define ADVANCEDPARSERCLASSES_H_

/*
All the code written by
Choong Jin Ng (301226977)
Steven Luu    (301150253)
*/

#include <string>
#include <cctype>
#include <iostream>
#include "lexemesTypes.h"
#include "parserClasses.h"

using namespace std;

namespace ensc251_advancedparserclass
{
	// Public Constants and Arrays
	const string keyWords_conditional [] = { "if", "else if", "else", "for", "while", "do", "switch" };
	const string keyWords_jumpConditional [] = { "break", "continue" };
	const string keyWords_function [] = {"hello"};

	const int numElements_keyWords_conditional = 7;
	const int numElements_keyWords_jumpConditional = 2;
	const int numElements_keyWords_function = 1;

	// Class Identify checks the assignment statements, and for functions 
	class Identify
	{
		friend class Clippy;

	private:
		bool endQuote; // When false, it is the end of a quote or not a quote (e.g "). When true, it is inside a quote
	public:
		Identify();
		Token* AssignmentStatements(TokenList &tokenList);
		Token* FunctionStatements(TokenList &tokenList);
		void LogicStatements();

	}; // end of class Identify

	// Class Clippy checks for errors and analyzes the input code
	class Clippy
	{
	private:
		bool syntaxError_Found; // True if a syntax error is found
		bool logicError_Found; // True if a logic error is found
	public:
		Clippy();
		void errorAssistant();

		bool checkConditionalStatement(const string &str);
		bool checkJumpConditional(const string &str);
		bool includeStatement(const string &str);

		bool checkSecondHalf(const char &first_half, const string &str);
	}; // end of Class Clippy

} // end of namespace ensc251_advancedparserclass

#endif /* ADVANCEDPARSERCLASSES_H_ */