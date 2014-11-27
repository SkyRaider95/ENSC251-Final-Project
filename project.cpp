/*
Created by:
Choong Jin Ng 301226977
Steven Luu    301150253
*/

//Using the following libraries:
#include "parserClasses.h"
#include "advancedParserClasses.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace ensc251;
using namespace ensc251_advancedparserclass;

//Removes all inline comments from the tokenList including the // marker
//Returns the number of comments removed
int removeInlineComments(TokenList &tokenList)
{
	int counter = 0;
	Token* temp;
	Token* target1;
	Token* target2;
	temp = tokenList.getFirst();

	while (temp)
	{
		// Found comment
		if (temp->getStringRep() == "//")
		{
			counter++;
			target1 = temp;

			if (temp->getNext() != NULL)
			{
				target2 = new Token;
				target2 = temp->getNext();
				temp = target2->getNext();
				tokenList.deleteToken(target1);
				tokenList.deleteToken(target2);
			}
		}

		temp = temp->getNext();
	}
	return counter;
} // End of removeInlineComments

//Remove all block comments from the tokenList including /* and */ markers
//Returns the number of block comments removed (where each pair of /* and */ count as one comment)
int removeBlockComments(TokenList &tokenList)
{
	int counter = 0;
	Token* temp, *target;
	temp = tokenList.getFirst();
	bool block_comment = false;
	string temp_string;

	while (temp)
	{
		if (temp->getStringRep() == "/*")
		{
			counter++;
			block_comment = true;

			while (block_comment)
			{
				temp_string = temp->getStringRep();

				// Empty string
				if (temp_string.empty())
				{
					temp = temp->getNext();
				}

				// Found the end of block comment
				else if (temp_string == "*/")
				{
					block_comment = false;
					target = temp;
					temp = temp->getNext();
					tokenList.deleteToken(target);
				}

				// Delete comment
				else
				{
					target = temp;
					temp = temp->getNext();
					tokenList.deleteToken(target);
				}
			}
		}
		temp = temp->getNext();
	}

	return counter;
}

