#ifndef MEDA_LITERAL_H
#define MEDA_LITERAL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "../meda_parser.h"

typedef struct _meda_literal_t {
    int literal_type;
    union {
        char *string;
        int   number;
        int   boolean;
    } literal_value;

} meda_literal_t;

#define LITERAL_ALLOCATE (meda_literal_t *)malloc(sizeof(meda_literal_t))

meda_literal_t *make_number_lit(int number);
meda_literal_t *make_string_lit(char *string);
meda_literal_t *make_bool_lit(int boolean);
meda_literal_t *make_nil_lit(void);

char *get_type_of_lit(meda_literal_t *literal);

/* io */
void io_write_lit(meda_literal_t *literal, int should_i_free);
void io_write_line_lit(meda_literal_t *literal, int should_i_free);

#endif // MEDA_LITERAL_H
