Sunayana Mitra
README
------------------------
FILES:
List.h - The List.h file defines all of the functions that can be used, when people want to use the Integer List
	ADT. This includes access functions as well as manipulation functions.
List.c - The List.c file actually defines all the functions in List.h. All List.h files will be usable with the
	addition of this file, so it is essential to be there.
ListTest.c - This file has a main that tests the functions of List.h and prints whether they were successful or
	not.
Lex.c - This file takes an input file and output file as the parameters. With these, it will read through the input
	file and sort each line into alphabetical order and output to the ouput file. It does this through the use
	of the List.h functions.
Makefile - The makefile builds the entire project, with emphasis towards the Lex function that alphabetizes a file.
	One can simply use the command "make" to have access to all the executables for this project.