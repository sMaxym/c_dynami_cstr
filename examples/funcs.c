#include <stdio.h>

#include "./../include/my_str_t.h"

void test_creation();
void test_fields();
void test_access_to_chars();

int main(int argc, char** argv)
{
    test_creation();
    printf("\n");
    test_fields();
    printf("\n");
    test_access_to_chars();
    printf("\n");

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
    my_str_free(&str_b);
    printf("String cleaned, so now capacity is %zu\n", my_str_capacity(&str_b));
}

void test_fields()
{
    printf("%s\n", "\tFIELDS EXAMPLES");

    my_str_t str_a;
    my_str_from_cstr(&str_a, "Max and Ihor", 100);
    printf("The properties of string 'str_a' are:\n\t-size: %zu\n\t-capacity: %zu\n",
            my_str_size(&str_a),
            my_str_capacity(&str_a));
    if (my_str_empty(&str_a)) 
    {
        printf("%s\n", "String 'str_a' is empty");
    }
    else
    {
        printf("%s\n", "String 'str_a' is not empty");
    }
}

void test_access_to_chars()
{
    printf("%s\n", "\tACCESS EXAMPLES");
    int ch; 
    my_str_t str_a;
    my_str_from_cstr(&str_a, "Ihor is", 20);
    printf("This function gets 4th char from string 'Ihor is'\n");
    printf("It is %d or letter r\n", my_str_getc(&str_a, 3));
    printf("This function will put some char to 4th position\n");
    

}