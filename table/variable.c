#include "variable.h"

extern assign_table_t *variable_table;
// extern size_t table_size;

size_t get_hash_code(char *var_name)
{
  size_t code = 0;
  for(size_t i = 0; var_name[i] != '\0'; i++)
  {
    code = (code + 835) * (size_t)var_name[i];
  }

  return (code % table_size);
}

void init_literal_table()
{
  variable_table = (assign_table_t *)malloc(sizeof(assign_table_t));
  variable_table->variables = (variable_t **)malloc(sizeof(variable_t) * table_size);
  printf("from init talbe: size of var: %zd\n", sizeof(table_size));

  for(size_t i = 0; i < table_size; i++)
  {
    variable_table->variables[i] = NULL;
  }
}

/* deallocate all reserved memory */
void destroy_literal_table()
{
  if(variable_table == NULL) return;

  variable_t *temp = NULL;

  for(size_t i = 0; i < table_size; i++)
  {
    while(variable_table->variables[i])
    {
      temp = variable_table->variables[i];
      variable_table->variables[i] = variable_table->variables[i]->next;
      if(temp->literal->literal_type == STRING)
      {
        free(temp->literal->literal_value.string);
      }
      free(temp->variable_name);
      free(temp->literal);
      free(temp);
      temp = NULL;
    }
  }

  printf("size of variables: %zd\n", sizeof(variable_table->variables));
  free(variable_table->variables);
  variable_table->variables = NULL;
  free(variable_table);
  variable_table = NULL;
  puts("finished");
}

/* insert into table */
void insert_lit_var_into_table(char *var_name, meda_literal_t *literal)
{
  size_t code = get_hash_code(var_name);
  variable_t *var = variable_table->variables[code];
  int flag = 0;

  if(var == NULL)
  {
    // flag = 0;
    goto INSERT_INTO_TABLE;
  }
  else
  {
    /* if var already exist */
    if( strcmp(var->variable_name, var_name) == 0)
    {
      goto EXIST_ERROR;
    }
    else
    {
      var = var->next;
      while(var)
      {
        /* if var already exist */
        if( strcmp(var->variable_name, var_name) == 0)
        {
          goto EXIST_ERROR;
        }
        var = var->next;
      }
      if(var == NULL)
      {
        flag = 1; // not at the head of list
        goto INSERT_INTO_TABLE;
      }
    }
  }

  EXIST_ERROR:
  {
    fprintf(stderr, "SyntaxError, (variable %s is previously defined, so remove let)\n", var_name);
    exit(EXIT_FAILURE);
  }

  INSERT_INTO_TABLE:
  {
    var = (variable_t *)malloc(sizeof(variable_t));
    var->variable_name = var_name;
    var->literal = literal;
    var->next = 0;
    if(flag == 0)
    {
      variable_table->variables[code] = var;
    }
    /*
    else
    {
      // does not change
    }
    */
  }
}

void remove_variable(char *var_name)
{
    size_t code = get_hash_code(var_name);
    variable_t *var = variable_table->variables[code];
    variable_t *temp = NULL;

    if(var == NULL)
    {
        goto ERROR;
    }
    else
    {
        if( strcmp(var->variable_name, var_name) == 0)
        {
            goto DELETE_VAR;
        }
        else
        {
            /* move to the next, bacuase the current is already checked */
            var = var->next;
            while(var)
            {
                if( strcmp(var->variable_name, var_name) == 0)
                {
                    goto DELETE_VAR;
                }
            }
            if(var == NULL)
            {
                goto ERROR;
            }
        }
    }

    ERROR:
    {
        fprintf(stderr, "Error (%s is undefined)\n", var_name);
        exit(EXIT_FAILURE);
    }

    DELETE_VAR:
    {
        temp = var;
        var = var->next;
        if(temp->literal->literal_type == STRING)
        {
            free(temp->literal->literal_value.string);
        }
        free(temp->literal);
        free(temp->variable_name);
        free(temp);
        temp = NULL;
    }
}

/* other */
char *get_type_of_var(char *var_name)
{
  size_t code = get_hash_code(var_name);
  variable_t *var = variable_table->variables[code];
  if(var == NULL)
  {
    goto ERROR;
  }
  else
  {
    if( strcmp(var->variable_name, var_name) == 0)
    {
      goto RETURN_VAR_TYPE;
    }
    else
    {
      var = var->next;
      while(var)
      {
        if( strcmp(var->variable_name, var_name) == 0)
        {
          goto RETURN_VAR_TYPE;
        }
      }
      if(var == NULL)
      {
        goto ERROR;
      }
    }
  }

  ERROR:
  {
    fprintf(stderr, "Error (%s is undefined)\n", var_name);
    exit(EXIT_FAILURE);
  }

  RETURN_VAR_TYPE:
  {
    return get_type_of_lit(var->literal);
  }
}

/* io */
void io_write_identifier(char *var_name)
{
  size_t code = get_hash_code(var_name);
  variable_t *var = variable_table->variables[code];
  if(var == NULL)
  {
    goto ERROR;
  }
  else
  {
    if( strcmp(var->variable_name, var_name) == 0)
    {
      goto IO_WRITE;
    }
    else
    {
      var = var->next;
      while(var)
      {
        if( strcmp(var->variable_name, var_name) == 0)
        {
          goto IO_WRITE;
        }
        var = var->next;
      }
      if(var == NULL)
      {
        goto ERROR;
      }
    }
  }

  ERROR:
  {
    fprintf(stderr, "Error (%s is undefined)\n", var_name);
    exit(EXIT_FAILURE);
  }

  IO_WRITE:
  {
    io_write_lit(var->literal, 0);   
  }
}

void io_write_line_identifier(char *var_name)
{
  size_t code = get_hash_code(var_name);
  variable_t *var = variable_table->variables[code];
  if(var == NULL)
  {
    goto ERROR;
  }
  else
  {
    if( strcmp(var->variable_name, var_name) == 0)
    {
      goto IO_WRITE;
    }
    else
    {
      var = var->next;
      while(var)
      {
        if( strcmp(var->variable_name, var_name) == 0)
        {
          goto IO_WRITE;
        }
        var = var->next;
      }
      if(var == NULL)
      {
        goto ERROR;
      }
    }
  }

  ERROR:
  {
    fprintf(stderr, "Error (%s is undefined)\n", var_name);
    exit(EXIT_FAILURE);
  }

  IO_WRITE:
  {
    /* dont free the literal */
    io_write_line_lit(var->literal, 0);
  }
}
