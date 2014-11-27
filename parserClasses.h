#ifndef PARSERCLASSES_H_
#define PARSERCLASSES_H_
/*
All code written by :
Jason Liu 301224956
Daryl Seah 301222124

Modified by:
Choong Jin Ng 301226977
Steven Luu    301150253
*/

// Last edited: 25 Nov 2014, 9.34pm

//Use only the following libraries:
#include <string>
#include <iostream>
#include "lexemesTypes.h"

using namespace std;
using namespace ensc251;

//Declare your variables for storing delimiters here:

//typedef for custom data type defined in header file "lexemesTypes.h"
typedef ensc251::LexemeType TokenClass;

//Token class for a doubly-linked list of string tokens
class Token

{
private:
	Token *next; //Next pointer for doubly linked list
	Token *prev; //Previous pointer for doubly linked list
	string stringRep; //Token value
    TokenClass stringClass; //Token class (to which class this token belongs to, for e.g. identifier, keywords...etc)
	string stringType; // Under class, what type of string is it (e.g int, bool, class, union)
    TokenClass identifier_value; //type of identifier --- Jin: StringType is suppose to do this. Also, we may have to check for class, unions and structures
	//Allow TokenList class to access Token member variables marked private
	friend class TokenList;

public:
	//Default Constructor, pointers initialized to NULL
	Token() : next(NULL), prev(NULL) { }

	//Constructor with string initialization, pointers initialized to NULL
	Token(const string &stringRep) : next(NULL), prev(NULL), stringRep(stringRep) { }

	//Returns the Token's *next member
	Token* getNext ( ) const
	{
		return next;
	}

	//Sets the Token's *next member
	void setNext(Token* next)
	{
		this->next = next;
	}

	//Returns the Token's *prev member
	Token* getPrev ( ) const
	{
		return prev;
	}

	//Sets the Token's *prev member
	void setPrev (Token* prev )
	{
		this->prev = prev;
	}

	//Returns a reference to the Token's stringRep member variable
	const string& getStringRep ( ) const
	{
		return stringRep;
	}

	//Sets the token's stringRep variable
	void setStringRep (const string& stringRep )
	{
		this->stringRep = stringRep;
	}

	//Returns a reference to the Token's stringClass member variable
	const TokenClass getStringClass ( ) const
	{
		return stringClass;
	}

	//Sets the token's stringClass variable
	void setStringClass (const TokenClass& stringClass)
	{
		this->stringClass = stringClass;
	}

	// Returns a reference to the Token's stringType member variable
	const string getStringType() const
	{
		return stringType;
	}

	// Sets the token's stringType variable
	void setStringType(const string& stringType)
	{
		this->stringType = stringType;
	}
	//Return the Token's identifier value
	const TokenClass getID_value()const
	{
		return identifier_value;
	}

	//Sets the Token's identifier value
	void setID_value(const TokenClass& ID_value)
	{
		this->identifier_value = ID_value;
	}
};

//A doubly-linked list class consisting of Token elements
class TokenList 
{
private:
	Token *head; //Points to the head of the token list (doubly linked)
	Token *tail; //Points to the tail of the function list (doubly linked)

public:
	//Default Constructor, Empty list with pointers initialized to NULL
	TokenList() : head(NULL), tail(NULL) { }

	//Returns a pointer to the head of the list
	Token* getFirst() const
	{
		return head;
	}

	//Returns a pointer to the tail of the list
	Token* getLast() const
	{
		return tail;
	}

	//Creates a new token for the string input, str
	//Appends this new token to the TokenList
	//On return from the function, it will be the last token in the list
	void append(const string &str); //example comment

	//Appends the token to the TokenList if not null
	//On return from the function, it will be the last token in the list
	void append(Token *token);

    //Removes the token from the linked list if it is not null
	//Deletes the token
	//On return from function, head, tail and the prev and next Tokens (in relation to the provided token) may be modified.
	void deleteToken(Token *token);

	//Input: a pointer to a token
	//Output: it won't return anything, but within function, it should set the token class (i.e. token->stringClass)
	//Note: one can invoke this function before adding token to the token list
	void setTokenClass(Token *token);

	//Input: a pointer to a token
	//Output: it won't return anything, but within function, it should set the token class (i.e. token->stringClass)
	//NOTE: DOES NOT DO ANYTHING RIGHT NOW
	void setTokenType(Token *token);
	
