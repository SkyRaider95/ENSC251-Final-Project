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
				}
			}
			
		}
		
		// Next token 
		temp_token = temp_token->getNext();

	}

	// Return token list;
	return (assignment_token.getFirst());
} // end of getAssignmentStatements

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
					cout << "\n" << "Error: Unmatched braces";
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
	}//*/
	
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
}//End of unmatchedBraces

//Functions for categorizing tokens of a type
//Returns a list of a specific stringType
Token* categorizeIdentifiers(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringType() == T_Identifier)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
}
Token* categorizeOperator(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringType() == T_Operator)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
}

Token* categorizePunctuator(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringType() == T_Punctuator)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
}

Token* categorizeKeyword(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringType() == T_Keyword)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
}

Token* categorizeBoolean(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringType() == T_Boolean)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
}

Token* categorizeInteger(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringType() == T_IntegerLiteral)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
}

Token* categorizeFloat(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringType() == T_FloatLiteral)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
}

Token* categorizeString(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringType() == T_StringLiteral)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
}

Token* categorizeUnknown(TokenList &tokenList)
{
	TokenList sortTokens;
	Token *temp_Token = tokenList.getFirst();
	int numOfTokens = 0;
	while (temp_Token)
	{
		if (temp_Token->getStringType() == T_Unknown)
		{
			sortTokens.append(temp_Token->getStringRep());
			numOfTokens++;
		}
		temp_Token = temp_Token->getNext();
	}
	cout << numOfTokens << endl;
	return sortTokens.getFirst();
}

//Functions for printing token values in tokenlists
void printAssignment(TokenList &tokenList)
{
	Token *aListPtr1 = getAssignmentStatements(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
}//*/

void printError(TokenList &tokenList)
{
	Token *aListPtr1 = checkUnmatchedBrace(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
}//*/

void printIdentifiers(TokenList &tokenList)
{
	Token *aListPtr1 = categorizeIdentifiers(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
}//*/

void printOperators(TokenList &tokenList)
{
	Token *aListPtr1 = categorizeOperator(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
}

void printPunctuators(TokenList &tokenList)
{
	Token *aListPtr1 = categorizePunctuator(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
}
void printKeywords(TokenList &tokenList)
{
	Token *aListPtr1 = categorizeKeyword(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
}
void printBoolean(TokenList &tokenList)
{
	Token *aListPtr1 = categorizeBoolean(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
}
void printIntegers(TokenList &tokenList)
{
	Token *aListPtr1 = categorizeInteger(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
}
void printFloats(TokenList &tokenList)
{
	Token *aListPtr1 = categorizeFloat(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
}
void printStrings(TokenList &tokenList)
{
	Token *aListPtr1 = categorizeString(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
}
void printUnknowns(TokenList &tokenList)
{
	Token *aListPtr1 = categorizeUnknown(tokenList);
	while (aListPtr1)
	{
		cout << aListPtr1->getStringRep() << " ";
		aListPtr1 = aListPtr1->getNext();
	}
}

//Prints tokens types in non verbose mode
//Gives the total number of tokens in a token type 
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
}

//Prints tokens types in verbose mode
//Gives the total number of tokens in a token type  and prints tokens that belong to this category
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
}
//Functions that print out the statistics of the input file
//Gives different data depending on non verbose or verbose mode 
void print_nonverbose(TokenList &tokenList)
{
	cout << "\n" << "Number of assignment statements: " ;
	getAssignmentStatements(tokenList);
	printError(tokenList);
	cout << "\n" << "Number of function declarations: " ; 
	getFunctionDeclarations(tokenList);
	printTokensTypes_NV(tokenList);
}

void print_verbose(TokenList &tokenList)
{
	cout << "\n" << "Number of assignment statements: " ;
	getAssignmentStatements(tokenList);
	printError(tokenList);
	cout << "\n" << "Number of function declarations: " ;
	getFunctionDeclarations(tokenList);
	printTokensTypes_V(tokenList);
}


//Example Test code for interacting with your Token, TokenList, and Tokenizer classes
//Add your own code to further test the operation of your Token, TokenList, and Tokenizer classes
int main()
{
	ifstream sourceFile;
	TokenList tokens;
	Tokenizer tokenizer;
	Clippy clippy;

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
		}
		//Re-insert newline that was removed by the getline function
		tokens.append("\n");
	}

	removeInlineComments(tokens);
	removeBlockComments(tokens);

	/*Test your tokenization of the file by traversing the tokens list and printing out the tokens and the tokens type*/
	Token *t = tokens.getFirst();
	//Input choice for verbose or non-verbose statistic or exit 
	//Prompts user for input depending on what the user wants
	//The program repeats until the user enters the choice to terminate
	int choice = 0;
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
			while (t) {
				cout << t->getStringRep() << " ";
				t = t->getNext();
			}
			t = tokens.getFirst();
			while (t) {
				cout << t->getStringType() << " ";
				t = t->getNext();
			}
			t = tokens.getFirst();
			cout << "\n";
			break;
		case 4:
			//Exits the program
			exit(0);
		}
	}
	/*while (t)
	{
		cout << t->getStringRep() << " ";
		t = t->getNext();
	}

	cout << endl;

	t = tokens.getFirst();

	while (t)
	{
		cout << t->getStringClass() << " ";
		t = t->getNext();
	}
	cout << endl;

	// Error and Analysis
	clippy.errorAssistant(tokens);
	*/
	return 0;
}
