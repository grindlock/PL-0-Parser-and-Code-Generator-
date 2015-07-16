

//read in the lexical analysis...
int read_lexilist()
{
    FILE *read = fopen("lexicallist.txt","r");
    input_read = (struct symbol*)malloc(sizeof(struct symbol));
    int i = 0;
    char str[MAX_IDENT_LEN];
    char *tmp;
    int d;

    while(fscanf(read, "%s", str)!=EOF)
    {
        int temp = atoi(str);
        if(temp == identsym)
        {
            input_read[i].token= temp;
            fscanf(read, "%s", str);
            strcpy(input_read[i].lexeme, str);
           // printf("From table lexeme: %s\n", input_read[i].lexeme);
        }
        else if(temp == numbersym)
        {
            input_read[i].token= temp;
            fscanf(read, "%s", str);
            input_read[i].val = atoi(str);
          //  printf("From table val: %d\n", input_read[i].val);
        }
        else
        {
            input_read[i].token= temp;
        }
      //  printf("From table: %d\n", input_read[i].token);
        i++; //increment loop...
        input_read = (struct symbol*)realloc(input_read,(i+2)*sizeof(struct symbol));
    }
    fclose(read);
    return i;
}

//Until next comment all below are for block
int parse_block(int gIndex, struct symbol symbol_table[])
{
    int temp = cx;
    addr = 4;

    //emit(JMP, 0, 0); // JMP proccess

  //  printf("Hit parse_block\n");
    if(input_read[gIndex].token == constsym)
    {
        //symbol_table[symIndex].token = 1;
        //temp = symIndex;
        gIndex++;
        gIndex = parse_const(gIndex, symbol_table);
        //emit(temp, symbol_table, INC, 0, symIndex+4);
        //symIndex++;
    }
    if(input_read[gIndex].token == varsym)
    {
        /*int i;
        for(i = 0 ; i <gIndex; i++){
            if(input_read[i].token =constsym)
            {
                break;
            }
            else if(i== gIndex-1)
            {
                //throw error
                print_errors(gIndex, 12,NULL);
            }
        }*/
        //temp = symIndex;
        gIndex++;
        gIndex = parse_var(gIndex, symbol_table);

    }

    /*while(get_token(gIndex, symbol_table) == procsym)
    {
        symbol_table[symIndex].token = 3;
        gIndex++;
        gIndex = parse_procedure( gIndex, symbol_table);
        //here some code should be written to handle the generate code.
    }*/
  //  printf("in block method gIndex = %d\n", gIndex);
    //gIndex++;
    mcode[temp].address = cx;
    emit( INC, 0, addr);

    //symIndex++;
    gIndex = parse_statement(gIndex,symbol_table);

    //emit( OPR, 0, 0);
    //symIndex++;
 //  printf(" out of parse_block, gIndex=%d\n",gIndex);


    return gIndex;
}

//This check for a good implementation of const.    *** This function has been tested and works fine **
int parse_const(int gIndex, struct symbol symbol_table[])
{
   // printf("Hit parse_const\n");
    if(input_read[gIndex-1].token== constsym && input_read[gIndex].token!=identsym )
    {
        print_errors(gIndex, 4, NULL);
    }

    if(input_read[gIndex].token!=identsym )
    {
        print_errors(gIndex,27, NULL);
    }
    symbol_table[symIndex].token = 1;

    if(identifier_exists(symIndex, input_read[gIndex].lexeme, symbol_table))
    {
        print_errors(gIndex,28, input_read[gIndex].lexeme);
    }
    strcpy(symbol_table[symIndex].lexeme, input_read[gIndex].lexeme);
    addr++;


    gIndex++;

    if(input_read[gIndex].token != eqsym)
    {
        print_errors(gIndex, 3, NULL);
    }

    gIndex++;

    if(input_read[gIndex].token != numbersym)
    {
        print_errors(gIndex,2, NULL);
    }

    symbol_table[symIndex].val = input_read[gIndex].val;
    symbol_table[symIndex].address = symIndex+4;
    symIndex++;

    gIndex++;

    if(input_read[gIndex].token == commasym)
    {
        return parse_const(gIndex+1, symbol_table);
    }

    else if(input_read[gIndex-1].token == numbersym && input_read[gIndex].token == identsym)
    {
        print_errors(gIndex,5, NULL);
    }
    else if(input_read[gIndex-1].token == numbersym && input_read[gIndex].token != semicolonsym)
    {
        print_errors(gIndex,10, NULL);
    }
  //  printf(" out of parse_const, gIndex=%d\n",gIndex);

    return gIndex + 1;
}

