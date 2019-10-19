#include <stdio.h>

#include "./../include/my_str_t.h"

void test_creation();
void test_fields();
void test_access_to_chars();
void test_string_modify();
void test_string_size();
void test_search_and_compare();
void test_input_output(char * file_mame);

int main(int argc, char** argv)
{
    test_creation();
    printf("\n");
    test_fields();
    printf("\n");
    test_access_to_chars();
    printf("\n");
    test_string_modify();
    printf("\n");
    test_string_size();
    printf("\n");
    test_search_and_compare();
    printf("\n");
    test_input_output(argv[1]);
    printf("\n");

    return 0;
}

void test_creation()
{
    printf("%s\n", "\tCREATION EXAMPLES");

    my_str_t str_a, str_b;
    my_str_create(&str_a, 12);
    my_str_create(&str_b, 12);
    printf("String created with capacity %zu and size %zu\n",
            my_str_capacity(&str_a),
            my_str_size(&str_a));
    my_str_from_cstr(&str_b, "message", 12);
    printf("String created with capacity %zu, size %zu and value '%s'\n",
            my_str_capacity(&str_b),
            my_str_size(&str_b),
            my_str_get_cstr(&str_b));
    my_str_free(&str_b);
    printf("String cleaned, so now capacity is %zu\n", my_str_capacity(&str_b));
    my_str_free(&str_a);
    my_str_free(&str_b);
}

void test_fields()
{
    printf("%s\n", "\tFIELDS EXAMPLES");

    my_str_t str_a;
    my_str_create(&str_a, 12);
    my_str_from_cstr(&str_a, "Max and Ihor", 12);
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
    my_str_free(&str_a);
}

void test_access_to_chars()
{
    printf("%s\n", "\tACCESS EXAMPLES");
    int ch; 
    my_str_t str_a;
    my_str_create(&str_a, 12);
    my_str_from_cstr(&str_a, "Ihor is", 12);
    printf("This function gets 4th char from string 'Ihor is'\n");
    printf("It is %d or letter r\n", my_str_getc(&str_a, 3));
    printf("This function will put  W to 4th position\n");
    printf("Before: %s\n", my_str_get_cstr(&str_a));
    my_str_putc(&str_a, 4, 'W');
    printf("After: %s\n", my_str_get_cstr(&str_a));
    my_str_free(&str_a);
}

void test_string_modify()
{
    printf("%s\n", "\tSTRING MODIFY");
    my_str_t str_a , str_b;
    my_str_create(&str_a, 12);
    my_str_create(&str_b, 4);
    my_str_from_cstr(&str_a, "Ihor and Max", 20);
    char ch = 'W';
    printf("This function will put  W to the end of the string\n");
    printf("Before: %s\n", my_str_get_cstr(&str_a));
    my_str_pushback(&str_a, 'W');
    printf("After: %s\n", my_str_get_cstr(&str_a));
    printf("This function will remove W from the end of the string\n");
    printf("Before: %s\n", my_str_get_cstr(&str_a));
    my_str_popback(&str_a);
    printf("After: %s\n", my_str_get_cstr(&str_a));
    printf("This function will clear string\n");
    printf("Before: %u\n", str_a.size_m);
    my_str_clear(&str_a);
    printf("After: %u\n", str_a.size_m);
    printf("This function will put on 3rd position W and will not replace char\n");
    my_str_from_cstr(&str_a, "Ihor and Max", 20);
    printf("Before: %s\n", my_str_get_cstr(&str_a));
    my_str_insert_c(&str_a, 'W', 3);
    printf("After: %s\n",  my_str_get_cstr(&str_a));
    my_str_clear(&str_a);
    printf("This function will put another string to 3rd position\n");
    my_str_from_cstr(&str_a, "Ihor and Max", 20);
    my_str_from_cstr(&str_b, "POK", 5);
    printf("Before: %s\n", my_str_get_cstr(&str_a));
    my_str_insert(&str_a, &str_b, 3);
    printf("After: %s\n",  my_str_get_cstr(&str_a));
    my_str_clear(&str_a);
    my_str_clear(&str_b);
    char str_c[3] = {"HI"};
    printf("This function will put on 3rd position Cstring\n");
    my_str_from_cstr(&str_a, "Ihor and Max", 20);
    printf("Before: %s\n", my_str_get_cstr(&str_a));
    my_str_insert_cstr(&str_a, str_c , 3);
    printf("After: %s\n",  my_str_get_cstr(&str_a));
    my_str_clear(&str_a);
    my_str_clear(&str_b);
    printf("This function will put another string to the end of the string\n");
    my_str_from_cstr(&str_a, "Ihor and Max", 20);
    my_str_from_cstr(&str_b, "POK", 5);
    printf("Before: %s\n", my_str_get_cstr(&str_a));
    my_str_append(&str_a, &str_b);
    printf("After: %s\n",  my_str_get_cstr(&str_a));
    my_str_clear(&str_a);
    my_str_clear(&str_b);
    printf("This function will put on Cstring to the end\n");
    my_str_from_cstr(&str_a, "Ihor and Max", 20);
    printf("Before: %s\n", my_str_get_cstr(&str_a));
    my_str_append_cstr(&str_a, str_c);
    printf("After: %s\n",  my_str_get_cstr(&str_a));
    my_str_clear(&str_a);
    my_str_clear(&str_b);
    printf("This function will copy substring to another\n");
    my_str_from_cstr(&str_a, "Ihor and Max", 20);
    printf("Before: %s\n", my_str_get_cstr(&str_b));
    my_str_substr(&str_a, &str_b, 1, 4);
    printf("After: %s\n",  my_str_get_cstr(&str_b));
    my_str_clear(&str_a);
    my_str_clear(&str_b);
    char str_d[8] = {};
    printf("This function will copy C substring to another\n");
    my_str_from_cstr(&str_a, "Ihor and Max", 20);
    printf("Before: %s\n", str_d);
    my_str_substr_cstr(&str_a, str_d, 1, 4);
    printf("After: %s\n",  str_d);
    my_str_free(&str_a);
    my_str_free(&str_b);
}

