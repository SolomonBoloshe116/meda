/* THIS IS FLEX FILE */
%{
    # include "meda_parser.h"

    extern YYSTYPE yylval;
%}
ID     [a-z][a-z_0-9]*
DIGIT  [0-9]+
%%
"+"          { return ADD;        }
"-"          { return SUB;        }
"*"          { return MULT;       }
"/"          { return FSLASH;     }
";"          { return SEMI_COLON; }
"="          { return ASSIGN;     }
"("          { return *yytext;    }
")"          { return *yytext;    }
\n           { return NEW_LINE;   }
"exit"       { exit(1);           }
"undef"      { return UNDEF_VAR;  }
"print"      { return PRINT;      }
"let"        { return LET;        }
{ID}        { yylval.identifier = strdup(yytext);
               return IDENTIFIER;
            }
{DIGIT}     { yylval.number = atoi(yytext);
               return NUMBER;
            }

[ \t]+ ;
.      ;
%%