//This check for a good implementation of var.    *** This function has been tested and works fine **
int parse_var(int gIndex, struct symbol symbol_table[])
{
 //   printf("Hit parse_var\n");


    if(input_read[gIndex].token == identsym)
    {
        symbol_table[symIndex].token = 2;
        if(identifier_exists(symIndex, input_read[gIndex].lexeme, symbol_table))
        {
            print_errors(gIndex,28, input_read[gIndex].lexeme);
        }
        strcpy(symbol_table[symIndex].lexeme,input_read[gIndex].lexeme);
        symbol_table[symIndex].address = symIndex+4;
        symIndex++;
        addr++;
        gIndex++;

        while(input_read[gIndex].token == identsym || input_read[gIndex].token == commasym)
        {

            if(input_read[gIndex-1].token == identsym && input_read[gIndex].token == identsym)
            {
           //     printf("here , \n");
                print_errors(gIndex, 5,NULL);
            }
            else if(input_read[gIndex].token == identsym)
            {
                if(identifier_exists(symIndex, input_read[gIndex].lexeme, symbol_table))
                {
                    print_errors(gIndex,28, input_read[gIndex].lexeme);
                }
                symbol_table[symIndex].token = 2;
                strcpy(symbol_table[symIndex].lexeme,input_read[gIndex].lexeme);
                symbol_table[symIndex].address = symIndex+4;
                addr++;
                symIndex++;
            }

            gIndex++;

        }

        if(input_read[gIndex].token != semicolonsym)
        {
            print_errors(gIndex,10, NULL);
        }
    }

    else
    {
        print_errors(gIndex,4,NULL);
    }

   // printf(" out of parse_var, gIndex=%d\n",gIndex);

    //symbolIndex++;
    return gIndex+1;
}

/*int parse_procedure(int gIndex, struct symbol symbol_table[]){   // everything seems to be working right.

    if(get_token(gIndex, symbol_table)!=identsym)
    {
        print_errors(gIndex,4, NULL);
    }
    gIndex++;
    if(get_token(gIndex, symbol_table)!=semicolonsym)
    {
        print_errors(gIndex, 5, NULL);
    }
    gIndex++;

    gIndex = parse_block(gIndex, symbol_table);

    if(symbol_table[gIndex].token!=semicolonsym){
        print_errors(gIndex, 17, NULL);
    }
    return gIndex;
}*/

//until next comment all below are for statement

int parse_statement(int gIndex, struct symbol symbol_table[])
{
  //  printf("Hit parse_statement\n");
    switch(input_read[gIndex].token)
    {
    case identsym:
        gIndex = parse_ident(gIndex, symbol_table);
        break;
    case callsym:
        gIndex = parse_call(gIndex,symbol_table);
        break;
    case beginsym:
        gIndex = parse_begin(gIndex,symbol_table);
        break;
    case ifsym:
        gIndex = parse_if(gIndex,symbol_table);
        break;
    case elsesym:
        gIndex = parse_else(gIndex, symbol_table);
        break;
    case whilesym:
        gIndex = parse_while(gIndex,symbol_table);
        break;
    case readsym:
        gIndex = parse_ident_read(gIndex, symbol_table);
        break;
    case writesym:
        gIndex = parse_ident_write(gIndex, symbol_table);
        break;
    }
  //  printf(" out of parse_statement, gIndex=%d token = %d  lexeme = %s  \n",gIndex+1, input_read[gIndex+1].token,input_read[gIndex+1].lexeme);
   
    return gIndex++;
}

int parse_else(int gIndex, struct symbol symbol_table[])
{
    gIndex++;
    gIndex = parse_statement(gIndex, symbol_table);

    return gIndex;
}


