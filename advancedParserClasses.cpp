/*
All the code written by
Choong Jin Ng (301226977)
Steven Luu    (301150253)
*/

#include <string>
#include <cctype>
#include <iostream>
#include "lexemesTypes.h"
#include "advancedParserClasses.h"
#include "parserClasses.h"

using namespace std;


namespace ensc251_advancedparserclass
{
	// **** Identify ****

	// Default Constructor
	Identify::Identify() : endQuote(false)
	{

	}

	//Input: a list of tokens
	//Output: head pointer to the list of assignment statements
	//NOTE: Assignment statement must end with a semi-colon
	//@ description: extract all the assignment statements from input token list, prepare a new token list (assignment list)
	//using extracted statements and return the head pointer to it
	Token* Identify::getAssignmentStatements(TokenList &tokenList)
	{
		// Creation of Assignment statements
		TokenList assignment_token;
		Token *temp_token = tokenList.getFirst();

		//Traversing through the list
		while (temp_token)
		{

			//Checking for assignment operator "="
			if (temp_token->getStringRep() == "=")
			{
				assignment_token.append(temp_token->getPrev());

				//Adds tokens to the list until it finds the end of the statement;
				while (temp_token->getStringRep() != ";")
				{
					assignment_token.append(temp_token->getStringRep());
					temp_token = temp_token->getNext();

					//When semicolon is found, append it to the list and the loop is over
					if (temp_token->getStringRep() == ";")
					{
						assignment_token.append(temp_token->getStringRep());
						numAssignmentStatements = numAssignmentStatements + 1;
					}
				}
			}

			// Next token 
			temp_token = temp_token->getNext();
		}

		// Return token list;
		return (assignment_token.getFirst());
	} // end of getAssignmentStatements

	/*//Input: a list of tokens
	//Output: head pointer to the list of function declaration
	//NOTE: Function declarations end at right parathesis
	Token* Identify::getFunctionDeclarations(TokenList &tokenList)
	{
		// Creation of Function Declaration statements
		TokenList function_declaration_token;
		Token *temp_token = tokenList.getFirst();

		while (temp_token)
		{
			//Checking for left parenthesis
			if (temp_token->getStringRep() == "(")
			{
				function_declaration_token.append(temp_token->getPrev());

				//Adds tokens to the list until it finds the end of the statement;
				while (temp_token->getStringRep() != ")")
				{
					function_declaration_token.append(temp_token->getStringRep());
					temp_token = temp_token->getNext();

					//When right parenthesis is found, append it to the list and the loop is over
					if (temp_token->getStringRep() == ")")
					{
						function_declaration_token.append(temp_token->getStringRep());
						numFunctionDeclarations = numFunctionDeclarations + 1;
					}
				}
			}

			// Next token 
			temp_token = temp_token->getNext();
		}

		// Return token list;
		return (function_declaration_token.getFirst());
	} // end of FunctionStatements*/
	
	Token* Identify::getFunctionDeclarations(TokenList &tokenList)
	{
		// Creation of Function Declaration statements
		TokenList function_declaration_token;
		Token *temp_token = tokenList.getFirst();

		while (temp_token)
		{
			//Checking for left parenthesis
			if (temp_token->getStringRep() == "(")
			{
				function_declaration_token.append(temp_token->getPrev());
				//Checks for keyword after left parenthesis
				for (int i = 0; i < numElement_tableOfKeywords; i++)
				{
					if (temp_token->getNext()->getStringRep() == tableOfKeywords[i])
					{
						//Adds tokens to the list until it finds the end of the statement;
						while (temp_token->getStringRep() != ";")
						{
							function_declaration_token.append(temp_token->getStringRep());
							temp_token = temp_token->getNext();

							//When right parenthesis is found, append it to the list and the loop is over
							if (temp_token->getStringRep() == ";")
							{
								function_declaration_token.append(temp_token->getStringRep());
								numFunctionDeclarations = numFunctionDeclarations + 1;
							}
						}
					}
				}

			}

			// Next token 
			temp_token = temp_token->getNext();
		}

		// Return token list;
		return (function_declaration_token.getFirst());
	} // end of FunctionStatements*/

	// **** Clippy ****

	// Default constructor
	Clippy::Clippy() : syntaxError_Found(false), logicError_Found(false)
	{
	}

	// Handles the bulk of the checking process
	void Clippy::errorAssistant()
	{


		// If a function is found
	}

	// Checks the function implementation
	void Clippy::checkFunctionImplementation()
	{

	}

	// Input: string
	// Output: Returns true if the conditional statement is found
	bool Clippy::checkConditionalStatement(const string &str)
	{
		for (int ii = 0; ii != numElements_keyWords_conditional; ii++)
		{
			// Matches a conditional keyword
			if (str == keyWords_conditional[ii])
			{
				return true;
			}
		}
		return false;
	}

	// Input: string
	// Output: Returns true if jump conditional statement is found. Returns false otherwise
	bool Clippy::checkJumpConditional(const string &str)
	{
		for (int ii = 0; ii != numElements_keyWords_jumpConditional; ii++)
		{
			//Matches a conditional jump statement
			if (str == keyWords_jumpConditional[ii])
			{
				return true;
			}
		}
		return false;
	}

	// Input: string
	// Output: Returns true if the library declaration is defined correctly, returns false otherwise
	bool Clippy::includeStatement(const string &str)
	{
		string temp_string;
		// Reading each character of the string
		for (int ii = 0; ii != str.length(); ii++)
		{
			temp_string =temp_string + str[ii];

			// #include is missing
			if (ii == 7 && (temp_string != "#include"))
			{
				return false;
			}
		}
		temp_string.clear();
		return true;
	}

	// Input: First half of punctuator (e.g ", <)
	// Output: Returns true if found. Otherwise, returns false
	bool checkSecondHalf(const char &first_half, const string &str)
	{
		char second_half = NULL;

		if (first_half == '<')
		{
			second_half = '>';
		}

		else if (first_half == '"')
		{
			second_half = first_half;
		}

		else if (first_half == '\'')
		{
			second_half = '\'';
		}

		// Invalid
		if (second_half == NULL)
		{
			cerr << "ERROR! Invalid first_half" << endl;
			return false;
		}

		for (int ii = 0; ii != str.length(); ii++)
		{
			if (second_half == str[ii])
			{
				return true;
			}
		}

		return false;
	}

} // end of namespace ensc251_advancedparserclass
