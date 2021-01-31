/* THIS IS FLEX FILE */
%{
    # include "meda_parser.h"

    extern YYSTYPE yylval;
%}
ID       [a-z][a-z_0-9]*
DIGIT    [0-9]+
QSTRING  \".*?\"
%%
"+"          { return ADD;        }
"-"          { return SUB;        }
"*"          { return MULT;       }
"/"          { return DIV;        }
";"          { return SEMI_COLON; }
"%"          { return MOD;        }
"="          { return ASSIGN;     }
"("          { return LBRACE;     }
")"          { return RBRACE;     }
"."          { return DOT;        }
\n           { return NEW_LINE;   }
"io"         { return IO;         }
"write"      { return WRITE;      }
"write_line" { return WRITE_LINE; }
"let"        { return LET;        }
"exit"       { exit(1);           }
"nil"        { return NIL;        }
"typeof"     { return TYPE_OF;    }
"true"      { yylval.number = 1;
               return BOOL;
            }
"false"     { yylval.number = 0;
              return BOOL;
            }
{ID}        { yylval.string = strdup(yytext);
               return IDENTIFIER;
            }
{DIGIT}     { yylval.number = atoi(yytext);
               return NUMBER;
            }
{QSTRING}   { yylval.string = strdup(yytext);
              return STRING;
            }
[ \t]+ ;
.      ;
%%
