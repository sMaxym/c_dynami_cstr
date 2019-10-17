#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    size_t capacity_m;
    size_t size_m;
    char* data;
} my_str_t;


//!===========================================================================
//! Створення та знищення стрічки.
//!===========================================================================

static size_t my_str_len(const char* str)
{
    size_t index = 0;
    while(str[index++] != '\0');
    return index - 1;
}

int my_str_create(my_str_t* str, size_t buf_size)
{
    str->capacity_m = buf_size;
    str->size_m = 0;
    int allocation_size = sizeof(char*) * str->capacity_m + 1;
    str->data = (char*) malloc(allocation_size);
    if (!str->data)
    {
        return -1;
    }
    return 0;
}


// todo: remake normally
int my_str_from_cstr(my_str_t* str, const char* cstr, size_t buf_size)
{
    size_t cstr_size = my_str_len(cstr);
    if (!buf_size)
    {
        buf_size = cstr_size;
    }
    if (buf_size < cstr_size)
    {
        return -1;
    }

    my_str_create(str, buf_size);
    memcpy(str->data, cstr, cstr_size);
    str->size_m = cstr_size;
    if (!str->data)
    {
        return -2;
    }
    return 0;
}

void my_str_free(my_str_t* str)
{   
    str->capacity_m = 0;
    str->size_m = 0;
    free(str->data);
}


//!============================================================================
//! Інформація про стрічку
//!============================================================================

//! Повертає розмір стрічки.
//! Для нульового вказівника -- 0.
size_t my_str_size(const my_str_t* str)
{
    if (!(str->size_m))
    {
        return -1;
    }
    else
    {
        return str->size_m;
    }
}

//! Повертає розмір буфера.
//! Для нульового вказівника -- 0.
size_t my_str_capacity(const my_str_t* str)
{
    if (!(str->capacity_m))
    {
        return -1;
    }
    else
    {
        return str->capacity_m;
    }
}

//! Повертає булеве значення, чи стрічка порожня:
int my_str_empty(const my_str_t* str)
{
    if (str->size_m == 0){
        return 1;
    }
    else
    {
        return -1;
    }
}

//!===========================================================================
//! Доступ до символів стрічки
//!===========================================================================

//! Повертає символ у вказаній позиції, або -1, якщо вихід за межі стрічки,
//! включаючи переданий нульовий вказівник.
//! Тому, власне, int а не char
int my_str_getc(const my_str_t* str, size_t index)
{
    if (index >= str->size_m || index < 0 || !str) 
    {
        return -1;
    }

    return (int) *(str->data + index);
}

//! Записує символ у вказану позиції (заміняючи той, що там був),
//! Повертає 0, якщо позиція в межах стрічки,
//! Поветає -1, не змінюючи її вмісту, якщо ні.
int my_str_putc(my_str_t* str, size_t index, char c)
{
    if (index >= str->size_m || index < 0)
    {
        return -1;
    }
    *(str->data + index) = c;
    return 0;
}

//! Повернути вказівник на С-стрічку, еквівалентну str.
//! Вважатимемо, що змінювати цю С-стрічку заборонено.
//! Вважатимемо, що як тільки my_str_t змінено, цей вказівник
//! може стати некоректним.
//! Якщо в буфері було зарезервовано на байт більше за макс. розмір, можна
//! просто додати нульовий символ в кінці та повернути вказівник data.
const char* my_str_get_cstr(my_str_t* str)
{
    char* cstr = str->data;
    *(cstr + str->size_m) = '\0';
    return cstr;
}

//!===========================================================================
//! Модифікації стрічки, що змінюють її розмір і можуть викликати реалокацію.
//!===========================================================================
//! Якщо буфер недостатній -- ці функції збільшують його,
//! викликом my_str_reserve().
//! Розумним є буфер кожного разу збільшувати в 1.8-2 рази.
//! ==========================================================================

//! Додає символ в кінець.
//! Повертає 0, якщо успішно,
//! -1 -- якщо передано нульовий вказівник,
//! -2 -- помилка виділення додаткової пам'яті.
int my_str_pushback(my_str_t* str, char c)
{
    int pointer;
    if (!str)
    {
        return -1; 
    }
    if (str->size_m < str->capacity_m)
    {
        *(str->data + str->size_m) = c;
        str->size_m++;
    }
    else{
        pointer = my_str_reserve(str,  2 * str->size_m);
        if (pointer < 0)
        {
            return -2;
        }
        *(str->data + str->size_m) = c;
        str->size_m++;
    }
    return 0;
}

//! Викидає символ з кінця.
//! Повертає його, якщо успішно,
//! -1 -- якщо передано нульовий вказівник,
//! -2 -- якщо стрічка порожня.
int my_str_popback(my_str_t* str)
{
    int pointer = my_str_empty(str);
    if (!str)
    {
        return -1;
    }
    if (pointer == 1)
    {
        return -2;
    }
    char c = *(str->data + str->size_m - 1);
    str->size_m--; 
    return c;
}

