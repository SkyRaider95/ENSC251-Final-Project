/*
Created by:
Choong Jin Ng 301226977
Steven Luu    301150253
*/

//Using the following libraries:
#include "parserClasses.h"
#include <iostream>
#include <fstream>
#include <cctype> 

using namespace std;
using namespace ensc251;

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
} // end of removeBlockComments

//Example Test code for interacting with your Token, TokenList, and Tokenizer classes
//Add your own code to further test the operation of your Token, TokenList, and Tokenizer classes
void main()
{
	// Declaration of objects

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

		// String is not empty
		if (!(lineA.empty()))
		{
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
			clippy.print_nonverbose(tokens);
			cout << "\n" << "Total number of tokens: " << total_tokens << endl;
			break;
		case 2:
			//Print verbose mode statistics
			clippy.print_verbose(tokens);
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
} // end of main function