int parse_ident_read(int gIndex, struct symbol symbol_table[])
{
  //  printf("Hit parse_ident_read\n");
    gIndex++;
    if(input_read[gIndex].token == identsym)
    {

        if(check_for_valid_var(symIndex,symbol_table,input_read[gIndex].lexeme)==true)
        {
            if(tType == 1) // constants
            {
                print_errors(gIndex, 12, NULL);
            }
            else if (tType == 2) // variables
            {
                emit(SIO, 0, 1);
                emit(STO, 0, mem);

            }

            /*gIndex++;

            if(input_read[gIndex].token != semicolonsym)
            {
                print_errors(gIndex, 5, NULL);
            }*/
        }
        else
        {
            print_errors(gIndex, 11, input_read[gIndex].lexeme);
        }
    }
    else
    {
        print_errors(gIndex,27,NULL);
    }
    gIndex++;
    //printf("  out of parse_read gIndex = %d  token = %d\n", gIndex,input_read[gIndex].token);
    gIndex = parse_statement(gIndex, symbol_table);
    return gIndex;
}

int parse_ident_write(int gIndex, struct symbol symbol_table[])
{
   // printf("Hit parse_ident_write\n");
    gIndex++;
    if(input_read[gIndex].token == identsym)
    {

        if(check_for_valid_var(symIndex,symbol_table,input_read[gIndex].lexeme)==true)
        {
          //  printf("    pass var check\n");
            if(tType == 1) // constants
            {
                emit(LIT, 0, mem);
                emit(SIO, 0, 0);
            }
            else if (tType == 2) // variables
            {
                emit(LOD, 0, mem);
                emit(SIO, 0, 0);

            }
            //symIndex++;
            /*gIndex++;

            if(input_read[gIndex].token != semicolonsym)
            {
                    print_errors(gIndex,5,NULL);
            }*/
        }
        else
        {
            print_errors(gIndex,11,input_read[gIndex].lexeme);
        }
    }
    else
    {
        print_errors(gIndex,27,NULL);
    }

    gIndex++;
   // printf("  out of parse_write gIndex = %d, token = %d\n",gIndex,input_read[gIndex].token);
    gIndex = parse_statement(gIndex,symbol_table);

    return gIndex;
}




int parse_ident(int gIndex, struct symbol symbol_table[])
{
  //  printf("Hit parse_ident\n");


    if(check_for_valid_var(symIndex,symbol_table,input_read[gIndex].lexeme)==true)
    {
        gIndex++;
        int tempMem = mem;

        //printf("%d",input_read[gIndex].token);

        if(input_read[gIndex].token != becomessym)
        {
            print_errors(gIndex, 1, NULL);
        }

        gIndex++;
        gIndex = parse_expression(gIndex,symbol_table);
        emit(STO, 0, tempMem);
    }
    else
    {
        print_errors(gIndex,11,NULL);
    }
//    printf(" out of parse_ident, gIndex=%d\n",gIndex);

    return gIndex;
}

int parse_call(int gIndex,struct symbol symbol_table[])
{
   // printf("Hit parse_call\n");
    gIndex++;
    if(input_read[gIndex].token != identsym)
    {
        print_errors(gIndex,9, NULL);
    }
  //  printf(" out of parse_call, gIndex=%d\n",gIndex);
   
    return gIndex;
}

int parse_begin(int gIndex,struct symbol symbol_table[])
{
   // printf("Hit parse_begin\n");
    gIndex++;
    gIndex = parse_statement(gIndex,symbol_table);
    int token = input_read[gIndex].token;
   
    while(input_read[gIndex].token == semicolonsym)
    {
        gIndex++;
        gIndex= parse_statement(gIndex, symbol_table);
    }
    int token1 = input_read[gIndex-1].token; int token2 = input_read[gIndex].token;

    if((token1 == identsym || token1 == numbersym || token1 == rparentsym) && (token2 == identsym))
    {     
        print_errors(gIndex,10,NULL);
    }


    else if(input_read[gIndex].token != endsym)
    {
        printf("error\n");
        print_errors(gIndex,26, NULL);
    }
    gIndex++;
 //   printf(" out of parse_begin, gIndex=%d\n",gIndex);
    //symbolIndex++;
    return gIndex;
}

int parse_if(int gIndex,struct symbol symbol_table[])
{
    int cxTemp;
   // printf("Hit parse_if\n");
    gIndex++;
    gIndex = parse_condition(gIndex,symbol_table);

    if(input_read[gIndex].token != thensym)
    {
        print_errors(gIndex,16, NULL);
    }
    else
        gIndex++;

    cxTemp = cx;
    emit(JPC, 0, 0);

    gIndex = parse_statement(gIndex,symbol_table);
  //  printf(" out of parse_if, gIndex=%d\n",gIndex);
    mcode[cxTemp].address = cx;

    return gIndex;
}

