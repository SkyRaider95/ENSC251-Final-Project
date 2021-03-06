/*
 * lexemesTypes.cpp
 *Created on: Oct 27, 2014
// Last Edited: 27 November 2014 - 6am
*/

/*
Choong Jin Ng	(301226977)
Steve Luu		(301150253)
*/

#include "lexemesTypes.h"

namespace ensc251
{
	//***Complete the implementation of the following functions: ***

	//This function returns TRUE if the input is identifier else FALSE
	bool isIdentifier(const string &lexeme)
	{
		int ii = 0;
		//Checks the first character of string is a valid identifier name
		for (int i = 0; i != numElement_identifierNames; i++)
		{
			// Matches identifier letters
			if (lexeme.at(ii) == identifierNames[i])
			{
				ii++;

				//Checks the rest of the string for valid identifier characters
				for (int jj = ii; jj != lexeme.length(); jj++)
				{
					//Compares char to valid identifier names
					for (int j = 0; j != numElement_identifierNames; j++)
					{
						// Matches identifier letters
						if (lexeme.at(jj) == identifierNames[j])
						{
							ii++;
						}

						// Matches to a number
						else if (lexeme.at(jj) == numberStuff[j])
						{
							ii++;
						}
					}


					if (ii == lexeme.length())
					{
						return true;
					}

					else
					{
						return false;
					}

				}

				//For the single char names
				if (ii == lexeme.length())
				{
					return true;
				}

				else
				{
					return false;
				}
			}
		}
		return false;

  } // end of isIdentifier

	//This function returns TRUE if the input is one of the operators defined in the variable
	//"tableOfOperators" in "lexemesTypes.h" else it returns FALSE
	bool isOperator(const string &lexeme)
	{
		for (int ii = 0; ii != numElement_tableOfOperators; ii++)
		{
			if (lexeme == tableOfOperators[ii])
			{
				return true;
			}
		}

		return false;
	} // end of isOperator

	//This function returns TRUE if the input is one of the punctuators defined in the variable
	//"tableOfPunctuators" in "lexemesTypes.h" else it returns FALSE
	bool isPunctuator(char lexeme)
	{
		for (int ii = 0; ii != numElement_tableOfPunctuators; ii++)
		{
			// Matches correctly
			if (lexeme == tableOfPunctuators[ii])
			{
				return true;
			}
		}

		// Does not match
		return false;
	} // end of isPuntuator

	//This function returns TRUE if the input is one of the keywords defined in the variable
	//"tableOfKeywords" in "lexemesTypes.h" else it returns FALSE
	bool isKeyword(const string &lexeme)
	{
		for (int ii = 0; ii != numElement_tableOfKeywords; ii++)
		{
			if (lexeme == tableOfKeywords[ii])
			{
				return true;
			}
		}

		return false;
	} // end of isKeyword

	//This function returns TRUE if the input is one of the boolean defined in the variable
	//"booleanValues" in "lexemesTypes.h" else it returns FALSE
	bool isBooleanValue(const string &lexeme)
	{
		for (int ii = 0; ii != numElement_booleanValues; ii++)
		{
			if (lexeme == booleanValues[ii])
			{
				return true;
			}
		}
		return false;
	} // end of isBooleanValue
         
	// This function returns TRUE if the input is a number literal else FALSE
	bool isDigitLiteral(const string &lexeme)
	{
		for (int ii = 0; ii != lexeme.length(); ii++)
		{
			// Comparing to a number list
			for (int jj = 0; jj != numElement_numberStuff; jj++)
			{
				// Not a digit or a dot
				if (lexeme[ii] != numberStuff[jj] || lexeme[ii] != dot)
				{
					return false;
				}
			}
		}
		return true;
	} // end of isDigitLiteral
	
	//This function returns TRUE if the input is integer literal else FALSE
	bool isIntegerLiteral(const string &lexeme)
	{
	  int ii = 0;

	  //Checks for hex literal then moves onto next char in string by Searching for 0,x,X
	  for (int i = 0; i != numElement_hexStuff; i++)
	  {
		  if (lexeme.at(ii) == hexStuff[i])
		  {
			  for (int h = 0; h != numElement_hexStuff; h++)
			  {
				  if (lexeme.at(ii) == hexStuff[h])
				  {
					  ii = ii + 2;
				  }
			  }
		  }

		  //Function then proceeds as normal
		  //Checks the length of the string
		  for (int jj = ii; jj != lexeme.length(); jj++)
		  {
			  //Compares char to number values
			  for (int j = 0; j != numElement_numberStuff; j++)
			  {
				  if (lexeme.at(jj) == numberStuff[j])
				  {
					  ii++;
				  }

				  for (int hh = 0; hh != numElement_hexStuff; hh++)
				  {
					  if (lexeme.at(jj) == hexStuff[hh])
					  {
						  ii++;
					  }
				  }
			  }

			  if (ii >= lexeme.length())
			  {
				  return true;
			  }
		  }
		  return false;
	  }

	  return false;
	} // end of isIntegerLiteral

	// This function returns true if the input is a float literal else FALSE
	bool isFloatLiteral(const string &lexeme)
	{
		for (int ii = 0; ii != lexeme.length(); ii++)
		{
			// dot implies it is a float
			if (lexeme.at(ii) == dot)
			{
				ii++;

				//Checks for numbers after the dot
				for (int jj = ii; jj != lexeme.length(); jj++)
				{
					//Compares char to number values
					for (int j = 0; j != numElement_numberStuff; j++)
					{
						if (lexeme.at(jj) == numberStuff[j])
						{
							ii++;
						}
						else if (lexeme.at(jj) == hexStuff[j])
						{
							ii++;
						}
					}

					if (ii >= lexeme.length())
					{
						return true;
					}
				}
			}
		}
	  return false;
	  } // End of isFloatLiteral
	
	//This function returns TRUE if the input is string literal else FALSE
	bool isStringLiteral(const string &lexeme)
	  {
	  	// Searches the entire string
	  	int ii = 0;
		  // Comparing to the string list
		  for (int jj = 0; jj != numElement_stringStuff; jj++)
		  {
			  // If a ' " ' is found
			  if (lexeme.at(ii) == stringStuff[jj])
			  {
				  //Searchs for the ending quotation
				  for (int i = ii + 1; i != lexeme.length(); i++)
				  {
					  for (int j = 0; j != numElement_stringStuff; j++)
					  {
						  //If both quotations are found then return true
						  if (lexeme.at(i) == stringStuff[j])
						  {
							  return true;
						  }
					  }
				  }
			  }	
		  }
	  return false;
	  } // end of isString

	//This function returns TRUE if the input is a keyword that declares identifiers else FALSE
	bool isCheckIdentifierKeyWords(const string &lexeme)
	{
		// Look for identifier keywords
		for (int jj = 0; jj != numElement_identifierWords; jj++)
		{
			if (lexeme == identifierWords[jj])
			{
				return true;
			}
		}
		return false;
	} // end of isCheckIdentifierKeyWords

	// This function returns TRUE if the input is a library else FALSE
	bool isLibraryLiteral(const string &lexeme)
	{
		// Look for identifier keywords
		for (int jj = 0; jj != numElement_tableOfDefaultLibraries; jj++)
		{
			if (lexeme == tableOfDefaultLibraries[jj])
			{
				return true;
			}
		}
		return false;
	} // end of isLibrary function

} // end of namespace ensc251
