/*
 * lexemesTypes.h
 * Created on: Oct 27, 2014
 */

/*
Choong Jin Ng (301226977)
Steven Luu    (301150253)
*/

// Last edited: 25 Nov 2014, 9.34pm

#ifndef LEXEMESTYPES_H_
#define LEXEMESTYPES_H_

//Use only the following libraries:
#include <string>
#include <cctype>

using namespace std;

namespace ensc251
{
	// Public Variables and tables

	// Table of operators
	const string tableOfOperators [] = { "+", "-", "/", "*", "=", "<", ">", "++", "--", "<<", ">>", "!=", "&", "&&", "|", "||", "[", "]", "==", "#"};
	// Table of Punctuators
	const char tableOfPunctuators [] = { ';', ',', '.', '(', ')', '{', '}' };

	// Table of Keywords
	const string tableOfKeywords [] = { "auto", "bool", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
		"enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static",
		"struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "asm", "_ss", "interrupt", "_cs", "cdecl",
		"near", "_ds", "far", "pascal", "_es", "huge", "catch", "class", "delete", "friend", "inline", "new", "operator", "overload",
		"private", "protected", "public", "template", "this", "throw", "try", "virtual", "include", "using", "namespace", "std"};

	// Table of Boolean Values
	const string booleanValues [] = { "true", "false" };
	// Table of Hexadecimal Characters
	const char hexStuff[] = { '0', 'x', 'X' };
	// Table of stuff that makes string
	const char stringStuff[] = { '"' };

	// A table of numbers, including hexadecimals
	const char numberStuff[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
		'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'u', 'U', 'l', 'L', '-'};

	// It's a dot. Nuff said
	const char dot = '.';

	// Table of letters
	const char identifierNames [] = { '_', 'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G', 'h', 'H',
		'i', 'I', 'j', 'J', 'k', 'K', 'l', 'L', 'm', 'M', 'n', 'N', 'o', 'O', 'p', 'P', 'q', 'Q', 'r', 'R', 's', 'S', 't', 'T',
        'u', 'U', 'v', 'V' , 'w','W', 'x', 'X', 'y', 'Y', 'z', 'Z' };

	//Table of Identifier Types
	const string tableOfIDtypes [] = { "bool", "int", "float", "string" };

	// Table of default libraries
	const string tableOfDefaultLibraries [] = { "<algorithm>", "<bitset>", "<cctype>",  "<chrono>", "<cmath>", "<complex>", "<complex deque>",
		"<condition_variable>", "<cstdio>", "<cstdlib>", "<exception>", "<fstream>", "<functional>", "<future>", "<iomanip>", "<ios>", "<iosfwd>",
		"<iostream>","<istream>", "<iterator>", "<limits>", "<list>", "<locale>", "<map>", "<memory>", "<mutex>", "<new>", "<numeric>", "<ostream>",
		"<queue>", "<random>", "<regex>", "<set>", "<sstream>", "<stack>", "<stdexcept>", "<streambuff>", "<string>", "<strstream>","<thread>",
		"<tuple>", "<typeinfo>", "<utility>", "<valarry>", "<vector>", "<xiosbase>", "<xlocale>", "<xlocinfo>", "<xlocmon>", "<xlocnum>", "<xloctime>",
		"<xmemory>", "<xstring>", "<xtree>", "<xutility>", "parserClasses.h", "lexemesTypes.h"};

	// Table of identifier words
	const string identifierWords [] = { "int", "double", "float", "string", "bool", "void", "class", "union", "struct" };
	
	const int numElement_tableOfOperators = 20; // Number of elements in the table of operators
	const int numElement_tableOfPunctuators = 7; // Number of elements in the table of punctuators
	const int numElement_tableOfKeywords = 63; // Number of elements in the table of keywords
	const int numElement_booleanValues = 2; // Number of elements in the table of boolean values

	const int numElement_hexStuff = 3;  // Number of elements in the table of hexadecimal values
	const int numElement_stringStuff = 1;  // Number of elements in the table of string stuff
	const int numElement_numberStuff = 27;  // Number of elements in the table of numbers
	const int numElement_identifierNames = 53;  // Number of elements in the table of letters
	const int numElement_tableOfIDtype = 4; // Number of elements in the table of identifier types
	const int numElement_tableOfDefaultLibraries = 57; // Number of elements in the table of libraries
	const int numElement_identifierWords = 9; // Number of elements in the table of identifier words

  //custom data type:
  enum LexemeType
  {
	  T_Identifier,
	  T_Operator,
	  T_Punctuator,
	  T_Keyword,
	  T_Boolean,
	  T_IntegerLiteral,
	  T_FloatLiteral,
	  T_StringLiteral,
	  T_Unknown,                  //if token does not belong to above classes then place it in this category
	  T_Library
  };

  //helper functions: for all of them
  //Input: a string value (char in case of isPunctuator() function)
  //Output: true/false depending on whether the input value is of type as denoted by the corresponding function name.
  //NOTE:- You need to DEFINE these functions in source file "lexemesTypes.cpp".
  bool isIdentifier(const string&);
  bool isOperator(const string&);
  bool isPunctuator(char);
  bool isKeyword(const string&);
  bool isBooleanValue(const string&);
  bool isIntegerLiteral(const string&);
  bool isFloatLiteral(const string&);
  bool isStringLiteral(const string&);

  // Own Function
  bool isDigitLiteral(const string&);
  bool isCheckIdentifierKeyWords(const string&);
  bool isLibraryLiteral(const string&);
}

#endif /* LEXEMESTYPES_H_ */
