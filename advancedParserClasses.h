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

		int numLeftParenthesis; // Indicates the number of left parenthesis '('
		int numRightParenthesis; // Indicates the number of right parenthesis ')'
		int numLeftBracket; // Indicates the number of left brackets '['
		int numRightBracket; // Indicates the number of right brackets ']'
		int numLeftCurly; // Indicates the number of left curly brackets '{'
		int numRightCurly; // Indicates the number of right curly brackets '}'
		
		// Private Functions
		TokenList getAssignmentStatements(TokenList &tokenList);
		TokenList getFunctionDeclarations(TokenList &tokenList);

		// Input: TokenList needed to be printed to the screen
		// Output: Prints the TokenList to the screen. If TokenList is empty, it will say that it is empty
		// NOTE: Does not change the TokenList itself
		void printTokenList(TokenList printTokens)
		{
			Token *t = printTokens.getFirst();

			// If printTokens is empty
			if (t == NULL)
			{
				cout << "Nothing to print";
			}

			// As long as t is not NULL
			while (t != NULL)
			{
				cout << t->getStringRep() << " ";
				t = t->getNext();
			}

			cout << endl;
		}
		Token* getUserDefined(TokenList &tokenList);
		void setIdentifierClass(Token *identifier_type, string Type);
		void LogicStatements();
	public:
		Clippy();
		void errorAssistant(TokenList &tokenList);

		void checkFunctionDeclaration();
		void checkFunctionImplementation();
		bool checkConditionalStatement(const string &str);
		bool checkJumpConditional(const string &str);
		bool includeStatement(const string &str);
		int checkSecondHalf(TokenList &tokenList, int previous_error);
	}; // end of Class Clippy

} // end of namespace ensc251_advancedparserclass

#endif /* ADVANCEDPARSERCLASSES_H_ */