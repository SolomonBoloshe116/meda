/* THIS IS YACC FILE*/
%{
  #include "./table/literal.h"
  #include "./table/variable.h"

  #include <stdio.h>

  extern int yylex(void);
  extern void yyerror(const char *error_message);
%}

%union {
  int number;
  char *string;

  struct _meda_literal_t *literal_t;
  struct _meda_call_t     *call_t;
}
%define parse.error detailed

/* tokens without types */

/* operators */
%token ADD
%token SUB
%token MULT
%token DIV
%token MOD

/* other tokens */
%token IO
%token WRITE
%token WRITE_LINE
%token LET
%token SEMI_COLON
%token ASSIGN
%token NEW_LINE
%token UNDEF_VAR
%token LBRACE
%token RBRACE
%token DOT
%token TYPE_OF
%token NIL

/* tokens with types */
%token <number> NUMBER
%token <string> IDENTIFIER
%token <string> STRING
%token <number> BOOL

/* types */
%type <number> math_fact math_term math_expr
%type <string> type_of
%type <literal_t> literal

%start prog
%%
prog: 
    %empty
  | prog line
  ;

/* void */
line:
    NEW_LINE
  | expr NEW_LINE
  | error NEW_LINE  { yyerrok; }
  ;

/* void */
expr:
    io_call
  | assign
  ;

/* void 
update_var:
    IDENTIFIER ASSIGN literal              {   }
  | IDENTIFIER ASSIGN type_of              {   }
  | IDENTIFIER ASSIGN math_expr            {   }
  ;
*/
/* void */
assign:
    LET IDENTIFIER ASSIGN literal   { insert_lit_var_into_table($2, $4);    }
  ;

/* number */
math_expr:
    math_expr ADD math_term         { $$ = $1 + $3; }
  | math_expr SUB math_term         { $$ = $1 - $3; }
  | math_term
  ;

/* number */
math_term:
    math_term DIV  math_fact
    {
        if($3 == 0)
        {
          fprintf(stderr, "ZeroDivisionError (%d divided by 0)\n", $1);
          exit(EXIT_FAILURE);
        }
        else
        {
          $$ = $1 / $3;
        }
    }
  | math_term MULT math_fact         { $$ = $1 * $3; }
  | math_term MOD  math_fact
    {
      if($3 == 0)
      {
        fprintf(stderr, "ZeroDivisionError (%d divided by 0)\n", $1);
        exit(EXIT_FAILURE);
      }
      else
      {
        $$ = $1 % $3;
      }
    }
  | math_fact
  ;

/* number */
math_fact:
    NUMBER
  /*| IDENTIFIER                     { $$ = get_identifier_value($1); }  */
  | LBRACE math_expr RBRACE        { $$ = $2;                       }
  ;

/* void */
io_call: 
    /* io.write(call) */
    IO DOT WRITE LBRACE literal RBRACE         { io_write_lit($5, 1);          }
    /* io.write_line(call) */
  | IO DOT WRITE_LINE LBRACE literal RBRACE    { io_write_line_lit($5, 1);     }
    /* io.write(typeof(32)) */
  | IO DOT WRITE LBRACE IDENTIFIER RBRACE      { io_write_identifier($5);      }
  /* io.write_line(a) */
  | IO DOT WRITE_LINE LBRACE IDENTIFIER RBRACE { io_write_line_identifier($5); }
  ;

/* char* */
type_of:
    TYPE_OF LBRACE literal RBRACE    { $$ = get_type_of_lit($3); }
  | TYPE_OF LBRACE IDENTIFIER RBRACE { $$ = get_type_of_var($3); }
  ;

/* literal_t*/
literal:
    STRING        { $$ = make_string_lit($1); }
  | BOOL          { $$ = make_bool_lit($1);   }
  | NIL           { $$ = make_nil_lit();      }
  | math_expr     { $$ = make_number_lit($1); }
  | type_of       { $$ = make_string_lit($1); }
  ;

%%

void
yyerror (const char *msg)
{
  printf("Error: %s\n", msg);
  exit(EXIT_FAILURE);
}
