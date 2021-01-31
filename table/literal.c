#include "literal.h"

meda_literal_t *make_number_lit(int number)
{
  meda_literal_t *number_lit = LITERAL_ALLOCATE;
  number_lit->literal_type = NUMBER;
  number_lit->literal_value.number = number;

  return number_lit;
}

meda_literal_t *make_string_lit(char *string)
{
  meda_literal_t *string_lit = LITERAL_ALLOCATE;
  string_lit->literal_type = STRING;
  string_lit->literal_value.string = string;

  return string_lit;
}

meda_literal_t *make_bool_lit(int boolean)
{
  meda_literal_t *bool_lit = LITERAL_ALLOCATE;
  bool_lit->literal_type = BOOL;
  bool_lit->literal_value.boolean = boolean;

  return bool_lit;
}

meda_literal_t *make_nil_lit()
{
  meda_literal_t *bool_lit = LITERAL_ALLOCATE;
  bool_lit->literal_type = NIL;

  return bool_lit;
}

/* typeof(32)
   typeof("hello")
   typeof(nil)
   typeof(true)
   typeof(false)

   literal must be freed else it cause mem leak, where?
   literal: NUMBER/STRING .... , those methods allocate mem
*/
char *get_type_of_lit(meda_literal_t *literal)
{
  if(literal == NULL)
  {
    fprintf(stderr, "TypeError: Literal cant be nil\n");
    exit(EXIT_FAILURE);
  }

  char *lit_type = NULL;

  switch(literal->literal_type)
  {
    case STRING:
      lit_type = "String";
      free(literal->literal_value.string);
      literal->literal_value.string = NULL;
      break;
    case NUMBER:
      lit_type = "Number";
      break;
    case BOOL:
      lit_type = "Bool";
      break;
    case NIL:
      lit_type = "Nil";
      break;
  }
  free(literal);
  literal = NULL;

  return lit_type;
}

/* io */
void io_write_lit(meda_literal_t *literal, int should_i_free)
{
  if(literal == NULL)
  {
    printf("Error: literal is nil\n");
    exit(EXIT_FAILURE);
  }

  switch(literal->literal_type)
  {
    case STRING:
      printf("%s", literal->literal_value.string);
      if(should_i_free == 1)
      {
        free(literal->literal_value.string);
        literal->literal_value.string = NULL;
      }
      break;
    case NUMBER:
      printf("%d", literal->literal_value.number);
      break;
    case BOOL:
      printf("%s", literal->literal_value.boolean ? "true" : "false");
      break;
    case NIL:
      printf("nil");
      break;
  }
  if(should_i_free == 1)
  {
    free(literal);
    literal = NULL;
  }
}

/* print to console */
void io_write_line_lit(meda_literal_t *literal, int should_i_free)
{
  if(literal == NULL)
  {
    printf("Error: literal is nil\n");
    exit(EXIT_FAILURE);
  }

  switch(literal->literal_type)
  {
    case STRING:
      puts(literal->literal_value.string);
      if(should_i_free == 1)
      {
        free(literal->literal_value.string);
        literal->literal_value.string = NULL;
      }
      break;
    case NUMBER:
      printf("%d\n", literal->literal_value.number);
      break;
    case BOOL:
      printf("%s\n", literal->literal_value.boolean ? "true" : "false");
      break;
    case NIL:
      puts("nil");
      break;
  }
  if(should_i_free == 1)
  {
    free(literal);
    literal = NULL;
  }
}