void test_string_size()
{
    printf("%s\n", "\tSIZE EXAMPLES");
    my_str_t str_a;
    my_str_create(&str_a, 12);
    my_str_from_cstr(&str_a, "Ihor and Max", 20);
    printf("This function will increase buffer\n");
    printf("Before: %u\n", str_a.capacity_m);
    my_str_reserve(&str_a, str_a.capacity_m * 2);
    printf("After: %u\n",  str_a.capacity_m);
    printf("This function will diminish buffer to normal size\n");
    printf("Before: %u\n", str_a.capacity_m);
    my_str_shrink_to_fit(&str_a);
    printf("After: %u\n",  str_a.capacity_m);
    printf("This function will increase size of str and new symbols will be same\n");
    printf("Before: %u , %s\n", str_a.size_m, my_str_get_cstr(&str_a));
    my_str_resize(&str_a, 15, 'W');
    printf("After: %u, %s\n",  str_a.size_m, my_str_get_cstr(&str_a));
    my_str_free(&str_a);
}
int predicate(int symb)
{
    if (symb == 'a')
    {
        return 1;
    }
    return 0;
}

void test_search_and_compare()
{
    printf("%s\n", "\tSEARCH AND COMPARE EXAMPLES");
    my_str_t str_a, str_b;
    my_str_create(&str_a, 12);
     my_str_create(&str_b, 4);
    char str_c[8] = {"Hi"};
    my_str_from_cstr(&str_a, "Ihor and Max", 20);
    my_str_from_cstr(&str_b, "Ihor", 20);
    printf("This function will find position of substring\n");
    printf("String 1: %s\n", my_str_get_cstr(&str_a));
    printf("String 2: %s\n", my_str_get_cstr(&str_b));
    printf("Position: %u\n",  my_str_find(&str_a, &str_b, 0));
    printf("This function compare strings\n");
    printf("String 1: %s\n", my_str_get_cstr(&str_a));
    printf("String 2: %s\n", my_str_get_cstr(&str_b));
    printf("Position: %d\n",  my_str_cmp(&str_a, &str_b));
    printf("This function compare string and C-string\n");
    printf("String 1: %s\n", my_str_get_cstr(&str_a));
    printf("String 2: %s\n", str_c);
    printf("Position: %d\n",  my_str_cmp(&str_a, str_c));
    printf("This function will find position of char\n");
    printf("String 1: %s\n", my_str_get_cstr(&str_a));
    printf("Position: %u\n",  my_str_find_c(&str_a, 'M', 2));
    printf("This function find char by other function\n");
    printf("String 1: %s\n", my_str_get_cstr(&str_a));
    printf("Position: %u\n",  my_str_find_if(&str_a, predicate));

    my_str_free(&str_a);
}

void test_input_output(char * file_mame)
{
    my_str_t str_a;
    my_str_create(&str_a, 12);
    FILE* fs;
    fs = fopen(file_mame, "r");
    my_str_read_file(&str_a, fs);
    fclose(fs);
    printf("%s\n", my_str_get_cstr(&str_a));
}