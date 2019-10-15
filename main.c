#include <stdio.h>

#include "my_str_t.h"

int main(int argc, char** argv)
{
    my_str_t a;
    my_str_create(&a, 3);
    printf("%zu %zu\n", a.capacity_m, a.size_m);
    my_str_free(&a);
    printf("%d\n", my_str_from_cstr(&a, "Max", 1));
    printf("%zu %zu\n", a.capacity_m, a.size_m);
    my_str_free(&a);

    return 0;
}