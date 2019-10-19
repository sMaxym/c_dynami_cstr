#include <stdio.h>

#include "./../include/my_str_t.h"

void test_creation();

int main(int argc, char** argv)
{
    test_creation();

    return 0;
}

void test_creation()
{
    printf("%s\n", "\tCREATION EXAMPLES");

    my_str_t str_a, str_b;
    my_str_create(&str_a, 12);
    printf("String created with capacity %zu and size %zu\n",
            my_str_capacity(&str_a),
            my_str_size(&str_a));
    my_str_from_cstr(&str_b, "message", 100);
    printf("String created with capacity %zu, size %zu and value '%s'\n",
            my_str_capacity(&str_b),
            my_str_size(&str_b),
            my_str_get_cstr(&str_b));
    my_str_empty(&str_b);
    printf("String cleaned, so now capacity is %zu\n", my_str_capacity(&str_b));
}