#ifndef  TINYMACHINE_H_
#define  TINYMACHINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "errors.c"



#define MAX_IDENT_LEN 11
#define MAX_INT_LEN 5
#define MAX_SYM_TABLE 100
#define MAX_CODE_LENGTH 500
#define true 1
#define false 0



typedef enum {nulsym = 1, identsym, numbersym, plussym, minussym,
 multsym, slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
 gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
 periodsym, becomessym, beginsym, endsym, ifsym, thensym,
 whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
 readsym , elsesym } Token;

typedef enum {RET, NEG, ADD, SUB, MUL, DIV, ODD, MOD, EQL, NEQ, LSS, LEQ, GTR, GEQ} OPER;
typedef enum CMDS {SSS, LIT, OPR, LOD, STO, CAL, INC, JMP, JPC, SIO} CmdIndex;


struct symbol
{
    int token;     //Const = 1, Var = 2, Proc = 3
    char lexeme[MAX_IDENT_LEN];
    int val;       //Number
    int op;        //OPR
    int level;     //L level
    int address;   //M address
    };


int symIndex;
int mem;
int cx;
int loc;
int addr;
int tType;
struct symbol *input_read;
struct  symbol mcode[MAX_CODE_LENGTH];

#endif
