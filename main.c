#include "meda_parser.h"
#include "./table/variable.h"
#include "./table/literal.h"
#include <stdio.h>
#include <errno.h>

extern int yylex(void);
extern int yyparse(void);
extern FILE *yyin;

extern void destroy_literal_table(void);

void handle_with_input(char *file_name);
void handle_without_input(void);

int main(int argc, char *argv[])
{
    init_literal_table();
    atexit(destroy_literal_table);

    switch(argc)
    {
        case 1:
           handle_without_input();
           break;
        case 2:
           handle_with_input(argv[1]);
           break;
        default:
           fprintf(stderr, "Please don\'t mess with too many arguments\n");
    }

    return 0;
}

void handle_with_input(char *file_name)
{
    yyin = fopen(file_name, "r");
    if(!yyin)
    {
        perror("Error:");
        exit(EXIT_FAILURE);
    }
    yyparse();
    fclose(yyin);
    destroy_literal_table();
}

void handle_without_input()
{
    yyparse();
}
