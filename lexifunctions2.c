
//#include "ourfunctions.h"

void run_lexical()
{
	FILE *cleanOut = fopen("cleanoutput.txt","w+");
	FILE *lexTable = fopen("lexicaltable.txt", "w");
	FILE *lexiList = fopen("lexicallist.txt", "w");

	fprintf(lexTable, "lexeme\ttoken\n");

	struct linesRead *llInput = read_file();
	struct linesRead *test = llInput;
	struct linesRead *w = NULL;

	char *word = (char *)NULL;

	//struct token* tokenList;//HOLDS ALL THE LEXEMES!!

while(test != NULL)
{
	
	gIndex = 0;

	while(gIndex < strlen(test->line))
	{
		word = tempStr(test->line, gIndex);
		//printf("%s  %lu\n", word, strlen(word));
		
		identifer_check(word);
		//w = create_linked_list_node(w, word);

		fprintf(cleanOut,"%s", word);	
	}
    
	fprintf(cleanOut, "\n");
	test = test->next;
}

	free(word);

	fclose(cleanOut);
fclose(lexiList);
fclose(lexTable);
	
}
//read line by line of a file and save to a linked link 
struct linesRead *read_file()
{
	char *filename = {"input.txt"};
	
	FILE *inp = fopen(filename,"r");
	struct linesRead *n = NULL;

	if(inp == NULL)
	{
		printf("ERROR: the file : \"input.txt\" not found.\n");
		exit(1);
	}

	char *lineR = (char *) NULL;

	while((lineR = readLine(inp)) !=  NULL)
	{
		n = create_linked_list_node(n, lineR);
	}

	free(lineR);
	fclose(inp);
	return n;
}

char *tempStr(char str[], int g)
{
	int j = 0;

	if(isThisLetter(str[g])==true)
	{ 
		char *s = (char *)malloc((j+1)*sizeof(char *));

		while( (int)str[g] != 32 && str[g] != '\0')
		{	
			if(isThispunctuation(str[g])==true )
			{
				break;
			}

			
			s[j] = str[g];
			s = (char *)realloc(s, ((j+1)*sizeof(char)));
			g++;
			j++;

			if(j > MAX_IDENT_LEN) //This stop the program is identifier is longer than allow.
			{
				printf("identifier length (%d) is greater than %d. Program HALT",j, MAX_IDENT_LEN);
				j=0;
				exit(1);
			}
		}
			
		s[j] = '\0';
		j=0;
		gIndex = g;
		
		return s;
	}

	else if(isThisInteger(str[g])==true)
	{
		char *s = (char *)malloc((j+2)*sizeof(char *));

		while( (int)str[g] != 32 && str[g]!='\0') // &&  (j < MAX_INT_LEN))
		{
			if(isThispunctuation(str[g]) == true)
			{
					break;
			}

			s[j] = str[g];
			s = (char *)realloc(s, ((j+1)*sizeof(char)));
			g++;
			j++;
			
			if(j > MAX_INT_LEN)  //This stop the program is number is longer than allow.
			{
				printf("Number length (%d) is greater than %d. Program HALT", j, MAX_INT_LEN);
				exit(1);
			}
		}

		s[j] = '\0';
		gIndex = g;

		return s;
	}

	else if(isThispunctuation(str[g])==true)
	{
		char *s = (char *)malloc((j+1)*sizeof(char *));
		punctuationCases(str, s, g);
		g++;
		return s;
	}
	else if((int)str[g] == 32)
	{
		char *s = (char *)malloc((j+2)*sizeof(char *));
		s[j++] = (char)32;
		s[j] = '\0';
		gIndex = g+1;
		return s;
	}

	else if(str[g] == '\t')
	{
		char *s = (char *)malloc((j+3)*sizeof(char *));
		s[j++] = (char)32;
		s[j++] = (char)32;
		s[j] = '\0';
		gIndex = g+1;
		return s;
	}
		//this lines should never happen, check input file.
		char *s = (char *)malloc(sizeof(char));
		s[0] = '\0';
		gIndex = g+1;

		return s;
}


