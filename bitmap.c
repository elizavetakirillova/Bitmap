#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//#define LEFT_TO_RIGHT
/* Коды ошибок */
typedef enum 
{
    ok = 0,
    out_of_range,
    ptr_null,
    first_is_strict_bigger,
    first_is_bigger,
    second_is_strict_bigger,
    second_is_bigger,
    unequal,
    other_error
} myError_e;

typedef struct bits 
{
    union 
    {
        unsigned char raw;
        struct 
        {
            unsigned char b0:1,
                          b1:1,
                          b2:1,
                          b3:1,
                          b4:1,
                          b5:1,
                          b6:1,
                          b7:1;
        };
    };
} bits_t;

typedef struct bitmap 
{
    bits_t *bits_arr;
    unsigned int bits;
} bitmap_t;

/* Перевод из битов в байты */
static int bits_to_byte(int bits)
{
    if (bits%8 == 0)
    {
        return bits/8;
    }
        
    return bits/8 + 1;
}

/* Перевод из байтов в биты */
static int bytes_to_bits(int bytes) 
{
    return bytes * 8;
}

/* Принимает указатель на структуру bitmap и номер бита.
Возвращает значение данного бита */
int get_bit(bitmap_t *ptr, int num_bits)
{
    if (ptr == NULL)
    {
        return ptr_null;
    }

    if (num_bits > bits_to_byte(ptr->bits) * sizeof(bitmap_t *))
    {
        return out_of_range;
    }

    int num_bit = num_bits%8;
    int val_bit = 0;

    switch(num_bit)
    {
        case 0:
            val_bit = ptr->bits_arr[num_bits/8].b0;
            break;
        case 1:
            val_bit = ptr->bits_arr[num_bits/8].b1;
            break;
        case 2:
            val_bit = ptr->bits_arr[num_bits/8].b2;
            break;
        case 3:
            val_bit = ptr->bits_arr[num_bits/8].b3;
            break;
        case 4:
            val_bit = ptr->bits_arr[num_bits/8].b4;
            break;
        case 5:
            val_bit = ptr->bits_arr[num_bits/8].b5;
            break;
        case 6:
            val_bit = ptr->bits_arr[num_bits/8].b6;
            break;
        case 7:
            val_bit = ptr->bits_arr[num_bits/8].b7;
            break;
        default:
            return other_error;
            break;
    }

    return val_bit;
}

/* Принимает указатель на структуру bitmap и значение для установления значения всех
битов (0/1).Возвращает код успешного выполнения/ошибки типа myError. Инициализирует
структуру bitmap значением 0/1 */ 
myError_e to_default_value(bitmap_t *ptr, int val)
{
    if (ptr == NULL)
    {
        return ptr_null;
    }
    
    if (val == 0)
    {
        for(int i = 0; i < (bits_to_byte(ptr->bits) * (sizeof(bitmap_t *))); i++)
        {
            ptr->bits_arr[i/8].raw &= ~(unsigned char)(1 << i%8);
        }
        return ok;
    }
    else if (val == 1)
    {
        for(int i = 0; i < (bits_to_byte(ptr->bits) * (sizeof(bitmap_t *))); i++)
        {
            ptr->bits_arr[i/8].raw |= (unsigned char)(1 << i%8);
        }
        return ok;
    }
    
    return other_error;
}

/* Принимает указатель на структуру bitmap. Возвращает код успешного 
выполнения/ошибки типа myError. Выводит на экран значения bitmap */ 

myError_e show_bitmap(bitmap_t *ptr) 
{
    if (ptr == NULL)
    {
        return ptr_null;
    }
    #if defined RIGHT_TO_LEFT
     
    for (int i = (bits_to_byte(ptr->bits) - 1); i >= 0; i--) 
    {
        printf("%d%d%d%d%d%d%d%d", ptr->bits_arr[i].b7, ptr->bits_arr[i].b6, 
        ptr->bits_arr[i].b5, ptr->bits_arr[i].b4, ptr->bits_arr[i].b3,
        ptr->bits_arr[i].b2, ptr->bits_arr[i].b1, ptr->bits_arr[i].b0);
    }
    #else
    for (int i = 0; i < bits_to_byte(ptr->bits); i++) 
    {
        printf("%d%d%d%d%d%d%d%d", ptr->bits_arr[i].b0, ptr->bits_arr[i].b1, 
        ptr->bits_arr[i].b2, ptr->bits_arr[i].b3, ptr->bits_arr[i].b4,
        ptr->bits_arr[i].b5, ptr->bits_arr[i].b6, ptr->bits_arr[i].b7);
    }
    #endif
    
    printf("\n");
    
    return ok;
}

