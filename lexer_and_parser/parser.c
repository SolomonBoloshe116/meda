%{
    #include "./table/assignment_table.h"
    #include <stdio.h>

    extern int yylex(void);
    extern void yyerror(const char *error_message);
%}

%union {
    int number;
    char *identifier;

    // struct assign_t *assing_ptr;
}
%define parse.error detailed

/* tokens without types */
%token ADD   
%token SUB   
%token MULT 
%token FSLASH
%token SEMI_COLON
%token ASSIGN
%token NEW_LINE
%token UNDEF_VAR
%token PRINT
%token LET
/* tokens with types */
%token <number> NUMBER
%token <identifier> IDENTIFIER

/* types */
%type <number> term expr fact
%type <number> assign

%start prog

%%
prog: 
    %empty
  | prog line
  ;

line: NEW_LINE
     | expr NEW_LINE
     | assign NEW_LINE line
     | error NEW_LINE  { yyerrok; }
     | PRINT expr
      {
        printf("=> %d\n", $2);
      }
     ;

/* int */
assign:
       /* char[]     =     int*/
        LET IDENTIFIER ASSIGN expr { $$ = make_new_assignment($2, $4); }
      | IDENTIFIER ASSIGN expr { $$ = make_existing_assignment($1, $3); }
      | UNDEF_VAR IDENTIFIER  { remove_assignment($2); }
      ;

/* int */
expr:
      /* int + int */
      expr ADD term { $$ = $1 + $3; }
    | expr SUB term { $$ = $1 - $3; }
    | term
    ;

term: term MULT   fact  { $$ = $1 * $3; }
    | term FSLASH fact
      { 
        if( $3 == 0)
        {
            printf("Error: ZerroDivisionError (%d by 0)\n", $1);
            exit(-1);
        }
        else
        {
            $$ = $1 / $3;
        }
      }
    | fact
    ;

fact:
      NUMBER
    | IDENTIFIER   { $$ = get_identifier_value($1); }
    | '(' expr ')' { $$ = $2; }
    ;
%%

void
yyerror (const char *msg)
{
   printf("Error: %s\n", msg);
   exit(EXIT_FAILURE);
}