void punctuationCases(char str[], char s[], int g)
{
	int j = 0;

	switch(str[g])
	{
			case '-':
				s[j] = str[g];
				s[j+1] = '\0';
				break;
			case '+':
				s[j] = str[g];
				s[j+1] = '\0';
				break;
			case '*':
				if(str[gIndex+1] != '/'){
					s[j] = str[g];
					s[j+1] = '\0';}
				break;

			case '/':
				{
					if(str[g+1] == '*')
					{
						g++; 
						while(1)
						{
							g++;
							if((str[g] == '*' && str[g+1] == '/'))
							{
								g +=2;
								break;
							}
							else if(str[g] == '\0')
							{
								break;
							}
						}
					}
					
						s[j] = str[g];	
					break;
				}	
			case '(':
				s[j] = str[g];
				s[j+1] = '\0';
				break;

			case ')':
				s[j] = str[g];
				s[j+1] = '\0';
				break;

			case ';':
				s[j] = str[g];
				s[j+1] = '\0';
				break;

			case ',':
				s[j] = str[g];
				s[j+1] = '\0';
				break;

			case ':':
				if(str[g+1] == '=')
				{
					s[j] = str[g];
					s = (char *)realloc(s, ((j+2)*sizeof(char *)));
					s[++j] = str[++g];
					s[j+1] = '\0';
				}
				else
				{
					printf("ERROR: Illegal character \'%c\' is not a valid caharacter. Program HALT.\n",str[g] );
					exit(1);
				}
				break;

			case '=':
				s[j] = str[g];
				s[j+1] = '\0';
				break;

			case'.':
				s[j] = str[g];
				s[j+1] = '\0';
				break;

			case'<':
				if(str[g+1] == '=')
				{
					s[j] = str[g];
					s = (char *)realloc(s, ((j+2)*sizeof(char *)));
					s[++j] = str[++g];
					s[j+1] = '\0';
				}
				else if(str[g+1] == '>')
				{
					s[j] = str[g];
					s = (char *)realloc(s, ((j+2)*sizeof(char *)));
					s[++j] = str[++g];
					s[j+1] = '\0';
				}
				else
				{
					s[j] = str[g];
					s[j+1] = '\0';
				}
				break;

				case'>':
					if(str[g+1] == '=')
					{
						s[j] = str[g];
						s = (char *)realloc(s, ((j+2)*sizeof(char *)));
						s[++j] = str[++g];
						s[j+1] = '\0';
					}
					else
					{
						s[j] = str[g];
						s[j+1] = '\0';
					}
				break;

			default:
			printf("ERROR: Illegal character \'%c\' is not a valid caharacter. Program HALT.\n",str[g] );
			exit(1);
			break;
	}
	gIndex = g+1;

}

void identifer_check(char s[])
{
	FILE *lexTable = fopen("lexicaltable.txt", "a");
	FILE *lexiList = fopen("lexicallist.txt", "a");
	//struct token* tokensReturned;
	//fprintf(lexTable, "lexeme\ttoken\n");

//while(wds != NULL){


	/*if(wds->line == NULL)
	{
		break;
	}*/

	 if(isThisLetter(s[0])==true || isThispunctuation(s[0])==true)
	{
		if(isThisReservedWord(s)==true){
			int i;
			for(i = 0; i < 31; i++)
			//while(i < 31)
			{
				if(strcmp(s, reserved_words[i])==0)
				{
					//tokensReturned = tokenInsertBack(tokensReturned,wds->line, rwNum[i]);
					//printf("s = %s   rNum = %d\n", s, rwNum[i]);
					fprintf(lexTable, "%s \t%d\n", s, rwNum[i]);
					fprintf(lexiList, "%d ", rwNum[i]);
				}
			//i++;
			}
			
		}
		else if(isThisReservedWord(s) == false)
		{
			//tokensReturned = tokenInsertBack(tokensReturned,s, identsym);
		//printf("not reserved s = %s  \n", s);

			fprintf(lexTable, "%s   %d\t\n",s, identsym);
			fprintf(lexiList, "%d %s ", identsym, s);
		}
	}

	else if(isThisInteger(s[0])==true)
	{
		//tokensReturned = tokenInsertBack(tokensReturned,s, numbersym);
		fprintf(lexTable, "%s\t%d\t\n",s,numbersym);
		fprintf(lexiList, "%d %s ", numbersym, s);
	}
	
	//wds = wds->next;
//}



fclose(lexTable);
fclose(lexiList);
//return tokensReturned;
}


int isThisLetter(char a)
{
	if((int)a > 64 && (int)a < 91)
	{
		return true;
	}
	else if((int)a > 96 && (int)a < 123)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int isThisInteger(char a)
{
	if((int)a > 47 && (int)a < 58)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int isThispunctuation(char a)
{
	if((int)a > 32 && (int)a < 48)
	{
		return true;
	}
	else if((int)a > 57 && (int)a < 65)
	{
		return true;
	}
	else if((int)a > 90 && (int)a < 97)
	{
		return true;
	}
	else if((int)a > 122 && (int)a <= 127)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// this function returns true is the word is one of the reserved otherwise false
int isThisReservedWord(char rWord[])
{
	int i;
	for( i=0; i < 31; i++)
	{
		if(strcmp(rWord, reserved_words[i])==0)
		{
			return true;
		}
	}
	return false; 
}



// reads a line from a file.
char *readLine(FILE *in)
{
	char *arr1 = (char *) NULL, *tmp = (char *) NULL;
	int c;
	int i = 0;
	arr1 = (char *)malloc(sizeof(char));

		if( feof(in))
		{
			return NULL;
		}

		while((c = getc(in)) != EOF )
		{
				arr1[i++] = c;

				tmp = (char *)realloc(arr1, ((i+1)*sizeof(char *)));

				if(tmp == NULL)
				{
					free(arr1);
					return NULL;
				}

				arr1 = tmp;
				if(c == '\n')
				{
					arr1[i-1] = '\0';
					break;
			    }
		}
		
	return arr1;
}

struct linesRead *create_linked_list_node(struct linesRead *nodePass, char *arr)
{
    struct linesRead *node = (struct linesRead*)malloc(sizeof(struct linesRead));
    struct linesRead *curr = NULL;

    node->line = arr;
    node->next = NULL;

    curr = nodePass;

    if(nodePass == NULL)
    	return node;

    while(curr->next != NULL)
    {
    	curr = curr->next;
    }

    curr->next = node;

    return nodePass;
}

void print_linked_list(struct linesRead *node)
{
	while(node != NULL){
		printf("%s\n", node->line);
		node = node->next;
	}
}



