//Use only the following libraries:
#include "parserClasses.h"
#include <string>

/*
Original code written by :
Jason Liu 301224956
Daryl Seah 301222124

Modified and optimized by:
Choong Jin Ng 301226977
Steven Luu    301150253
*/

// Last edited: 25 Nov 2014, 9.34pm

//****TokenList class function definitions******

//Creates a new token for the string input, str
//Appends this new token to the TokenList
//On return from the function, it will be the last token in the list
void TokenList::append(const string &str)
{
	// If the string is empty
	if (str.empty())
	{
		return;
	}

	// Otherwise
	else
	{
		Token *d = new Token(str);
		setTokenClass(d);
		this->append(d);
	}
}

//Appends the token to the TokenList if not null
//On return from the function, it will be the last token in the list
void TokenList::append(Token *token)
{
	if (token)
	{
		token->setPrev(getLast());
		token->setNext(NULL);
		if (tail) //if tail is not null, then there is at least one element in the list
		{
			tail->setNext(token); //sets current final to point to the new one
		}
		else
		{
			head = token; //if tail is null, that means head is also null. head needs to point to token
		}
		tail = token; //at the end, tail has to point to the newly appended token.
	}
}

//Removes the token from the linked list if it is not null
//Deletes the token
//On return from function, head, tail and the prev and next Tokens (in relation to the provided token) may be modified.
void TokenList::deleteToken(Token *token)
{
	if (token)
	{
		if (token == head && token == tail)
		{
			head = NULL;
			tail = NULL;
		}
		else if (token == head)
		{
			token->next->prev = NULL;
			head = token->next;
		}
		else if (token == tail)
		{
			token->prev->next = NULL; //makes the previous one point to null
			tail = token->prev; //moves tail to the previous one
		}
		else
		{
			token->next->prev = token->prev; //makes the next one point behind it
			token->prev->next = token->next; //makes the previous one point ahead of it
		}
		delete token; //unless token was null, token will be deleted in the end.
	}
}

//Input: a pointer to a token
//Output: it won't return anything, but within function, it should set the token class (i.e. token->stringClass)
//Note: one can invoke this function before adding token to the token list
void TokenList::setTokenClass(Token *token) 
{
	using namespace ensc251;

	if (token)
	{
		for (int i = 0; i != token->stringRep.length(); i++)
		{
			if (isKeyword(token->stringRep) == true)
			{
				token->stringClass = T_Keyword;
			}
			else if (isOperator(token->stringRep) == true)
			{
				token->stringClass= T_Operator;
			}
			else if (isBooleanValue(token->stringRep) == true)
			{
				token->stringClass = T_Boolean;
			}
			else if (isPunctuator(token->stringRep.at(i)) == true)
			{
				token->stringClass = T_Punctuator;
			}
			else if (isIdentifier(token->stringRep) == true)
			{
				token->stringClass = T_Identifier;
			}
			else if (isStringLiteral(token->stringRep) == true)
			{
				token->stringClass = T_StringLiteral;
			}

			// Only numbers can enter this
			else if (isDigitLiteral(token->stringRep) == true)
			{
				// Is it a float
				if (isFloatLiteral(token->stringRep) == true)
				{
					token->stringClass = T_FloatLiteral;
				}

				// Is it a integer
				else if (isIntegerLiteral(token->stringRep) == true)
				{
					token->stringClass = T_IntegerLiteral;
				}

				else
				{
					token->stringClass = T_Unknown;
				}
			}

			else if (isLibraryLiteral(token->stringRep) == true)
			{
				token->stringClass = T_Library;
			}

			else
			{
				token->stringClass = T_Unknown;
			}
		}
	}
	return;
}

//Sets identifier_Value for a token depending on strings in a table
//Used so another function can match an identifier with this value
void TokenList::setIdentifierValue(Token *token)
{
	using namespace ensc251;
	if (token->stringRep == tableOfIDtypes[0])
	{
		token->identifier_value = T_Boolean;
	}
	else if (token->stringRep == tableOfIDtypes[1])
	{
		token->identifier_value = T_IntegerLiteral;
	}
	else if (token->stringRep == tableOfIDtypes[2])
	{
		token->identifier_value = T_FloatLiteral;
	}
	else if (token->stringRep == tableOfIDtypes[3])
	{
		token->identifier_value = T_StringLiteral;
	}
	else
	{
		token->identifier_value = T_Unknown;
	}
	return;
} // end of setIdentifierValue

//Input: a pointer to a token
//Output: it won't return anything, but within function, it should set the token type (i.e. token->setStringType(string))
//NOTE: DOES NOT DO ANYTHING RIGHT NOW
void setTokenType(Token *token)
{
	using namespace ensc251;

	if (token)
	{
	}
} // end of setTokenType

