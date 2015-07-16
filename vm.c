
///read the instructions from inputfile
//file name has to be "mcode.txt"
void readFromFile(){

    //initialize the file pointer
    //read the input file
	FILE *filename = fopen("mcode.txt", "r");
	int nLines = 0;
	//loop through the file
	if(filename!=NULL)
	{
		while(nLines < MAX_CODE_LENGTH && !feof(filename))
		{
			fscanf(filename, "%d", &oper[nLines].op);
			fscanf(filename, "%d", &oper[nLines].l);
			fscanf(filename, "%d", &oper[nLines].m);

			nLines++;
		}
	}
	//if the file pointer is null, promot the user with file missing
	else
	{
		printf("%s\n","file not found" );
	}
	//close the file pointer
	fclose(filename);
	nCodeLines = nLines;
}

//this function process the call of the vm
void vmRUN()
{
	//initialize the stacks
	stack[1] = 0;
	stack[2] = 0;
	stack[3] = 0;

	int flag = 1;

	//This function reads from the mcode file and
	//loads the struct array
	readFromFile();
	//this function creates stacktrace.txt and write to the file
	//what was red from the mcode file
    writeInterpetratedInput();
    //runs all the process and append to the
    //stacktrace.txt file

	//the program will run until the halt flag is not true.
	//if there is no halt operation in the input, the program will stopped after it reads all the lines of input
	while(!halt) //|| nCodeLines>=2)
	{
		//this only will be call if not HALT code <9 0 2> has be found 
		//and have reach the of the instructions array.
		// the program will exit because of wrong command.
		/*if(nCodeLines < 1)
		{
			printf("Program exit on wrong OP.");
			exit(EXIT_FAILURE);
		}*/
		writeRunTime(flag);
		flag = 0;

        nCodeLines--;
	}
}


//this function holds all the instructions
//this pesudocode of the ISA is provided on project instructions
void cmdsSwitch( void )
{
	//the fetch cycle of the instruction
	IR = &oper[pc];
	pc++;
	//end of fetch

	switch(IR->op)
	{
	    //push M onto stack
		case LIT:
			sp ++;
			stack[sp] = IR->m;

		break;

        //arithmetic or logical operaction
		case OPR:
			operSwitch();
		break;

        //get the value at offset M in frame L levels down and pust it
		case LOD:
			sp +=1;
			stack[sp] = stack[base(IR->l, bp) + IR->m];
		break;

		//pop stack and insert M in fram L levels down
		case STO:
			stack[base(IR->l, bp) + IR->m] = stack[sp];
			sp--;
		break;

		//call procedure at M
		//generates new stack frame
		case CAL:
			stack[sp + 1] = 0;
			stack[sp + 2] = base(IR->l, bp);
			stack[sp + 3] = bp;
			stack[sp + 4] = pc;
			bp = sp + 1;
			pc = IR->m;
            //the current
            frame[nframes]=bp;
            //in CAL it will create a new stack frame
            //the number of AR should increase by 1
            nframes++;
            //in this project, the max stack is 3
            //this if statement is here only in case there is more than 3 stack frames
            if (nframes > MAX_LEXI_LEVELS)
            {
                printf("Only three Active Records can be built at this time.\n");
                exit(EXIT_FAILURE);
            }
		break;

		//allocate M locals on stack
		case INC:
			sp += IR->m;
		break;

		//jump to M
		case JMP:
			pc = IR->m;
		break;

		//pop stack and jump to M if value is equal to 0
		case JPC:
			if(stack[sp] == 0)
			{
				pc = IR->m;
			}
			sp -= 1;
		break;

		//there are 3 modes of SIO
		//SIO 0 0: pop stack and print out the value
		//SIO 0 1: read the input from the user and push it
		//SIO 0 2: halt the machine
		case SIO:
			if(IR->m == 0)
			{
				printf("%d\n", stack[sp]);
				sp -= 1;
			}
			else if(IR->m == 1)
			{
				sp += 1;
			    printf("Please enter the value:\n");
                scanf("%d",&stack[sp]);
			}
			else if(IR->m == 2)
			{
			    //halt the vm
			    //set the halt flag to 1
			    //therefore the program will stop
			    halt = 1;
			}
			else
            {
                printf("Invaild SIO mode.\n");
            }
		break;

		default:
		    printf("Invaild Instruction.\n");
		break;
	}

}