int parse_while(int gIndex,struct symbol symbol_table[])
{
  //  printf("Hit parse_while\n");
    int cxTemp1 = cx;
    gIndex++;
    gIndex = parse_condition(gIndex,symbol_table);
    int cxTemp2 = cx;
    emit(JPC, 0, 0);
    //symIndex++;
    if(input_read[gIndex].token != dosym)
    {
        print_errors(gIndex,18, NULL);
    }
    else
        gIndex++;

    gIndex = parse_statement(gIndex,symbol_table);
   // printf(" \n\n OUT OF WHILE LOOP, gIndex=%d\n\n",gIndex);
    emit(JMP, 0, cxTemp1);
    mcode[cxTemp2].address = cx;
   
    return gIndex;
}


//...For condition
int parse_condition(int gIndex,struct symbol symbol_table[])
{
  //  printf("Hit parse_condition\n");
    if(input_read[gIndex].token == oddsym)
    {
        gIndex++;
        gIndex = parse_expression(gIndex,symbol_table);
    }
    else
    {
        gIndex = parse_expression(gIndex,symbol_table);

        if(isRelation(gIndex)==false)
        {
            print_errors(gIndex, 20, NULL);
        }
        int tp = gIndex;
    //    printf("Print tp before expr = %d\n",tp);
        gIndex++;
        gIndex = parse_expression(gIndex,symbol_table);
     //   printf("     Print tp after expr = %d\n",tp);
        parse_relation(tp, symbol_table);

    }
  //  printf(" out of parse_condition, gIndex=%d\n",gIndex);

    return gIndex;
}


int isRelation(int gIndex)
{
    int token = input_read[gIndex].token;
  //  printf("inside of isRelation token = %d\n", token);
    switch (token)
    {
    case eqsym:
     //   printf("out of isRelation  =\n");
        return true;

    case neqsym:
      //  printf("out of isRelation  <>\n");
        return true;

    case lessym:
    //    printf("out of isRelation  <\n");
        return true;

    case leqsym:
     //   printf("out of isRelation  <=\n");
        return true;

    case gtrsym:
     //   printf("out of isRelation  >\n");
        return true ;

    case geqsym:
      //  printf("out of isRelation  >=\n");
        return true;

    default:
     //   printf("out of isRelation  none\n");
        return false;
    }
}

void parse_relation(int gIndex, struct symbol symbol_table[])
{
    switch(input_read[gIndex].token)
    {
    case eqsym:
        emit(OPR, 0, EQL);
        break;

    case neqsym:
        emit(OPR, 0, NEQ);
        break;

    case lessym:
        emit(OPR, 0, LSS );
        break;

    case leqsym:
        emit(OPR, 0, LEQ );
        break;

    case gtrsym:
        emit(OPR, 0, GTR );
        break;

    case geqsym:
        emit(OPR, 0, GEQ );
        break;

    default:
        break;
    }

    //return gIndex;
}

int parse_expression(int gIndex, struct symbol symbol_table[])
{

    int op;

    if(input_read[gIndex].token == plussym || input_read[gIndex].token == minussym)
    {
        op = input_read[gIndex].token;
        gIndex++;
        gIndex = parse_term(gIndex,symbol_table);

        if(op == minussym)
        {
            emit( OPR, 0, NEG);
        }
    }
    else
    {
        gIndex = parse_term(gIndex, symbol_table);
        //emit(symIndex,symbol_table,LOD, 0, mem);
      
    }

    while(input_read[gIndex].token == plussym || input_read[gIndex].token == minussym)
    {
        op = input_read[gIndex].token;

        gIndex++;
        gIndex = parse_term(gIndex, symbol_table);
        if(op == plussym)
        {
            emit(OPR, 0, ADD);
        }
        else
        {
            emit(OPR, 0, SUB);
        }
    }
    return gIndex;
}

int parse_term(int gIndex,struct symbol symbol_table[])
{
    int op;

    gIndex = parse_factor(gIndex,symbol_table);

    while(input_read[gIndex].token == multsym || input_read[gIndex].token == slashsym)
    {
        op = input_read[gIndex].token;
        gIndex++;
        gIndex = parse_factor(gIndex,symbol_table);

        if(op == multsym)
        {
            emit(OPR, 0, MUL);
        }
        else
        {
            emit(OPR, 0, DIV);
        }
    }

    return gIndex;
}