//****Tokenizer class function definitions******

//Computes a new tokenLength for the next token
//Modifies: size_t tokenLength, and bool complete
//(Optionally): may modify offset
//Does NOT modify any other member variable of Tokenizer
void Tokenizer::prepareNextToken()
{
	tokenLength = 0;
	size_t len = str->length();

	// Erase spaces
	if (!complete && !processingInlineComment && !processingBlockComment)
	{
		trimwhitespace();
	}

	//if the character is the end of the line
	if (offset == len)
	{
		complete = true;
		return;
	}

	//if complete is true for some reason
	if (complete)
	{
		return;
	}

	//if the first character of the token is a number,
	if (isnumber((char) str->at(offset)))
	{
		processingFloat = true;
	}
	
	else if (str->at(offset) == '.')
	{
		if (!(offset + 1 == len)) {
			if (isnumber((char) str->at(offset + 1)))
			{
				processingFloat = true;
			}
		}
	}

	// Found an inline comment
	if (processingInlineComment)
	{
		while (offset < len)
		{
			offset++;
			tokenLength++;

			if (offset == len)
			{
				complete = true;
				break;
			}
		}

		return;
	}

	// Found a block comment
	else if (processingBlockComment)
	{ 
		if (offset == len)
		{
			complete = true;
			return;
		}

		//if the next characters are */, stop the block comment. token is length 2.
		if (str->at(offset) == '*')
		{
			//if the line ends in a *, add it to the current token.
			if (offset + 1 == len) 
			{
				offset++;
				tokenLength++;
				complete = true;
				return;
			}

			else if (str->at(offset + 1) == '/')
			{
				offset += 2;
				tokenLength = 2;
				return;
			}
		}

		//otherwise, continue adding characters to the token until */ is found. after that, stop adding characters.
		else
		{
			while (true)
			{
				//no * found, just keep reading.
				if (str->at(offset) != '*')
				{
					offset++;
					tokenLength++;

					//if the character is the end of the line
					if (offset == len)
					{
						complete = true;
						break;
					}
				}
				//note that processingBlockComment is never set to false, unless the end of the block comment is found.
				
				//if there is a *
				else
				{
					//if it's the last character in the line, just add it to the current token and return.
					if (offset + 1 == len)
					{
						offset++;
						tokenLength++;
						complete = true;
						break;
					}

					//if it isn't the last character,
					else 
					{
						//if the next is a /, the */ condition wil execute in the top-level if.
						if (str->at(offset + 1) == '/')
						{
							//ignore the * and the /, and everything before it was the block comment.
							break;
						}

						//otherwise, you just add it to the token. It won't be the end of the line.
						else
						{
							offset++;
							tokenLength++;
						}
					}
				}
			}
			return;
		}
	}

	//this probably can be refactored too
	else if (processingFloat)
	{
		while (isnumber((char) str->at(offset)) || str->at(offset) == 'e' || str->at(offset) == '.' || str->at(offset) == 'f' ||
			str->at(offset) == 'F' || str->at(offset) == 'l' || str->at(offset) == 'L' || str->at(offset) == 'U' || str->at(offset) == 'E')
		{
			if ((str->at(offset) == 'e' || str->at(offset) == 'E') && (str->at(offset + 1) == '-' || str->at(offset + 1) == '+'))
			{
				offset++;
				tokenLength++;
				if (offset == len)
				{
					complete = true;
					break;
				}
			}

			offset++;
			tokenLength++;
			if (offset == len)
			{
				complete = true;
				return;
			}
		}

		//switch to hexadecimal processing
		if (str->at(offset) == 'x')
		{
			offset++;
			tokenLength++;
			if (offset == len)
			{
				complete = true;
				return;
			}

			while (isnumber((char) str->at(offset)) || str->at(offset) == 'A' || str->at(offset) == 'B' || str->at(offset) == 'C' ||
				str->at(offset) == 'D' || str->at(offset) == 'E' || str->at(offset) == 'F' || str->at(offset) == 'L' ||
				str->at(offset) == 'l' || str->at(offset) == 'U')
			{
				offset++;
				tokenLength++;
				if (offset == len)
				{
					complete = true;
					break;
				}
			}
		}

		processingFloat = false;
		return;
	}

	//this is convoluted, could probably be refactored
	//if include statement, if we don't see a <, ", ', we have to trim whitespace until we see a
	//<,",', or get the entire word "include" or "ifndef" as a token.
	else if (processingIncludeStatement)
	{
		if (str->at(offset) != '<' && str->at(offset) != '"')
		{
			//gets the word "include"
			while (str->at(offset) != ' ' && str->at(offset) != '\t' && str->at(offset) != '<' && str->at(offset) != '"')
			{
				offset++;
				tokenLength++;
				if (offset == len)
				{
					complete = true;
					return;
				}
			}
		}

		else
		{
			offset++;
			tokenLength++;
			while (str->at(offset) != '>' && str->at(offset) != '"')
			{
				offset++; //gets <ctime> or "parserClasses.h" or whatever.
				tokenLength++;
				if (offset == len) {
					complete = true;
					return;
				}
			}
			offset++;
			tokenLength++; //gets the > at the end.

			if (offset == len)
			{
				complete = true;
			}
		}
		return;
	}

	//begin regular processing
	while (str->at(offset) != ' ' && str->at(offset) != '\t' && offset<len)
	{
		if (str->at(offset) == '"')
		{ //for string literals 
			tokenLength++;
			offset++;
			while (str->at(offset) != '"' && offset<len)
			{
				if (str->at(offset) == '\\')
				{ //if it sees one escape sequence, add two to offset and token length.
					tokenLength += 2;
					offset += 2;

					if (offset == len)
					{
						complete = true;
						break;
					}
					continue; //check again if it sees a " or ' after the escape sequence.
				}
				tokenLength++;
				offset++; //otherwise just move forward by one.

				if (offset == len)
				{
					complete = true;
					break;
				}
			} // end of while loop

			offset++; //includes the last " or the '
			tokenLength++;
			if (offset == len)
			{
				complete = true;
				break;
			}
			break;
		}

		//for string literals 
		else if (str->at(offset) == '\'')
		{ 
			tokenLength++;
			offset++;
			while (str->at(offset) != '\'' && offset<len)
			{
				//if it sees one escape sequence, add two to offset and token length.
				if (str->at(offset) == '\\')
				{ 
					tokenLength += 2;
					offset += 2;

					if (offset == len)
					{
						complete = true;
						break;
					}
					continue; //check again if it sees a " or ' after the escape sequence.
				}
				tokenLength++;
				offset++; //otherwise just move forward by one.
				if (offset == len)
				{
					complete = true;
					break;
				}
			}

			offset++; //includes the last " or the '
			tokenLength++;
			if (offset == len)
			{
				complete = true;
				break;
			}
			break;
		}

		//all operators which can be doubled onto themselves except for --
		//(::, &&, ||, ++, --, <<, >>, and also the <<= and >>= operators
		//and &=, |=, +=, -=, <=, >
		else if (str->at(offset) == '|' || str->at(offset) == '&' || str->at(offset) == '+' || str->at(offset) == '>' ||
			str->at(offset) == '<' || str->at(offset) == ':' || str->at(offset) == '=')
		{
			offset++;
			tokenLength++;
			if (offset == len)
			{
				complete = true;
				break;
			}

			if (str->at(offset) == str->at(offset - 1) || str->at(offset) == '=')
			{
				offset++;
				tokenLength++;
				if (offset == len)
				{
					complete = true;
					break;
				}
				if (str->at(offset) == '=')
				{
					offset++;
					tokenLength++;
				}
			}
			break;
		}

		else if (str->at(offset) == '*' || str->at(offset) == '%' || str->at(offset) == '!' || str->at(offset) == '~' ||
			str->at(offset) == '.' || str->at(offset) == ',' || str->at(offset) == ';' || str->at(offset) == '^' ||
			str->at(offset) == '?' || str->at(offset) == '#')
		{
			//list of all operators/specials that come alone/compound.
			if (str->at(offset) == '.')
			{
				offset++;
				tokenLength++;

				if (offset == len)
				{
					complete = true;
					break;
				}

				if (str->at(offset) == '*')
				{
					offset++;
					tokenLength++;
				}
			}
			else
			{
				offset++;
				tokenLength++;
				if (offset == len)
				{ //in case for some reason one of these characters is the end of a line
					complete = true;
					break;
				}

				if (str->at(offset) == '=' || str->at(offset) == ':')
				{
					//this contains all possible 2nd parts of any compound operators (can't put spaces between)
					//this assumes that syntax of the original file is actually correct (no one wrote something stupid like +&)
					offset++;
					tokenLength++;

					if (offset == len)
					{ //in case for some reason one of these characters is the end of a line
						complete = true;
						break;
					}

					if (str->at(offset) == '=')
					{
						//the only 3-
						offset++;
						tokenLength++;
					}
				}
			}
			break;
		}

		else if (str->at(offset) == '-')
		{
			offset++;
			tokenLength++;
			if (offset == len) {
				complete = true;
				break;
			}
			if (str->at(offset) == '-' || str->at(offset) == '=')
			{
				offset++;
				tokenLength++;
			}

			else if (str->at(offset) == '>')
			{
				offset++;
				tokenLength++;

				if (offset == len)
				{
					complete = true;
					break;
				}

				if (str->at(offset) == '*')
				{
					offset++;
					tokenLength++;
				}
				break;
			}
			break;
		}
		
		// slash is special
		else if (str->at(offset) == '/')
		{
			offset++;
			tokenLength++;
			if (offset == len)//in case for some reason one of these characters is the end of a line
			{ 
				complete = true;
				break;
			}

			if (str->at(offset) == '/' || str->at(offset) == '*' || str->at(offset) == '=')
			{
				offset++;
				tokenLength++;
				break;
			}
			break;
		}
		else if (str->at(offset) == '(' || str->at(offset) == ')' || str->at(offset) == '[' || str->at(offset) == ']' ||
			str->at(offset) == '{' || str->at(offset) == '}')
		{
			offset++;
			tokenLength++;
			if (offset == len)
			{
				complete = true;
				break;
			}
			break;
		}

		else
		{
			while (str->at(offset) != '+' && str->at(offset) != '-' && str->at(offset) != '*' && str->at(offset) != '/' &&
				str->at(offset) != '(' && str->at(offset) != '{' && str->at(offset) != '.' && str->at(offset) != '&' &&
				str->at(offset) != ')' && str->at(offset) != '}' && str->at(offset) != ',' && str->at(offset) != '|' &&
				str->at(offset) != '[' && str->at(offset) != '<' && str->at(offset) != ';' && str->at(offset) != '!' &&
				str->at(offset) != ']' && str->at(offset) != '>' && str->at(offset) != ':' && str->at(offset) != '^' &&
				str->at(offset) != '#' && str->at(offset) != '~' && str->at(offset) != '"' && str->at(offset) != '\'' &&
				str->at(offset) != '=' && str->at(offset) != '%' && str->at(offset) != ' ' && str->at(offset) != '\t' &&
				str->at(offset) != '?')
			{
				//no special characters found, just take more characters.
				offset++;
				tokenLength++;
				if (offset == len)
				{
					complete = true;
					break;
				}
			}
			break;
		}

		if (offset == len)
		{
			complete = true;
			break;
		}
	}

	if (offset == len)
	{
		complete = true;
	}
}