//this function holds all the OPR instructions
//pseudocode under each switch is provided on project instruction
void operSwitch()
{
	switch(IR->m)
	{
		case RET:
			sp = bp -1;
			pc = stack[sp + 4];
			bp = stack[sp + 3];
			//reset the current stack frme
			frame[nframes] = 0;
			//the number of stack frames should decrease by 1
			nframes--;
		break;

		case NEG:
			stack[sp] = -stack[sp];
		break;

		case ADD:
			sp -= 1;
			stack[sp] += stack[sp + 1];
		break;

		case SUB:
			sp -= 1;
			stack[sp] -= stack[sp + 1];
		break;

		case MUL:
			sp -= 1;
			stack[sp] *= stack[sp + 1];
		break;

		case DIV:
			sp -= 1;
			stack[sp] /= stack[sp + 1];
		break;

		case ODD:
			if(stack[sp] % 2 ==1)
			{
				stack[sp] = 1;
			}
			else
			{
				stack[sp] = 0;
			}
		break;

		case MOD:
			sp -= 1;
			stack[sp] %= stack[sp + 1];
		break;

		case EQL:
			sp -= 1;
			if(stack[sp] == stack[sp + 1])
			{
				stack[sp] = 1;
			}
			else
			{
				stack[sp] = 0;
			}
		break;

		case NEQ:
			sp -= 1;
			if(stack[sp] != stack[sp + 1])
			{
				stack[sp] = 1;
			}
			else
			{
				stack[sp] = 0;
			}
		break;

		case LSS:
			sp -= 1;
			if(stack[sp] < stack[sp + 1])
			{
				stack[sp] = 1;
			}
			else
			{
				stack[sp] = 0;
			}
		break;

		case LEQ:
			sp -= 1;
			if(stack[sp] <= stack[sp + 1])
			{
				stack[sp] = 1;
			}
			else
			{
				stack[sp] = 0;
			}
		break;

		case GTR:
			sp -= 1;
			if(stack[sp] > stack[sp + 1])
			{
				stack[sp] = 1;
			}
			else
			{
				stack[sp] = 0;
			}
		break;

		case GEQ:
			sp -= 1;
			if(stack[sp] >= stack[sp + 1])
			{
				stack[sp] = 1;
			}
			else
			{
				stack[sp] = 0;
			}
		break;

		default:
            printf("Invaild OPR modes.\n");
		break;

	}
}

//convert the input numbers to symbolic instructions and print it out
void writeInterpetratedInput()
{
    //initialize file pointer
	FILE *out = fopen("stacktrace.txt","w");

    //print the title
	fprintf(out, "Line\tOP\tL\tM\t\n");
    int a = 0;
    //loop through the codes
	for(a = 0; a < nCodeLines; a++)
	{
	    //print the code to file
		fprintf(out,"%d\t%s\t%d\t%d\t\n", a, t[oper[a].op],oper[a].l,oper[a].m);
	}

	fprintf(out, "\n\n");

    //close file pointer
	fclose(out);
}

//this function print the instructions states and stack states line by line
void writeRunTime(int beg)
{
    //initialize the file pointer
	FILE *out = fopen("stacktrace.txt","a");

	//print the initial state of the stacks
	//if no file created, print the result to screen
	if(beg == 1)
	{
		fprintf(out, "\t\t\t\t%s\t%s\t%s\t%s\t\n","pc","bp","sp","stack");
		fprintf(out, "%s\t\t\t%d\t%d\t%d\n","Initial values",pc,bp,sp);
	}

	//print out the converted symbolic instruction names and initial state
	fprintf(out,"%d\t%s\t%d\t%d\t",pc,t[oper[pc].op],oper[pc].l,oper[pc].m);
	//instruction switch to run the instructions and modified its states
	cmdsSwitch();
	//print out the instruction states
	fprintf(out,"%d\t%d\t%d\t",pc,bp,sp);

    //this sections is to print out the stack frames
    if (bp != 0)
    {
        int i,j;
        //loop through the stacks
        //sp is updated when there is a new stack used
        for (i=1; i<= sp; i++)
        {
            //loop thrgouth the stack frames
            for (j=0; j<=nframes; j++)
            {
                //when the stack frame number is equal to the stack pointer which is pointing to the top of the stack
                //it means the next number is the start of the new stack frame
                if (frame[j] == i)
                {
                    fprintf(out,"|");
                    if(beg == 1)
                    {
                        //if no file created, print "|" between stack frames to screen
                        printf("|");
                    }
                }
            }
            //print the state of the stacks
            fprintf(out,"%2d ",stack[i]);

            //if no file created, print the resut to screen
           /* if(beg == 1)
            {
                printf("%2d ",stack[i]);
            }*/
        }
        fprintf(out,"\n");
    }
    else
    {
        fprintf(out,"\n");
    }

    //close the file pointer
	fclose(out);
}

//find the a variable in a different Activation Record some L levels down
//this function was probated by the assignmet document.
//b -> base
int base(int level, int b)
{
    while (level > 0)
    {
        b = stack[b + 2];
        level--;
    }
    return b;
}