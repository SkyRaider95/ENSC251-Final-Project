/*
All the code written by
Choong Jin Ng (301226977)
Steven Luu    (301150253)
*/

#include <string>
#include <cctype>
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


	Token* Identify::AssignmentStatements(TokenList &tokenList)
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
			}

			// These if-elseif functions should be be run like an array or something
			else if (temp_token->getStringRep() == "if")
			{

			}

			/*
			Special cases are:
			#include
			if and else-if statements
			while
			functions
			class
			namespace
			*/


			// End of assignment statement. Place the assignment into assignment_token and clears the string
			else if (temp_token->getStringRep() == ";")
			{
				assignment_token.append(temp_string);
				temp_string.clear();
			}

			// Next string
			temp_token = temp_token->getNext();
		}

		return (assignment_token.getFirst());
	} // end of AssignmentStatements

	void Identify::FunctionStatements()
	{

	}

	// **** Clippy ****

	// Input: Assignment Statement
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

} // end of namespace ensc251_advancedparserclass