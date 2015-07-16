#ifndef LEXIFUNCTIONS_H_
#define LEXIFUNCTIONS_H_


#include "tinymachine.h"

//store the information after been processed
struct lexi_analyzer{
    int typeToken;
    char *lexeme; 
    int val;
    int level;
    int adr;
};

//struct to store a string. this coulb use to stroe the line read from the file.
struct linesRead{
	char *line;
	struct linesRead *next;
};





//struct to store each token
struct token
{
    Token type;
    char lexeme[MAX_IDENT_LEN];
    struct token* next;
};

 int gIndex;
 struct lexi_analyzer symbol_table[MAX_SYM_TABLE];

 char *reserved_words[31] = { "odd", "begin", "end", "if", "then", 
 							  "while", "do", "call", "const", "var", 
 							  "procedure", "write", "read", "else", "NULL", 
 							  "+", "-", "*", "/","=",
 							  "!=","<","<=",">",">=",
 							  "(", ")", ",", ";", ".",
 							  ":="};

int rwNum[31] = {oddsym, beginsym, endsym, ifsym, thensym, 
				whilesym, dosym, callsym, constsym, varsym, 
				procsym, writesym, readsym, elsesym, nulsym, 
				plussym, minussym, multsym, slashsym, eqsym, 
				neqsym, lessym,leqsym, gtrsym, geqsym, 
				lparentsym, rparentsym, commasym, semicolonsym, periodsym, 
				becomessym};

void run_lexical();

struct linesRead *read_file();

char *tempStr(char str[], int g);

void punctuationCases(char str[], char s[], int g);

void identifer_check(char s[]);

int isThisLetter(char a);

int isThisInteger(char a);

int isThispunctuation(char a);

int isThisReservedWord(char rWord[]);
//Reads a line from a file
char* readLine( FILE *in);
//find if reseverd word or regular identifier
//struct lexi_analyzer identifer_check(char ind[]);
//create a node for a linked list
struct linesRead *create_linked_list_node(struct linesRead *nodePass, char *arr);
//
//struct lexi_analyzer *create_linked_list_lexeme(struct lexi_analyzer *nodePass, char *arr, int tpe);
//prints the linked list
void print_linked_list(struct linesRead *node);

struct token* tokenInsertBack(struct token* tokens, char* lexeme, int type);

#endif
