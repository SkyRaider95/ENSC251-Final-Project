Type: Final Project
Class: ENSC251
Date: 19 November 2014

Author: Choong Jin Ng (301226977)
		Steven Luu    (301150253)

Credits to: Daryl and Jason, for allowing us to modify their parcer class for this assignment

General:
Jin:	I'm thinking of implementing a new header file and a new cpp to implement the features of the compiler.
		No point creating a huge class for everything. What do you think? I created advancedParserClasses for this purpose.
Steven: It's a good idea but I wasn't sure how to properly implement the new classes in the advancedParserClasses 
		So for simplicity of coding I added most new functions to the project.cpp though it doesn't looks as clean
Jin:	If you are okay with it, I can put all the functions in project.cpp into advancerParserClasses.
Steven: I sent you an email of the version of the project I intend to submit since we are low on time and the code here on github
	doesn't appear to be finished. 
	
	Let me know if you think this is okay, the program works but the bugs mentioned before are still present.
	
	If we had more time we might've been able to resolve these issue but since almost everything in the program revolves
	around getAssignmentStatements I would rather hand in one that works but not for all case.

Jin:	We should work in resolving the issues with whitespaces. I have isolated the problem.
		It has to do with not considering that the string is empty (resolved)

		I discovered a bug for when 0 is used. Isolated it to setTokenClass. (Resolved)

		Also, we discovered that there is a bug where it does not recognise functions (unresolved).
		Also, there is a bug where it does not recognise libraries (unresolved).

Part 1:
Jin:	Mostly done, TA pointed out that this does not work if (bla bla) a = 0 (resolved)
		Listed some possibilities at the getAssignmentStatements function (resolved)
Steven: getAssignmentStatements function doesn't quite meet the specification of an assignment statement: "variable = expression;"
		It should be fine for the purposes of the project
Jin:	Agreed.
Part 2:
Steven:	Currently working on a bug in giving back the number of function declaration 
		Bug source is due to getAssignment Statements
Jin	:	

Part 3:
Jin:	For this part, I'm thinking we check through for any syntax errors first, then check for any other types of errors (Yes)

Steven:	Added function that checks for syntax error on braces
	Added non-verbose and verbose modes to project.cpp (Jin: I will turn them into advancedParserClasses)
	Added functions that calculate and gives statistics back to the user
	Functions appear to be working properly
	(Finish but only works with bool, int, float, and strings)Currently working on unmatched types 
Bonus:

Misc:
Steven: I sent you an email with my files for the project so far. This version works but has a couple of bugs with the getAssignmentStatementss.
		and with whitespace.
		I think this version should be used as a last resort as we don't have much time to finish this
		and this version is able to compile, run and works for several cases.
		
Jin:	I found the bug. It happens when test.cpp has "int a = 0". However, when I tried "int a = 1", it works. (unresolved)
		Also, if there is whitespace, the program will fail. (unresolved)
