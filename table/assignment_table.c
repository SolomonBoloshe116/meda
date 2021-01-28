#include "assignment_table.h"

extern assign_table_t *assign_table;

size_t
get_hash_code(char *variable_name)
{
    size_t code = 10;
    for(size_t i = 0; variable_name[i] != '\0'; i++)
    {
        code = (code * 116) + (size_t)variable_name[i];
    }
    return (code % assign_table_size);
}

void 
init_assign_table()
{
    assign_table = ALLOCATE_ASSIGN;
    assign_table->assignments = (assign_t **)malloc(sizeof(assign_t) * assign_table_size);
    for(size_t i = 0; i < assign_table_size; i++)
    {
        assign_table->assignments[i] = NULL;
    }
}

int
make_new_assignment(char *name, int value)
{
    size_t code = get_hash_code(name);
    assign_t *assign = assign_table->assignments[code];

    if(assign == NULL)
    {
        assign = (assign_t *)malloc(sizeof(assign_t));
        assign->value = value;
        assign->variable_name = name;
        assign->next = NULL;
        assign_table->assignments[code] = assign;
        return value;
    }

    if( strcmp(assign->variable_name, name) == 0)
    {
        assign->value = value;
        return value;
    }
    while(assign)
    {
        if( strcmp(assign->variable_name, name) == 0)
        {
            assign->value = value;
            return value;
        }
        assign = assign->next;
    }
    assign_t *new_assign = (assign_t *)malloc(sizeof(assign_t));
    new_assign->value = value;
    new_assign->variable_name = name;
    new_assign->next = NULL;
    assign = new_assign;
    return value;
}

void 
release_assign(assign_t **as)
{
    if( !(*as) ) return;

    free( (*as)->variable_name );
    (*as)->variable_name = NULL;
    free( (*as));
    *as = NULL;
}

void 
destroy_assignment_table()
{
    if( !assign_table) return;

    assign_t *trail = NULL;
    for(size_t i = 0;  i < assign_table_size; i++)
    {
        if( assign_table->assignments[i] )
        {
            while(assign_table->assignments[i])
            {
                trail = assign_table->assignments[i];
                assign_table->assignments[i] = assign_table->assignments[i]->next;
                free(trail->variable_name);
                trail->variable_name = NULL;
                free(trail);
                trail = NULL;
            }
        }
    }

    free(assign_table->assignments);
    assign_table->assignments = NULL;
    free(assign_table);
    assign_table = NULL;
}

int get_identifier_value(char *var_name)
{
    size_t code = get_hash_code(var_name);
    assign_t *assign = assign_table->assignments[code];
    if(assign == NULL)
    {
        printf("Error (undefined local variable  `%s`)\n", var_name);
        exit(EXIT_FAILURE);
    }

    if( strcmp(assign->variable_name, var_name) == 0)
    {
        return assign->value;
    }

    while(assign)
    {
        if( strcmp(assign->variable_name, var_name) == 0)
        {
            break;
        }
        assign = assign->next;
    }

    if(assign == NULL)
    {
        printf("Error (undefined local variable  %s)\n", var_name);
        exit(-1);
    }
   
    return assign->value;
}

void remove_assignment(char *var_name)
{
    size_t code = get_hash_code(var_name);
    assign_t *assign = assign_table->assignments[code];
    if(assign == NULL)
    {
        printf("Error (undefined local variable  `%s`)\n", var_name);
        exit(EXIT_FAILURE);   
    }
    else
    {
        if( strcmp(assign->variable_name, var_name) == 0)
        {
            if(assign->next == NULL)
            {
                free(assign_table->assignments[code]);
                assign_table->assignments[code] = NULL;
            }
            return;
        }
        assign_t *trail = NULL;
        while(assign)
        {
            if( strcmp(assign->variable_name, var_name) == 0)
            {
                trail = assign;
                assign = assign->next;
                free(trail->variable_name);
                trail->variable_name = NULL;
                free(trail);
                trail = NULL;
                return;
            }
            assign = assign->next;
        }
    }
    if(assign == NULL)
    {
        printf("Error (undefined local variable  %s)\n", var_name);
        exit(-1);
    }
}

void print_table_values()
{
    assign_t *temp = NULL;
    for(size_t i = 0; i < assign_table_size; i++)
    {
        temp = assign_table->assignments[i];
        if(temp)
        {
            while(temp)
            {
                printf("var: %s\n", temp->variable_name);
                temp = temp->next;
            }
        }
    }
}

int make_existing_assignment(char *name, int value)
{
    size_t code = get_hash_code(name);
    assign_t *assign = assign_table->assignments[code];

    if(assign == NULL)
    {
        printf("Error: Variable %s is not defined previously\n", name);
        exit(EXIT_FAILURE);
    }

    if( strcmp(assign->variable_name, name) == 0)
    {
        assign->value = value;
        return value;
    }
    while(assign)
    {
        if( strcmp(assign->variable_name, name) == 0)
        {
            assign->value = value;
            return value;
        }
        assign = assign->next;
    }
    assign_t *new_assign = (assign_t *)malloc(sizeof(assign_t));
    new_assign->value = value;
    new_assign->variable_name = name;
    new_assign->next = NULL;
    assign = new_assign;
    return value;
}