/* Принимает указатель на структуру bitmap, номер бита, который необходимо изменить 
(num), и значение val, на которое необходимо изменить (0/1). Возвращает код 
успешного выполнения/ошибки типа myError. Изменяет num-й бит в val 0/1 */ 
myError_e set_bit(bitmap_t *ptr, int num, int val) 
{
    if (ptr == NULL)
    {
        return ptr_null;
    }
        
    if (num > bits_to_byte(ptr->bits) * sizeof(*ptr))
    {
        return out_of_range;
    }

    if (val == 1) 
    {
        ptr->bits_arr[num/8].raw |= (unsigned char)(1 << num%8);
    }
    else if (val == 0)
    {
        ptr->bits_arr[num/8].raw &= ~(unsigned char)(1 << num%8);
    }
    else
    {
        return other_error;
    }
    
    return ok;
}

/* Принимает два указателя на структуру bitmap. Возвращает код успешного выполнения 
/ошибки типа myError. Сравнение двух структур данных: равно, строго больше, больше, 
строго меньше, меньше */
myError_e compare_bitmaps_length(bitmap_t *ptr_1, bitmap_t *ptr_2) 
{
    if (ptr_1 == NULL || ptr_2 == NULL)
    {
        return ptr_null;
    }

    if (ptr_1->bits == ptr_2->bits)
    {
        return ok;
    }

    if (ptr_1->bits > ptr_2->bits)
    {
        return first_is_strict_bigger;
    }
        
    if (ptr_1->bits >= ptr_2->bits)
    {
        return first_is_bigger;
    }
    
    if (ptr_1->bits < ptr_2->bits)
    {
        return second_is_strict_bigger;
    }
    
    if (ptr_1->bits <= ptr_2->bits)
    {
        return second_is_bigger;
    }
}

/* Принимает два указателя на структуру bitmap. Возвращает код успешного выполнения 
/ошибки типа myError. Выполнение побитовой операции AND для двух bitmap */
myError_e and_op(bitmap_t *ptr_1, bitmap_t *ptr_2) 
{
    if (ptr_1 == NULL || ptr_2 == NULL)
    {
        return ptr_null;
    }
    
    if (compare_bitmaps_length(ptr_1, ptr_2) == 0)
    {
        for(int i = 0; i < bits_to_byte(ptr_1->bits); i++)
        {
            ptr_1->bits_arr[i].raw &= ptr_2->bits_arr[i].raw;
        }  
        return ok;
    }
    
    return unequal;
}

/* Принимает два указателя на структуру bitmap. Возвращает код успешного выполнения 
/ошибки типа myError. Выполнение побитовой операции OR для двух bitmap */
myError_e or_op(bitmap_t *ptr_1, bitmap_t *ptr_2)
{
    if (ptr_1 == NULL || ptr_2 == NULL)
    {
        return ptr_null;
    }
    
    if (compare_bitmaps_length(ptr_1, ptr_2) == 0)
    {
        for(int i = 0; i < bits_to_byte(ptr_1->bits); i++)
        {
            ptr_1->bits_arr[i].raw |= ptr_2->bits_arr[i].raw;
        }  
        return ok;
    }
    
    return unequal;
}

/* Принимает два указателя на структуру bitmap. Возвращает код успешного выполнения 
/ошибки типа myError. Выполнение побитовой операции XOR для двух bitmap */
myError_e xor_op(bitmap_t *ptr_1, bitmap_t *ptr_2)
{
    if (ptr_1 == NULL || ptr_2 == NULL)
    {
        return ptr_null;
    }
    
    if (compare_bitmaps_length(ptr_1, ptr_2) == 0)
    {
        for(int i = 0; i < bits_to_byte(ptr_1->bits); i++)
        {
            ptr_1->bits_arr[i].raw ^= ptr_2->bits_arr[i].raw;
        }  
        return ok;
    }
    
    return unequal;
}

/* Принимает указатель на структуру bitmap. Возвращает код успешного выполнения 
/ошибки типа myError. Выполнение побитовой оператоции NOT для bitmap */
myError_e not_op(bitmap_t *ptr) 
{
    if (ptr == NULL)
    {
        return ptr_null;
    }
    
    for(int i = 0; i < bits_to_byte(ptr->bits); i++)
    {
        ptr->bits_arr[i].raw = ~ptr->bits_arr[i].raw;
    }  
    
    return ok;
}



/* Принимает указатель на создаваемую структуру bitmap и количество битов.
Возвращает код успешного выполнения/ошибки типа myError. Выделяет память под указатель.*/
myError_e bitmap_new(bitmap_t **ptr_new)
{
    if (ptr_new == NULL)
    {
        return ptr_null;
    }

    *ptr_new = (bitmap_t *)calloc(1, sizeof(bitmap_t*));

    return ok;
}

