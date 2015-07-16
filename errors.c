
void print_errors(int gIndex, int error, char s[])
{
    printf("ERROR #%d at the token index %d: ",error, gIndex);
  
    switch(error)
    {
      case 1:
        printf("%s", error_statement[error]);
      break;
      
      case 2:
        printf("%s", error_statement[error]);
      break;
      
      case 3:
        printf("%s", error_statement[error]);
      break;
      
      case 4:
       printf("%s", error_statement[error]);
      break;
      
      case 5:
       printf("%s", error_statement[error]);
      break;
      
      case 6:
        printf("%s", error_statement[error]);
      break;
      
      case 7:
        printf("%s", error_statement[error]);
      break;
      
      case 8:
        printf("%s", error_statement[error]);
      break;
      
      case 9:
        printf("%s", error_statement[error]);
      break;
      
      case 10:
        printf("%s", error_statement[error]);
      break;
      
      case 11:
        printf("Undeclared identifier \'%s\'.", s);
      break;
      
      case 12:
        printf("%s", error_statement[error]);
      break;
      
      case 13:
        printf("%s", error_statement[error]);
      break;
      
      case 14:
        printf("%s", error_statement[error]);
      break;
      
      case 15:
        printf("%s", error_statement[error]);
      break;
      
      case 16:
        printf("%s", error_statement[error]);
      break;
      
      case 17:
        printf("%s", error_statement[error]);
      break;
      
      case 18:
        printf("%s", error_statement[error]);
      break;
      
      case 19:
        printf("%s", error_statement[error]);
      break;
      
      case 20:
        printf("%s", error_statement[error]);
      break;
      
      case 21:
        printf("%s", error_statement[error]);
      break;
      
      case 22:
        printf("%s", error_statement[error]);
      break;
      
      case 23:
        printf("The preceding factor can not begin with this symbol \'%c\'.", s[0]);
      break;
      
      case 24:
        printf("An expression  can not begin with the symbol \'%c\'.", s[0]);
      break;
      
      case 25:
        printf("The number %s is larger than the allow length of %d.", s, 5); /// need works
      break;

      case 26:
        printf("%s", error_statement[error]);
      break;

      case 27:
        printf("%s", error_statement[error]);
      break;

      case 28:
        printf("Duplicate identifier: \'%s\' is already defined.", s);
      break;
      
      default:
        printf("FATAL\n");
      break;
    }
    printf("\nThe program: Compiler has EXIT.\n");
    exit(1);
}