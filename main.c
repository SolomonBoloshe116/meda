#include "meda_parser.h"
#include "./table/assignment_table.h"

extern int yylex(void);
extern int yyparse(void);
// extern FILE *yyin;

int main(int argc, char *argv[])
{
    yyparse();
    destroy_assignment_table();

    return 0;
}