/* Принимает указатель на структуру bitmap. Возвращает код успешного выполнения
/ошибки типа myError. Выделяет запрошенный пользователем объем памяти под bits */ 
myError_e calloc_bits(bitmap_t *ptr)
{
    if (ptr == NULL)
    {
        return ptr_null;
    }
    
    ptr->bits_arr = calloc(bits_to_byte(ptr->bits), sizeof(*ptr->bits_arr));
    
    return ok;
}

/* Принимает указатеaль на создаваемую структуру bitmap и количество битов bits. 
Возвращает код успешного выполнения/ошибки типа myError. Создает новую структуру 
bitmap c количеством бит bits */
myError_e create_bitmap(bitmap_t **ptr_new, int bits)
{
    if (ptr_new == NULL)
    {
        return ptr_null;
    }
    
    if (bits == 0)
    {
        return other_error;
    }

    bitmap_new(ptr_new);

    (*ptr_new)->bits = bytes_to_bits(bits_to_byte(bits));

    calloc_bits(*ptr_new);
    
    return ok;
}

/* Принимает два указателя на структуру bitmap. Возвращает код успешного выполнения
/ошибки типа myError. Копирует содержимое одной структуры в другую*/ 
myError_e copy_bitmap(bitmap_t *ptr, bitmap_t *ptr_copied) 
{
    if (ptr == NULL || ptr_copied == NULL)
    {
        return ptr_null;
    }
    
    for(int i = 0; i < bits_to_byte(ptr_copied->bits); i++)
    {
        ptr->bits_arr[i].raw = ptr_copied->bits_arr[i].raw;
    }  
    return ok;
}

/* Принимает два указателя на структуру bitmap. Возвращает код успешного выполнения
/ошибки типа myError. Клонирует содержимое одной структуры в другую */ 
myError_e clone_bitmap(bitmap_t **ptr_clone, bitmap_t *ptr)
{
    myError_e myError;
    
    if (ptr == NULL && ptr_clone == NULL)
    {
        return ptr_null;
    }
    
    *ptr_clone = NULL;

    if ((myError = create_bitmap(ptr_clone, ptr->bits)) != ok)
    {
        return myError;
    }
    
    if ((myError = copy_bitmap(*ptr_clone, ptr)) != ok)
    {
        return myError;
    }
    
    return ok;
}

/* Принимает указатель на структуру bitmap. Возвращает код успешного выполнения
/ошибки типа myError. Увеличивает количество памяти выделяемой под структуру bitmap */ 
myError_e realloc_bits(bitmap_t *ptr, int bits)
{
    if (ptr == NULL)
    {
        return ptr_null;
    }
    
    ptr->bits = bits;

    ptr->bits_arr = realloc(ptr->bits_arr, (bits_to_byte(bits) * sizeof(*ptr->bits_arr)));
    
    return ok;
}

/* Принимает два указателя на структуру bitmap. Возвращает код успешного выполнения
/ошибки типа myError. Соединяет две структуры вместе */ 
myError_e glue_bitmap(bitmap_t *ptr_1, bitmap_t *ptr_2)
{   
    if (ptr_1 == NULL || ptr_2 == NULL)
    {
        return ptr_null;
    }

    int offset_ptr_1 = bits_to_byte(ptr_1->bits);
    realloc_bits(ptr_1,(ptr_1->bits+ptr_2->bits));
    
    for(int i = 0; i < bits_to_byte(ptr_2->bits); i++)
    {
        ptr_1->bits_arr[i + offset_ptr_1].raw = ptr_2->bits_arr[i].raw;
    }
    
    return ok;
}

/* Принимает указатель на структуру bitmap и количество бит bits. Возвращает код 
успешного выполнения/ошибки типа myError. Добавляет bits бит в сруктуру bitmap */ 
myError_e add_bit_to_bitmap(bitmap_t *ptr_1, int bits)
{
    if (ptr_1 == NULL)
    {
        return ptr_null;
    }

    realloc_bits(ptr_1, (ptr_1->bits+(bytes_to_bits(bits_to_byte(bits)))));

    return ok;
}

/* Принимает указатель на структуру bitmap. Возвращает код успешного выполнения
/ошибки типа myError. Освобождает память, выделенную под указатель bitmap */ 
myError_e destroy_bits(bitmap_t *ptr)
{
    if (ptr == NULL)
    {
        return ptr_null;
    }
    
    for (int i = 0; i < bits_to_byte(ptr->bits) - (bits_to_byte(ptr->bits) - 1); i++) 
    {
        free(ptr->bits_arr + i);
    }

    free (ptr);
    return ok;
}
