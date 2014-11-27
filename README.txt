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

Part 1:
Jin:	Mostly done, TA pointed out that this does not work if (bla bla) a = 0 (resolved)
		Listed some possibilities at the getAssignmentStatements function (resolved)
Steven: getAssignmentStatements function doesn't quite meet the specification of an assignment statement: "variable = expression;"
		It should be fine for the purposes of the project
Jin:	Agreed.
Part 2:
Steven:	Currently working on a bug in giving back the number of function declaration 
Jin	:	

Part 3:
Jin:	For this part, I'm thinking we check through for any syntax errors first, then check for any other types of errors (Yes)
		For the matching braces part, I am thinking of doing such that when analyzing assignment statements, it will check for the braces.
		This might be better since we don't need to loop unnecessary. Also, we don't want the program to stop at every error

Steven:	Added function that checks for syntax error on braces
	Added non-verbose and verbose modes to project.cpp (Jin: I will turn them into advancedParserClasses)
	Added functions that calculate and gives statistics back to the user
	Functions appear to be working properly
	Currently working on unmatched types
Bonus:

Misc:
Jin:	I found the bug. It happens when test.cpp has "int a = 0". However, when I tried "int a = 1", it works. (unresolved)
		Also, if there is whitespace, the program will fail. (unresolved)
		When I input once, it prints but no values show up. Only tranverse actually works.
		When I input again, it breaks. (unresolved)
