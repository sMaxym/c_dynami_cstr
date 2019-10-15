#ifndef MY_STR_T_H
#define MY_STR_T_H

#include <stdlib.h>

typedef struct
{
    size_t capacity_m;
    size_t size_m;
    char* data;
} my_str_t;

int my_str_create(my_str_t* str, size_t buf_size);
int my_str_from_cstr(my_str_t* str, const char* cstr, size_t buf_size);
void my_str_free(my_str_t* str);

#endif

