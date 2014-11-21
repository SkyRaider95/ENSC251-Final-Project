/*

Created by:
Choong Jin Ng 301226977
Steven Luu    301150253

*/


//Use only the following three libraries:
#include "parserClasses.h"
#include "advancedParserClasses.h"
#include <iostream>
#include <fstream>

using namespace std;

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
	bool deleted = false;
	Token* temp, *target;
	temp = tokenList.getFirst();
	while (temp)
	{
		deleted = false;
		if (temp->getStringRep() == "/*")
		{
			counter++;
			while (!deleted)
			{
				target = temp;
				temp = temp->getNext();
				tokenList.deleteToken(target);
				if (temp->getStringRep() == "*/")
				{
					target = temp;
					temp = temp->getNext();
					deleted = true;
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
/*Token* getAssignmentStatements(TokenList &tokenList)
{
	// Creation of Assignment statements
	TokenList assignment_token;
	Token *temp_token = tokenList.getFirst();
	string temp_string;

	while (temp_token)
	{
		// Place the token values into the temp_string
		temp_string = temp_string + temp_token->getStringRep();

		// Library Declaration
		if (temp_token->getStringRep() == "#")
		{
			while (true)
			{

			}
		}

		// These if-elseif functions should be be run like an array or something
		else if (temp_token->getStringRep() == "if")
		{

		}

		
		Special cases are:
		#include
		if and else-if statements
		while
		functions
		class
		namespace
		


		// End of assignment statement. Place the assignment into assignment_token and clears the string
		else if (temp_token->getStringRep() == ";")
		{
			assignment_token.append(temp_string);
			temp_string.clear();
		}

		// Next string
		temp_token = temp_token->getNext();
	}

	//return NULL;
	return (assignment_token.getFirst());
}// end of getAssignmentStatements
*/

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
			while(temp_token->getStringRep() != ";")
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
}

//Example Test code for interacting with your Token, TokenList, and Tokenizer classes
//Add your own code to further test the operation of your Token, TokenList, and Tokenizer classes
int main()
{
	ifstream sourceFile;
	TokenList tokens;
	Tokenizer tokenizer;

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

	t = tokens.getFirst();

	while (t)
	{
		cout << t->getStringType() << " ";
		t = t->getNext();
	}

	//Test your assignment statements
	Token *aListPtr = getAssignmentStatements(tokens);

	cout << endl;

	while (aListPtr)
	{
		cout << aListPtr->getStringRep() << " ";
		aListPtr = aListPtr->getNext();
	}
	return 0;
}
