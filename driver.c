/*
*Parser, Code Generator and Driver v. 1.0
*Pedro Povedo
*Sergio Perez-Aponte
*/

#include <stdio.h>
#include <string.h>
#include "lexifunctions2.h"
#include "lexifunctions2.c"
#include "compilefunctions.h"
#include "compilefunctions.c"
#include "vm.h"
#include "vm.c"


int main(int argc, char **argv)
{

		int c;
		FILE *file, *output;


		if(argc == 1){
			printf("In\n");
		}
		run_lexical();
		//printf("finish lexical\n");
		parse_program();
		//printf("finish parser\n");
		vmRUN();
		//printf("finish pm machine\n");
		if(argc == 1){
			printf("Out\n");
		}

		//Print Driver Output
		//Part 1: LexiList
		
		output = fopen("output.txt", "w");
		fprintf(output, "Lexical Analyzer output\n\n");
		file = fopen("cleanoutput.txt", "r");
		if (file) {
		    while ((c = getc(file)) != EOF){
		    	fprintf(output, "%c", c);
		    }
		}
		fclose(file);
		fprintf(output, "\n\n");
		file = fopen("lexicallist.txt", "r");
		if (file) {
		    while ((c = getc(file)) != EOF){
		    	fprintf(output, "%c", c);
		    }
		}
		fclose(file);
		//Part 2: Print the parser Output
		fprintf(output, "\n\n Parser and Code Generator output\n\n");
		fprintf(output, "No errors, program is syntactically correct.");
		file = fopen("mcode.txt", "r");
		if (file) {
				fprintf(output, "\n\n");
		    while ((c = getc(file)) != EOF){
		    	fprintf(output, "%c", c);
		    }
		    fprintf(output, "\n\n");
		}
		fclose(file);

		//Part 3:stacktrace output
		fprintf(output, "PM0 Virtual Machine\n\n");
		file = fopen("stacktrace.txt", "r");
		if (file) {
		    while ((c = getc(file)) != EOF){
		        fprintf(output, "%c", c);
		    }
		}
	    fclose(file);
	    fclose(output);

        while(argc--){
        		putchar('\n');
                if(strcmp(*argv, "-l")==0){ //print the lexeme list
                	file = fopen("lexicallist.txt", "r");
					if (file) {
					    while ((c = getc(file)) != EOF){
					        putchar(c);
					    }
					}
					    fclose(file);
                }
                else if(strcmp(*argv, "-a")==0){//print the assembly code
                	file = fopen("mcode.txt", "r");
					if (file) {
					    while ((c = getc(file)) != EOF){
					        putchar(c);
					    }
					}
					    fclose(file);
                }
                else if(strcmp(*argv, "-v")==0){//print the vm trace.
                	file = fopen("stacktrace.txt", "r");
					if (file) {
					    while ((c = getc(file)) != EOF){
					        putchar(c);
					    }
					}
					    fclose(file);
                }

                *argv++;
                }
        exit(EXIT_SUCCESS);
}