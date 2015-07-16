#ifndef ERRORS_H_
#define ERRORS_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//subtract line number by 4 to get index =]
char *error_statement[29] = { " ",
 "Use of illegal character \'=\', instead use \':=\'. ",
 "the character \'=\' must be follow by a number.", 
 "Identifiers must be follow by the character \'=\' or \":=\"", 
 "The words \"const\", \"var\", \"procedure\" must be followed by an identifier. ",
  "Comma or semicolon missing.", 
  "Incorrect symbol after procedure.", 
  "Statement expected.", 
  "Incorrect symbol after statement part in block",
  "Period expected.", 
  "Semicolon between statements missing.",
   "Undeclared identifier", 
   "Assigment to constant or procedure is not allowed", 
   "Assignment operator expected.", 
   "The command \"call\" must be followed by an identifier.", 
   "Call of a constant or variable is meaningless.", 
   "\"then\" is expected.", 
   " semicolon \';\' or period \'.\' expected.", 
   "Command \"do\" expected.",
    "Incorrect symbol following statement", 
    "Relational operator expected.", 
    "Expression must not contain a procedure identifier.", 
    "Right parenthesis \')\' missing.", 
"The preceding factor can not begin with this symbol.", 
"An expression  can not begin with the symbol %s", 
"The number %s is larger than the allowed length of %d.",
"begin block must be terminated with \"end\".",
"Identifier missing.",
"Duplicate identifier:  is already defined." };

void print_errors(int gIndex, int error, char s[]);

#endif