//Input: a list of tokens
//Output: head pointer to the list of assignment statements
//NOTE: Assignment statement must end with a semi-colon
//@ description: extract all the assignment statements from input token list, prepare a new token list (assignment list)
//using extracted statements and return the head pointer to it
Token* getAssignmentStatements(TokenList &tokenList)
{
	// Creation of Assignment statements
	Token *temp_token = tokenList.getFirst();
	TokenList assignment_token;
	int numAssignmentStatements = 0;
	//Traversing through the list
	while (temp_token)
	{
		//Checking for assignment operator "="
		if (temp_token->getStringRep() == "=")
		{
			//Adds tokens to the list until it finds the end of the statement;
			assignment_token.append(temp_token->getPrev());
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
	cout << numAssignmentStatements << endl;
	return assignment_token.getFirst();
}//

//Looks for the number of function declaration
Token* getFunctionDeclarations(TokenList &tokenList)
{
	// Creation of Function Declaration statements
	Token *temp_token = tokenList.getFirst();
	TokenList function_declaration_token;
	int numFunctionDeclarations = 0;
	while (temp_token)
	{
		//Checking for left parenthesis
		if (temp_token->getStringRep() == "(")
		{
			//function_declaration_token.append(temp_token->getPrev());
			//Checks for keyword after left parenthesis
			for (int i = 0; i < ensc251::numElement_tableOfKeywords; i++)
			{
				if (temp_token->getNext()->getStringRep() == ensc251::tableOfKeywords[i])
				{
					//Adds tokens to the list until it finds the end of the statement;
					while (temp_token->getStringRep() != ";")
					{
						function_declaration_token.append(temp_token->getStringRep());
						temp_token = temp_token->getNext();
						//When semicolon is found, append it to the list and the loop is over
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
	cout << numFunctionDeclarations << endl;
	return (function_declaration_token.getFirst());
}//*/

//Checks for the order of parenthesis and see if they match
//Checks for number of right parenthesis and left parenthesis and see if they match
//Return 0 if everything matches
//else output error message and tokenlist
Token* checkUnmatchedBrace(TokenList &tokenList)
{
	TokenList brace_token;
	Token *temp_token = tokenList.getFirst();
	//Counter for each brace
	int right_braces = 0;
	int left_braces = 0;
	//Checks the tokenlist for matching parenthesis
	while (temp_token)
	{
		bool matchedBraces = false;
		//Checking for left parenthesis
		if (temp_token->getStringRep() == "(")
		{
			//Checks for right parenthesis
			while (matchedBraces == false)
			{
				brace_token.append(temp_token->getStringRep());
				//Found right parenthesis
				if (temp_token->getNext()->getStringRep() == ")")
				{
					brace_token.append(temp_token->getNext()->getStringRep());
					//temp_token = temp_token->getNext();
					//cout << "\n" << "found" << endl;
					matchedBraces = true;
				}
				//Increment to next token
				temp_token = temp_token->getNext();
				//End of list, matching parenthesis not found
				if (temp_token->getNext() == NULL)
				{
					cout << "\n" << "Error: Unmatched braces" << endl;
					return brace_token.getFirst();
				}
			}
		}
		else
		{
			brace_token.append(temp_token->getStringRep());
		}
		// Next token 
		temp_token = temp_token->getNext();
	}
	//Proceeds to check for the number of braces
	if (temp_token == NULL)
	{
		TokenList brace_token1;
		Token *temp_token = tokenList.getFirst();
		while (temp_token->getNext() != NULL)
		{
			bool rightNumber = false;

			while (rightNumber == false)
			{
				brace_token1.append(temp_token->getStringRep());
				if (temp_token->getStringRep() == "(")
				{
					left_braces++;
				}
				if (temp_token->getStringRep() == ")")
				{
					right_braces++;
				}
				//End of the list
				if (temp_token->getNext() == NULL)
				{
					//Number of braces matches
					if (left_braces == right_braces)
					{
						rightNumber = true;
						return 0;
					}
					else //if (left_braces != right_braces)
					{
						cout << "Error: Unmatched braces" << endl;
						return brace_token1.getFirst();
					}
				}
				// Next token 
				temp_token = temp_token->getNext();
			}
			// Next token 
			temp_token = temp_token->getNext();
		}
	}
	return brace_token.getFirst();;
}//End of checkUnmatchedBraces

//Checks for matching types 
//Goes through a list of tokens and looks for an identifier
//If there is an identifier and the previous token is a keyword of a type, 
//then apply the keyword type to the identifier
//Compares the identifierValue of the identifier with the identifierValue of the token after the assignment operator
//Output an error message and list of error if types don't match else return 0
//Currently works for bool, int, float and string
Token* checkUnmatchedTypes(TokenList &tokenList)
{

	TokenList matchedTypes_Tokens;
	Token *temp_Token = tokenList.getFirst();
	while (temp_Token->getStringRep() != ";")
	{
		for (int i = 0; i < numElement_tableOfIDtype; i++)
		{
			//Looks for keyword types
			if (temp_Token->getStringRep() == tableOfIDtypes[i])
			{
				matchedTypes_Tokens.append(temp_Token->getStringRep());
				//Checks if the next token is an identifier
				if (temp_Token->getNext()->getStringClass() == T_Identifier)
				{
					//Assigns keyword type to identifier_value
					temp_Token->getNext()->setID_value(temp_Token->getID_value());
					matchedTypes_Tokens.append(temp_Token->getNext()->getStringRep());
					//Checks for assignment operator after the identifier
					temp_Token = temp_Token->getNext();
					if (temp_Token->getNext()->getStringRep() == "=")
					{
						matchedTypes_Tokens.append(temp_Token->getNext()->getStringRep());
						//Checks for if identifer value matches the string type of token
						if (temp_Token->getID_value() == temp_Token->getNext()->getNext()->getStringClass())
						{
							temp_Token = temp_Token->getNext();
							matchedTypes_Tokens.append(temp_Token->getNext()->getStringRep());
							matchedTypes_Tokens.append(temp_Token->getNext()->getNext()->getStringRep());
							return 0;
						}
						else
						{
							temp_Token = temp_Token->getNext();
							matchedTypes_Tokens.append(temp_Token->getNext()->getStringRep());
							matchedTypes_Tokens.append(temp_Token->getNext()->getNext()->getStringRep());
							cout << "Error: mismatch types" << endl;
							return matchedTypes_Tokens.getFirst();
						}
					}
				}
			}
		}
		temp_Token = temp_Token->getNext();
	}
	return 0;
}// End of checkUnmatchedTypes function

// Functions for categorizing tokens of identifiers
// Returns a list of identifiers
Token* categorizeIdentifiers(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringClass() == T_Identifier)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
} // end of categorizeIdentifiers

// Functions for categorizing tokens of operators
// Returns a list of operators
Token* categorizeOperator(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringClass() == T_Operator)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
} // end of categorizeOperators

// Function for categorizing tokens of punctuators
// Returns a list of a specific punctuator
Token* categorizePunctuator(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringClass() == T_Punctuator)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
} // end of Punctuator

// Function for categorizing tokens of keywords
// Returns a list of keywords
Token* categorizeKeyword(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringClass() == T_Keyword)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
} // end of categorize Keyword

// Function for categorizing tokens of boolean
// Returns a list of boolean
Token* categorizeBoolean(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringClass() == T_Boolean)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
} // end of categorizeBoolean

// Function for categorizing tokens of Integers
// Returns a list of integers
Token* categorizeInteger(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringClass() == T_IntegerLiteral)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
} // end of categorizeInteger

// Function for categorizing tokens of floats
// Returns a list of floats
Token* categorizeFloat(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringClass() == T_FloatLiteral)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
} // end of categorizeFloat

