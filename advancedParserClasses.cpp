/*
All the code written by
Choong Jin Ng (301226977)
Steven Luu    (301150253)
*/

#include <string>
#include <cctype>
#include "lexemesTypes.h"
#include "advancedParserClasses.h"

using namespace std;


namespace ensc251_advancedparserclass
{
	// **** Identify ****
	void Identify::AssignmentStatements()
	{
		// Insert copy from project.cpp


	} // end of AssignmentStatements

	void Identify::FunctionStatements()
	{

	}

	// **** Clippy ****

	// Input: Assignment Statement
	// Output: Returns true if the include is defined correctly, returns false otherwise
	bool Clippy::includeStatement(const string &str)
	{
		string temp_string;
		// Reading each character of the string
		for (int ii = 0; ii != str.length(); ii++)
		{
			temp_string =temp_string + str[ii];

			// #include is missing
			if (ii == 7 && temp_string != "#include")
			{
				return false;
			}
		}

		temp_string.clear();
		return true;
	}

} // end of namespace ensc251_advancedparserclass