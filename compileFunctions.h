#ifndef COMPILEFUNCTIONS_H_
#define COMPILEFUNCTIONS_H_

#include "tinymachine.h"



void parse_program ();
int read_lexilist();                // **** TESTED FOR ALL CASES ****
int parse_block(int gIndex, struct symbol symbol_table[]);
int parse_const(int gIndex, struct symbol symbol_table[]);      // **** TESTED FOR ALL CASES ****
int parse_var(int gIndex, struct symbol symbol_table[]);        // **** TESTED FOR ALL CASES ****
//int parse_procedure(int gIndex, struct symbol symbol_table[]); this for hw4
int parse_statement(int gIndex,struct symbol symbol_table[]);
int parse_ident(int gIndex,struct symbol symbol_table[]);
int parse_call(int gIndex,struct symbol symbol_table[]);
int parse_begin(int gIndex,struct symbol symbol_table[]);
int parse_if(int gIndex,struct symbol symbol_table[]);
int parse_while(int gIndex,struct symbol symbol_table[]);
int parse_condition(int gIndex,struct symbol symbol_table[]);
int parse_expression(int gIndex,struct symbol symbol_table[]);
int parse_term(int gIndex,struct symbol symbol_table[]);
int parse_factor(int gIndex,struct symbol symbol_table[]);
int check_for_valid_var(int gIndex, struct symbol symbol_table[], char lex[]);
//int get_token(int gIndex, struct symbol symbol_table[]);
void emit( int op, int l, int m);
void print_mcode(struct symbol symbol_table[]);
int isRelation(int token);
void parse_relation(int gIndex, struct symbol symbol_table[]);
int parse_ident_read(int gIndex, struct symbol symbol_table[]);
int parse_ident_write(int gIndex, struct symbol symbol_table[]);
int parse_else(int gIndex, struct symbol symbol_table[]);
int identifier_exists(int symbolIndex, char* lexeme, struct symbol symbol_table[]);


#endif
