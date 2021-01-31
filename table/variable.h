#ifndef MEDA_VARIABLE_H
#define MEDA_VARIABLE_H

# include "literal.h"

/* from literal.h */
extern char *get_type_of_lit(meda_literal_t *literal);
extern void io_write_lit(meda_literal_t *literal, int should_i_free);
extern void io_write_line_lit(meda_literal_t *literal, int should_i_free);

typedef struct _variables_t {
    char *variable_name;
    meda_literal_t *literal;

    struct _variables_t *next;
} variable_t;

typedef struct _meda_variable_t {
    variable_t **variables;

} assign_table_t;

static assign_table_t *variable_table;
static size_t table_size = 1024;

size_t get_hash_code(char *var_name);

void init_literal_table(void);
void destroy_literal_table(void);

/* insert into table */
void insert_lit_var_into_table(char *var_name, meda_literal_t *literal);
void remove_variable(char *var_name);

/* other */
char *get_type_of_var(char *var_name);

/* io */
void io_write_identifier(char *var_name);
void io_write_line_identifier(char *var_name);

#endif // MEDA_VARIABLE_H