//Sets the current string to be tokenized
//Resets all Tokenizer state variables
//Calls Tokenizer::prepareNextToken() as the last statement before returning.
void Tokenizer::setString(string *str)
{
	this->str = str;
	complete = false;
	processingIncludeStatement = false; //include statements end after one line
	processingInlineComment = false; //inline comments end after one line
	processingFloat = false; //float processing cannot be multi-line
	offset = 0;
	tokenLength = 0;
}

//Returns the next token. Hint: consider the substr function
//Updates the tokenizer state
//Updates offset, resets tokenLength, updates processingABC member variables
//Calls Tokenizer::prepareNextToken() as the last statement before returning.
string Tokenizer::getNextToken()
{
	prepareNextToken();
	string d = str->substr(offset - tokenLength, tokenLength);

	if (d == "//")
	{
		processingInlineComment = true;
	}

	else if (d == "/*")
	{
		processingBlockComment = true;
	}

	else if (d == "*/")
	{
		processingBlockComment = false;
	}

	else if (d == "#")
	{
		processingIncludeStatement = true;
	}
	return d;
}

//****Clippy class function definitions******

// Input: A tokenlist to be processed
// Output: Prints to the screen all the details nonverbose
void Clippy::print_nonverbose(TokenList &tokenList)
{
	cout << "\n" << "Number of assignment statements: ";
	getAssignmentStatements(tokenList);
	printBraceError(tokenList);
	printTypeError(tokenList);
	cout << "\n" << "Number of function declarations: ";
	getFunctionDeclarations(tokenList);
	printTokensTypes_NV(tokenList);
} // end of print_nonverbose

// Input: A tokenlist to be processed
// Output: Prints to the screen all the details nonverbose
void Clippy::print_verbose(TokenList &tokenList)
{
	cout << "\n" << "Number of assignment statements: ";
	getAssignmentStatements(tokenList);
	printBraceError(tokenList);
	printTypeError(tokenList);
	cout << "\n" << "Number of function declarations: ";
	getFunctionDeclarations(tokenList);
	printTokensTypes_V(tokenList);
} // end of print_verbose