// Function for categorizing tokens of strings
// Returns a list of strings
Token* categorizeString(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringClass() == T_StringLiteral)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
} // end of categorizeString

// Function for categorizing tokens of unknown types
// Returns a list of unknown types
Token* categorizeUnknown(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringClass() == T_Unknown)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
} // end of categorizeUnknown

//Functions for printing token values in tokenlists

// Input: List of tokens
// Output: Print to screen the assignment tokens
void printAssignment(TokenList &tokenList)
{
	Token *aListPtr1 = getAssignmentStatements(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
} // end of printAssignment

// Input: List of tokens
// Output: Print to screen the brace errors
void printBraceError(TokenList &tokenList)
{
	Token *aListPtr1 = checkUnmatchedBrace(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
} // end of printBraceError

// Input: List of tokens
// Output: Print to screen the type error tokens
void printTypeError(TokenList &tokenList)
{
	Token *aListPtr1 = checkUnmatchedTypes(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
} // end of printTypeError

// Input: List of tokens
// Output: Print to screen the identifier tokens
void printIdentifiers(TokenList &tokenList)
{
	Token *aListPtr1 = categorizeIdentifiers(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
} // end of printIdentifiers

// Input: List of tokens
// Output: Print to screen the operator tokens
void printOperators(TokenList &tokenList)
{
	Token *aListPtr1 = categorizeOperator(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
}

// Input: List of tokens
// Output: Print to screen the punctuator tokens
void printPunctuators(TokenList &tokenList)
{
	Token *aListPtr1 = categorizePunctuator(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
} // end of printPunctuators

// Input: List of tokens
// Output: Print to screen the keyword tokens
void printKeywords(TokenList &tokenList)
{
	Token *aListPtr1 = categorizeKeyword(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
} // end of printKeywords

// Input: List of tokens
// Output: Print to screen the boolean tokens
void printBoolean(TokenList &tokenList)
{
	Token *aListPtr1 = categorizeBoolean(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
} // end of printBoolean

// Input: List of tokens
// Output: Print to screen the integer tokens
void printIntegers(TokenList &tokenList)
{
	Token *aListPtr1 = categorizeInteger(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
} // end of printIntegers

// Input: List of tokens
// Output: Print to screen the float tokens
void printFloats(TokenList &tokenList)
{
	Token *aListPtr1 = categorizeFloat(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
} // end of printFloats

// Input: List of tokens
// Output: Print to screen the string tokens
void printStrings(TokenList &tokenList)
{
	Token *aListPtr1 = categorizeString(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
} // end of printStrings

// Input: List of tokens
// Output: Print to screen the unknown tokens
void printUnknowns(TokenList &tokenList)
{
	Token *aListPtr1 = categorizeUnknown(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
} // end of printUnknowns

// Prints tokens types in non verbose mode
// Gives the total number of tokens in a token type 
void printTokensTypes_NV(TokenList &tokenList)
{
	cout << "\n" << "Number of identifiers: ";
	categorizeIdentifiers(tokenList);
	cout << "Number of operators: ";
	categorizeOperator(tokenList);
	cout << "Number of punctuators: ";
	categorizePunctuator(tokenList);
	cout << "Number of keywords: ";
	categorizeKeyword(tokenList);
	cout << "Number of booleans: ";
	categorizeBoolean(tokenList);
	cout << "Number of integers: ";
	categorizeInteger(tokenList);
	cout << "Number of floats: ";
	categorizeFloat(tokenList);
	cout << "Number of strings: ";
	categorizeString(tokenList);
	cout << "Number of unknowns; ";
	categorizeUnknown(tokenList);
} // end of printTokensType_NV

// Prints tokens types in verbose mode
// Gives the total number of tokens in a token type  and prints tokens that belong to this category
void printTokensTypes_V(TokenList &tokenList)
{
	cout << "\n" << "Number of identifiers: ";
	printIdentifiers(tokenList);
	cout << "\n" << "Number of operators: ";
	printOperators(tokenList);
	cout << "\n" << "Number of punctuators: ";
	printPunctuators(tokenList);
	cout << "\n" << "Number of keywords: ";
	printKeywords(tokenList);
	cout << "\n" << "Number of booleans: ";
	printBoolean(tokenList);
	cout << "\n" << "Number of integers: ";
	printIntegers(tokenList);
	cout << "\n" << "Number of floats: ";
	printFloats(tokenList);
	cout << "\n" << "Number of strings: ";
	printStrings(tokenList);
	cout << "\n" << "Number of unknowns; ";
	printUnknowns(tokenList);
	cout << "\n";
} // end of printTokensType_V

void print_nonverbose(TokenList &tokenList)
{
	cout << "\n" << "Number of assignment statements: ";
	getAssignmentStatements(tokenList);
	printBraceError(tokenList);
	printTypeError(tokenList);
	cout << "\n" << "Number of function declarations: ";
	getFunctionDeclarations(tokenList);
	printTokensTypes_NV(tokenList);
} // end of print_nonverbose

void print_verbose(TokenList &tokenList)
{
	cout << "\n" << "Number of assignment statements: ";
	getAssignmentStatements(tokenList);
	printBraceError(tokenList);
	printTypeError(tokenList);
	cout << "\n" << "Number of function declarations: ";
	getFunctionDeclarations(tokenList);
	printTokensTypes_V(tokenList);
} // end of print_verbose

//End of print functions

//Example Test code for interacting with your Token, TokenList, and Tokenizer classes
//Add your own code to further test the operation of your Token, TokenList, and Tokenizer classes
void main()
{
	// Declaration of variables and classes
	ifstream sourceFile;
	TokenList tokens;
	Tokenizer tokenizer;
	Clippy clippy;
	unsigned int total_tokens = 0;
	unsigned int choice = 0;

	//Read in a file line-by-line and tokenize each line

	sourceFile.open("test.cpp");
	if (!sourceFile.is_open())
	{
		cerr << "Failed to open file" << endl;
		exit(1);
	}

	while (!sourceFile.eof())
	{
		string lineA, lineB;

		getline(sourceFile, lineA);

		//while the current line ends with a line-continuation \ append the next line to the current line
		while (lineA[lineA.length() - 1] == '\\')
		{
			lineA.erase(lineA.length() - 1, 1);
			getline(sourceFile, lineB);
			lineA += lineB;
		}

		tokenizer.setString(&lineA);
		while (!tokenizer.isComplete())
		{
			tokens.append(tokenizer.getNextToken());
			total_tokens = total_tokens++;
		}
		//Re-insert newline that was removed by the getline function
		tokens.append("\n");
	}

	removeInlineComments(tokens);
	removeBlockComments(tokens);

	/*Test your tokenization of the file by traversing the tokens list and printing out the tokens and the tokens type*/
	Token *t = tokens.getFirst();

	//Input choice for verbose or non-verbose statistic or exit 
	while (1)
	{
		cout << "\n""**************** Parser ****************\n\n";
		cout << "Choices Are :-\n=> [1] For Non-Verbose mode \n=> [2] For Verbose mode\n=> [3] For Traverse\n=> [4] For Exit";
		cout << "\n\nEnter Your choice : ";
		cin >> choice;

		//Options for parser
		switch (choice)
		{
		case 1:
			//Print non-verbose mode statistics
			print_nonverbose(tokens);
			//getAssignmentStatements(tokens);
			//getFunctionDeclarations(tokens);
			cout << "\n" << "Total number of tokens: " << total_tokens << endl;
			break;
		case 2:
			//Print verbose mode statistics
			print_verbose(tokens);
			cout << "Total number of tokens: " << total_tokens << endl;
			break;
		case 3:
			//Traverses through the token list and prints out tokens and token types
			while (t)
			{
				cout << t->getStringRep() << " ";
				t = t->getNext();
			}
			t = tokens.getFirst();

			while (t) 
			{
				cout << t->getStringType() << " ";
				t = t->getNext();
			}
			t = tokens.getFirst();
			cout << "\n";
			break;
		case 4:
			//Exits the program
			sourceFile.close();
			exit(0);
		}
	} // end of while loop
}
