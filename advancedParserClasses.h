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
	const string assignmentOperators [] = { "=", "++", "--", "+=", "*=", "/=", "&=", "%=", "|=", "^=" };
	const string keyWords_conditional [] = { "if", "else if", "else", "for", "while", "do", "switch" };
	const string keyWords_jumpConditional [] = { "break", "continue"};
	const string keyWords_Declaration [] = {"int", "float", "bool", "double", "string", "class", "struct", "union", "void"};

	const int numElements_assignmentOperators = 9;
	const int numElements_keyWords_conditional = 7;
	const int numElements_keyWords_jumpConditional = 2;
	const int numElements_keyWords_Declaration = 9;

	// Type of identifiers
	enum IdentifierType
	{
		T_Integer,			// Integer type
		T_Float,			// Float type
		T_Boolean,			// Boolean Type
		T_Double,			// Double Type
		T_String,			// String Type
		T_Class,			// Class Type
		T_Structure,		// Structure Type
		T_Union,			// Union Type
		T_Void,				// Void Type
		T_Unknown			//if token does not belong to above classes then place it in this category
	};


	// Class Clippy identifies, checks for errors and analyzes the input code
	class Clippy
	{
	private:
		// Private Variables
		bool syntaxError_Found; // True if a syntax error is found
		bool logicError_Found; // True if a logic error is found
		bool functionDecError_Found; // True if a function declaration error is found
		bool functionImpError_Found; // True if a function implementation error is found
		bool endQuote; // When false, it is the end of a quote or not a quote (e.g "). When true, it is inside a quote
		int numAssignmentStatements; // Number of assignment statements
		int numFunctionDeclarations; // Number of functions
		int numTokensParsed; // Number of tokens parsed
		int numSyntaxError_Found; // Number of syntax errors found
		int numUnknown; // Number of unknown types

		// Private Functions
		Token* getAssignmentStatements(TokenList &tokenList);
		Token* getFunctionDeclarations(TokenList &tokenList);
		Token* getUserDefined(TokenList &tokenList);
		Token* setIdentifierClass(Token *identifier_type, Token *identifier);
		void LogicStatements();
	public:
		Clippy();
		void errorAssistant(TokenList &tokenList);

		void checkFunctionDeclaration();
		void checkFunctionImplementation();
		bool checkConditionalStatement(const string &str);
		bool checkJumpConditional(const string &str);
		bool includeStatement(const string &str);
		bool checkSecondHalf(const char &first_half, const string &str);
	}; // end of Class Clippy

} // end of namespace ensc251_advancedparserclass

#endif /* ADVANCEDPARSERCLASSES_H_ */