//! Копіює стрічку. Якщо reserve == true,
//! то із тим же розміром буферу, що й вихідна,
//! інакше -- із буфером мінімального достатнього розміру.
//! (Старий вміст стрічки перед тим звільняє, за потреби).
//! Повертає 0, якщо успішно, різні від'ємні числа для діагностики
//! проблеми некоректних аргументів.
int my_str_copy(const my_str_t* from,  my_str_t* to, int reserve);

//! Очищає стрічку -- робить її порожньою. Складність має бути О(1).
//! Уточнення (чомусь ця ф-ція викликала багато непорозумінь):
//! стрічка продовжує існувати, буфер той самий, того ж розміру, що був,
//! лише містить 0 символів -- єдине, що вона робить, це size_m = 0.
void my_str_clear(my_str_t* str)
{
    str->size_m = 0;
}

//! Вставити символ у стрічку в заданій позиції, змістивши решту символів праворуч.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_insert_c(my_str_t* str, char c, size_t pos)
{
    int pointer;
    if (str->size_m < str->capacity_m)
    {
        for(size_t i = str->size_m - 1; i >= pos; i = i - 1)
        {
            *(str->data + i + 1) = *(str->data + i);
        }
        *(str->data + pos) = c;
        str->size_m ++;
    }
    else
    {
        pointer = my_str_reserve(str, str->size_m * 2);
        if (pointer == -1)
        {
            return -1;
        }
        for(size_t i = str->size_m - 1; i > pos; i = i - 1)
        {
            *(str->data + i + 1) = *(str->data + i);
        }
        *(str->data + pos) = c;
        str->size_m ++;
    }
    return 0;
}

//! Вставити стрічку в заданій позиції, змістивши решту символів праворуч.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_insert(my_str_t* str, const my_str_t* from, size_t pos)
{
    int pointer;
    if (str->size_m + from->size_m >= str->capacity_m)
    {
        pointer = my_str_reserve(str, (str->size_m + from->size_m)* 2);
        if (pointer == -1)
        {
            return -1;
        }
    }
    for(size_t i = str->size_m - 1; i>=pos; i=i-1)
    {
        *(str->data + i + from->size_m) = *(str->data + i);
    }
    for(size_t j = 0; j < from->size_m; j++)
    {
        *(str->data + j + pos) = *(from->data + j);
    }
    str->size_m += from->size_m;
    return 0;
}

//! Вставити C-стрічку в заданій позиції, змістивши решту символів праворуч.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_insert_cstr(my_str_t* str, const char* from, size_t pos);

//! Додати стрічку в кінець.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_append(my_str_t* str, const my_str_t* from);
//! Додати С-стрічку в кінець.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_append_cstr(my_str_t* str, const char* from);

//! Скопіювати підстрічку, із beg включно, по end не включно ([beg, end)).
//! Якщо end за межами початкової стрічки -- це не помилка, копіювати всі
//! символи до кінця. beg має бути в її межах -- якщо beg>size, це помилка.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_substr(const my_str_t* from, my_str_t* to, size_t beg, size_t end);

//! C-string варіант my_str_substr().
//! Вважати, що в цільовій С-стрічці достатньо місц.
int my_str_substr_cstr(const my_str_t* from, char* to, size_t beg, size_t end);

//!===========================================================================
//! Маніпуляції розміром стрічки
//!===========================================================================

//! Збільшує буфер стрічки, із збереженням вмісту,
//! якщо новий розмір більший за попередній,
//! не робить нічого, якщо менший або рівний.
//! (Як показує практика, це -- корисний підхід).
//! Для збільшення виділяє новий буфер, копіює вміст
//! стрічки (size_m символів -- немає сенсу копіювати
//! решту буфера) із старого буфера та звільняє його.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_reserve(my_str_t* str, size_t buf_size)
{
    if (str->capacity_m >= buf_size)
    {
        return 0;
    }

    size_t allocation_size = sizeof(char) * buf_size;
    char* enlarged_buf = (char*) malloc(allocation_size + 1);
    if (!enlarged_buf)
    {
        return -1;
    }
    memcpy(enlarged_buf, str->data, str->size_m);
    free(str->data);
    str->data = enlarged_buf;
    str->capacity_m = buf_size;
    return 0;
}

//! Робить буфер розміром, рівний необхідному:
//! так, щоб capacity_m == size_t. Єдиний "офіційний"
//! спосіб зменшити фактичний розмір буфера.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_shrink_to_fit(my_str_t* str)
{
    size_t allocation_size = str->size_m * sizeof(char);
    char* fitted_buf = (char*) malloc(allocation_size + 1);
    if (!fitted_buf)
    {
        return -1;
    }
    memcpy(fitted_buf, str->data, str->size_m);
    free(str->data);
    str->data = fitted_buf;
    str->capacity_m = str->size_m;
    return 0;
    
}