int parse_factor(int gIndex,struct symbol symbol_table[])
{
  //  printf("Hit parse_factor\n");
    if(input_read[gIndex].token == identsym)
    {
        mem = 0;
        loc = 0;
        tType = 0;
        int ans = check_for_valid_var(symIndex, symbol_table, input_read[gIndex].lexeme);
        if(ans == true)
        {
            if(symbol_table[loc].token == 1)
            {
                emit(LIT, 0, symbol_table[loc].val);
            }
            else if(symbol_table[loc].token == 2)
            {
                emit(LOD, 0, mem);
            }
        }
        gIndex++;
    }
    else if(input_read[gIndex].token == numbersym)
    {
        emit(LIT, 0, input_read[gIndex].val);
        gIndex++;
    }

    /// MIGHT NEED TO ADD AN ERROR HERE.

    else if(input_read[gIndex].token == lparentsym)
    {
        gIndex++;
        gIndex = parse_expression(gIndex,symbol_table);

        if(input_read[gIndex].token != rparentsym)
        {
            print_errors(gIndex, 22, NULL);
        }
        gIndex++;
    }
    else
    {
        print_errors(gIndex, 23, symbol_table[gIndex].lexeme);
    }
   // printf(" out of parse_factor, gIndex=%d\n",gIndex);

    //symbolIndex++;
    return gIndex;
}


int check_for_valid_var(int gIn, struct symbol symbol_table[], char lex[])
{
    int i = 0;
    while (i < gIn)
    {
        if(symbol_table[i].token == 1 || symbol_table[i].token == 2)
            if(strcmp(symbol_table[i].lexeme, lex)==0)
            {
                //printf("in check  i = %d, address = %d\n",i,symbol_table[i].address);
                mem = symbol_table[i].address;
                loc = i;
                tType = symbol_table[i].token;
                return true;
            }

        i++;
    }
    mem = -7;
    return false;
}

/*int get_token(int gIndex, struct symbol symbol_table[])
{
    return symbol_table[gIndex].token;
}*/



//ALL Below are for program
void parse_program ()
{
    int symbolTableLength;
    struct symbol symbol_table[MAX_SYM_TABLE];
//struct  symbol mcode[MAX_CODE_LENGTH];
    
    int i;
    for(i = 0 ; i <MAX_SYM_TABLE; i++)
    {
        symbol_table[i].token = 0;
        symbol_table[i].level = 0; //Hope for the best
        symbol_table[i].op = -1;
        symbol_table[i].address = -1;
    }
    symbolTableLength = read_lexilist();
    symIndex = 0;
    cx = 0;
    int gIndex = 0;

    gIndex = parse_block(gIndex, symbol_table);

    if(input_read[gIndex].token != periodsym)
    {
        print_errors(gIndex, 9,NULL);
    }
   
    printf("\nNo errors, program is syntactically correct.\n");
 
    emit( SIO, 0, 2);
    
    print_mcode(mcode);

    //return 0;
}


void emit( int op, int l, int m)
{
    if(cx < MAX_CODE_LENGTH)
    {
        mcode[cx].op = op;
        mcode[cx].level = l;
        mcode[cx].address = m;
       // printf("BEFORE INC CX  %d\n", cx);
        cx++;
       // printf("AFTER INC CX  %d\n", cx);

    }
    else
    {
        printf("\nERROR: CODE EXCEDS LENGTH\n");
        exit(1);
    }
}

void print_mcode(struct symbol symbol_table[])
{
    FILE *wmcode = fopen("mcode.txt","w");

    int i;
    for(i = 0; i < cx; i++)
    {
        if(mcode[i].op != -1)
        {
            if(i == cx-1)
            {
                fprintf(wmcode, "%d %d %d",mcode[i].op, mcode[i].level,mcode[i].address);
            }
            else
            {
                fprintf(wmcode, "%d %d %d\n",mcode[i].op, mcode[i].level,mcode[i].address);
            }
        }
    }
    fclose(wmcode);
}


int identifier_exists(int symbolIndex, char* lexeme, struct symbol symbol_table[])
{

    int i;
  //  printf("In identifier exists.\n");
   // printf("%s: lexeme inputted", lexeme);
    for(i = 0; i <symbolIndex; i++)
    {
       // printf("%s: lexemes from symbol table\n", lexeme);
        if(strcmp(lexeme, symbol_table[i].lexeme)==0)
        {
            return true;
        }
    }
    return false;
}
