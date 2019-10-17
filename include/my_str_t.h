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

size_t my_str_size(const my_str_t* str);
size_t my_str_capacity(const my_str_t* str);
int my_str_empty(const my_str_t* str);

int my_str_pushback(my_str_t* str, char c);
int my_str_popback(my_str_t* str);
void my_str_clear(my_str_t* str);
int my_str_insert_c(my_str_t* str, char c, size_t pos);
int my_str_insert(my_str_t* str, const my_str_t* from, size_t pos);

int my_str_getc(const my_str_t* str, size_t index);
int my_str_putc(my_str_t* str, size_t index, char c);
const char* my_str_get_cstr(my_str_t* str);

int my_str_reserve(my_str_t* str, size_t buf_size);
int my_str_shrink_to_fit(my_str_t* str);
int my_str_resize(my_str_t* str, size_t new_size, char sym);


#endif

