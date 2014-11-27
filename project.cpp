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
	while (t)
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
	return 0;
}
