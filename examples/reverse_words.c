#include <stdio.h>

#include "./../include/my_str_t.h"

int reflect(my_str_t* str, my_str_t* reversed, size_t from, size_t to);


int main(int argc, char** argv)
{
    my_str_t data, reversed, buffer;
    size_t index_from = 0, index_to;
    
    my_str_create(&data, 10);
    my_str_create(&reversed, 10);
    my_str_create(&buffer, 20);
    
    FILE* fs;
            
    fs = fopen(argv[1], "r");
    if(my_str_read_file(&data, fs))
    {
       return -1; 
    }
    fclose(fs);

    index_to = my_str_find_c(&data, ' ', index_from);
    while (index_to != -1)
    {
        reflect(&data, &buffer, index_from, index_to);
        my_str_append(&reversed, &buffer);
        my_str_append_cstr(&reversed, " ");
        index_from = index_to + 1;
                printf("%zu\n", index_from);

        index_to = my_str_find_c(&data, ' ', index_from);
    }

    reflect(&data, &buffer, index_from, my_str_size(&data));
    my_str_append(&reversed, &buffer);

    return 0;
}

int reflect(my_str_t* str, my_str_t* reversed, size_t from, size_t to)
{
    char symb;
    for (size_t i = from; i < to; i++)
    {
        symb = (char)my_str_getc(str, i);
        my_str_insert_c(reversed, symb, 0);
    }
    return 0;
}