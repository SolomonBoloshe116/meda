#ifndef ASSIGNMENT_TABLE_H
#define ASSIGNMENT_TABLE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct assign_t {
    char *variable_name;
    int value;

   struct assign_t *next;
} assign_t;

typedef struct _assign_table_t{
    assign_t **assignments;
} assign_table_t;

#define ALLOCATE_ASSIGN (assign_table_t *)malloc(sizeof(assign_table_t))

static size_t assign_table_size     = 100;
static assign_table_t *assign_table = NULL;

size_t    get_hash_code(char *variable_name);
void      init_assign_table(void) __attribute ((constructor));
void      release_assign(assign_t **assign);
void      destroy_assignment_table(void) ;
void      remove_assignment(char *var_name);

void       print_table_values(void) ;

int make_existing_assignment(char *var_name, int value);
int make_new_assignment(char *variable_name, int value);
int get_identifier_value(char *var_name);

#endif // ASSIGNMENT_TABLE_H