	//If the token is an identifier, its value is set to a type
	void setIdentifierValue(Token *token);
};

//A class for tokenizing a string of C++ code into tokens
class Tokenizer 
{
private:
	/*State tracking variables for processing a single string*/
	bool processingInlineComment; //True if processing an In-line comment //
	bool processingBlockComment;  //True if processing a Block Comment /* */
	bool processingIncludeStatement; //True if processing an include statement <> ""
	bool processingFloat; //True if processing a number
	bool complete; //True if finished processing the current string

	size_t offset; //Current position in string
	size_t tokenLength; //Current token length
	string *str; //A pointer to the current string being processed

	//Include any helper functions here
	//e.g. trimming whitespace, comment processing
	void trimwhitespace() 
	{
		if (offset == str->length())
		{
			complete = true;
			return;
		}
		
		while ((str->at(offset) == ' ' || str->at(offset) == '\t' || str->at(offset) == '\v') && offset < str->length())
		{
			offset++;
			if (offset == str->length())
			{
				complete = true;
				return;
			}
		}
	} // end of trimwhitespace

	bool isnumber(const char d)
	{
		if (d > 47 && d < 58) //uses ascii values
		{
			return true;
		}
		return false;
	} // end of isnumber

	//Computes a new tokenLength for the next token
	//Modifies: size_t tokenLength, and bool complete
	//(Optionally): may modify offset
	//Does NOT modify any other member variable of Tokenizer
	void prepareNextToken();

public:
	//Default Constructor- YOU need to add the member variable initializers.
	Tokenizer() : processingInlineComment(false), processingBlockComment(false), processingIncludeStatement(false)
		,processingFloat(false), complete(false)
	{
		str = NULL;
		offset = 0;
		tokenLength = 0;
	}

	//Sets the current string to be tokenized
	//Resets all Tokenizer state variables
	//Calls Tokenizer::prepareNextToken() as the last statement before returning.
	void setString(string *str);

	//Returns true if all possible tokens have been extracted from the current string (string *str)
	bool isComplete() const
	{
		return complete;
	}

	//Returns the next token. Hint: consider the substr function
	//Updates the tokenizer state
	//Updates offset, resets tokenLength, updates processingABC member variables
	//Calls Tokenizer::prepareNextToken() as the last statement before returning.
	string getNextToken();
};

// A class for analyzing and error checking C++ tokens
class Clippy
{
	friend class TokenList;
	friend class Token;
private:
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

				for (int i = 0; i < ensc251::numElement_identifierWords; i++)
				{
					if (temp_token->getPrev()->getPrev()->getStringRep() == ensc251::identifierWords[i])
					{
						temp_token = temp_token->getPrev();
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
	} // end of getFunctionDeclarations

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
		using namespace ensc251;

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

	// Function for categorizing tokens of libraries
	// Returns a list of libraries
	Token* categorizeLibraries(TokenList &tokenList)
	{
		TokenList sortTokens;
		Token *temp_Token = tokenList.getFirst();
		int numOfTokens = 0;
		while (temp_Token)
		{
			if (temp_Token->getStringClass() == T_Library)
			{
				sortTokens.append(temp_Token->getStringRep());
				numOfTokens++;
			}
			temp_Token = temp_Token->getNext();
		}
		cout << numOfTokens << endl;
		return sortTokens.getFirst();
	} // end of categorizeLibraries

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

	void printLibraries(TokenList &tokenList)
	{
		Token *aListPtr1 = categorizeLibraries(tokenList);
		while (aListPtr1)
		{
			cout << aListPtr1->getStringRep() << " ";
			aListPtr1 = aListPtr1->getNext();
		}
	} // end of printLibraries

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
		cout << "Number of libraries: ";
		categorizeLibraries(tokenList);
		cout << "Number of unknowns: ";
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
		cout << "\n" << "Number of libraries: ";
		printLibraries(tokenList);
		cout << "\n" << "Number of unknowns; ";
		printUnknowns(tokenList);
		cout << "\n";
	} // end of printTokensType_V

public:
	// Defualy constructor
	Clippy()
	{

	}

	void print_nonverbose(TokenList &tokenList);
	void print_verbose(TokenList &tokenList);
};

#endif /* PARSERCLASSES_H_ */