//! Якщо new_size менший за поточний розмір -- просто
//! відкидає зайві символи (зменшуючи size_m). Якщо
//! більший -- збільшує фактичний розмір стрічки,
//! встановлюючи нові символи рівними sym.
//! За потреби, збільшує буфер.
//! Сподіваюся, різниця між розміром буфера та фактичним
//! розміром стрічки зрозуміла?
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_resize(my_str_t* str, size_t new_size, char sym)
{
    if (new_size <= str->size_m)
    {
        str->size_m = new_size;
        return 0;
    }
    size_t diff = new_size - str->size_m;
    while (diff)
    {
        if (my_str_pushback(str, sym))
        {
            return -1;
        }
        diff--;
    }
    return 0;
}

//!===========================================================================
//! Функції пошуку та порівняння
//!===========================================================================

static size_t my_str_cmp_pointers(const char* cstr1, const char* cstr2, size_t len1, size_t len2)
{
    size_t shorter_len = len1 <= len2 ? len1 : len2;
    for (size_t i = 0; i < shorter_len; i++)
    {
        char c1 = *(cstr1 + i), c2 = *(cstr2 + i);
        if (c1 > c2)
        {
            return 1;
        }
        if (c1 < c2)
        {
            return -1;
        }
    }
    if (len1 == len2)
    {
        return 0;
    }
    return len1 > len2 ? 1 : -1;
}

//! Знайти першу підстрічку в стрічці, повернути номер її
//! початку або (size_t)(-1), якщо не знайдено. from -- місце, з якого починати шукати.
//! Якщо більше за розмір -- вважати, що не знайдено.
size_t my_str_find(const my_str_t* str, const my_str_t* tofind, size_t from)
{
    if (from >= str->size_m)
    {
        return (size_t)(-1);
    }
    if (str->size_m < tofind->size_m)
    {
        return (size_t)(-2);
    }
    size_t endpoint = str->size_m - tofind->size_m;
    for (size_t i = from; i <= endpoint; i++)
    {
        for (size_t j = 0; j < tofind->size_m; j++)
        {
            if (my_str_getc(str, i + j) != my_str_getc(tofind, j))
            {
                break;
            }
            if (j == tofind->size_m - 1)
            {
                return i;
            }
        }
    }
    return (size_t)(-1);
}


//! Порівняти стрічки, повернути 0, якщо рівні (за вмістом!)
//! -1 (або інше від'ємне значення), якщо перша менша,
//! 1 (або інше додатне значення) -- якщо друга.
//! Поведінка має бути такою ж, як в strcmp.
int my_str_cmp(const my_str_t* str1, const my_str_t* str2)
{
    size_t len1 = str1->size_m, len2 = str2->size_m;
    return my_str_cmp_pointers(str1->data, str2->data, len1, len2);
}

//! Порівняти стрічку із С-стрічкою, повернути 0, якщо рівні (за вмістом!)
//! -1 (або інше від'ємне значення), якщо перша менша,
//! 1 (або інше додатне значення) -- якщо друга.
//! Поведінка має бути такою ж, як в strcmp.
int my_str_cmp_cstr(const my_str_t* str1, const char* cstr2)
{
    size_t len1 = str1->size_m, len2 = my_str_len(cstr2);
    return my_str_cmp_pointers(str1->data, cstr2, len1, len2);
}

//! Знайти перший символ в стрічці, повернути його номер
//! або (size_t)(-1), якщо не знайдено. from -- місце, з якого починати шукати.
//! Якщо більше за розмір -- вважати, що не знайдено.
size_t my_str_find_c(const my_str_t* str, char tofind, size_t from);

//! Знайти символ в стрічці, для якого передана
//! функція повернула true, повернути його номер
//! або (size_t)(-1), якщо не знайдено:
size_t my_str_find_if(const my_str_t* str, int (*predicat)(int));

//!===========================================================================
//! Ввід-вивід
//!===========================================================================

//! Прочитати стрічку із файлу. Читає цілий файл.
//! Не давайте читанню вийти за межі буфера! За потреби --
//! збільшуйте буфер.
//! Рекомендую скористатися fgets().
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_read_file(my_str_t* str, FILE* file);

//! Аналог my_str_read_file, із stdin.
int my_str_read(my_str_t* str);

//! Записати стрічку в файл:
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_write_file(const my_str_t* str, FILE* file);

//! Записати стрічку на консоль:
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_write(const my_str_t* str, FILE* file);

//! На відміну від my_str_read_file(), яка читає до кінця файлу,
//! читає по вказаний delimiter, за потреби
//! збільшує стрічку.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_read_file_delim(my_str_t* str, FILE* file, char delimiter);

