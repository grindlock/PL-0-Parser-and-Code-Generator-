#ifndef VM_H_
#define VM_H_

#include "tinymachine.h"

//CONSTANTS
#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3

struct instructions
{
	int op;
	int l;
	int m;
}opInst;


char* t[] = {"","LIT", "OPR", "LOD", "STO", "CAL", "INC", "JMP", "JPC", "SIO"};

//method use in the virtual machine
int base(int level, int b);
void readFromFile();
void writeInterpetratedInput();
void cmdsSwitch();
void operSwitch();
void vmRUN();
void writeRunTime(int f);

//initial state of the stack
int sp = 0;
int bp = 1;
int pc = 0;
int ir = 0;

//Global varibles
int stack[MAX_STACK_HEIGHT];
struct instructions oper[MAX_CODE_LENGTH];
struct instructions *IR;
int nCodeLines = 0;

//this is a flag for the halt instruction
int halt = 0;


//the stack frame tracker, the array size is set to 10
//just in case there are more codes
//if we know the number of frames and where it ends
//we know where to print the "|"
int frame[10];
int nframes = 0;
#endif