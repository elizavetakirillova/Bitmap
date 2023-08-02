#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "bitmap.h"


int bits_to_byte(int bits)
{
    if (bits%8 == 0)
    {
        return bits/8;
    }
        
    return bits/8 + 1;
}

int bytes_to_bits(int bytes) 
{
    return bytes * 8;
}

myError_e realloc_bitmap(bitmap_t **ptr, int bits)
{
    if (ptr == NULL)
    {
        return ptr_null;
    }
    
    *ptr = realloc(*ptr, ( bits_to_byte(bits) * sizeof((*ptr)->bits_arr)));

    return ok;
}

int input_value(void)
{
    int w = 0;
    int value;
        while (w != 1)     
        {
            if((scanf("%d",&value)) == 1)
            {
                w = 1;
            }else {
            getchar();
            }
        }
    return value;
}

unsigned char invert(unsigned char number) 
{        
    int base = 256;

    unsigned char  res = 0;
    while (number != 0) 
    {
        res += (number & 1) * (base >>= 1);
        number >>= 1;
    }

    return res;
}

int search_num_bit (int num)
{
    int bit;
    int i;
    int y;
    int count_bit;
    for(i = 0; i < bytes_to_bits(bits_to_byte(log2(num))); i++)
    {
        bit = (num >> i) & 1u;
        if (bit == 1)
        {
            break;
        }
    }
    for(y = bytes_to_bits(bits_to_byte(log2(num)));y > 0 ;y--)
    {
        bit = (num >> y) & 1u;
        if (bit == 1)
        {
            break;
        }
    }

    count_bit = y - i;
    return count_bit;
}

int num_to_bytes(int num, int x)
{
    num = num << (bytes_to_bits(bits_to_byte((int)log2(num))))-(int)(log2(num)+1);
    unsigned char *s = (char *)(&num);
    return s[x];
    
}

int main()
{   
    int count_bitmap = 0;
    bitmap_t myBitmap[100];
    bitmap_t *ptr = myBitmap;
    int number_bitmap = 0;
    int number_bitmap_2 = 0;
    int val_bit = 0;
    int num_bit = 0;
    int number_menu = 0;
    while (1)
    {   
        printf( "(1)Create bitmap\n"
                "(2)Create a bitmap from a number\n"
                "(3)Check bitmap\n"
                "(4)Set the value to bits\n"
                "(5)Show all bitmaps\n"
                "(6)AND\n"
                "(7)OR\n"
                "(8)XOR\n"
                "(9)NOT\n"
                "(10)Copy\n"
                "(11)Clone\n"
                "(12)Get bit\n"
                "(13)Glue bitmap\n"
                "(14)Add bit to bitmap\n"
                "(15)Exit\n");
        number_menu = input_value();
        switch (number_menu)
        {
        case 1:
            printf("Specify the number of bits\n");

            int size_bitmap = 0;
            size_bitmap = input_value();

            create_bitmap((&ptr)+count_bitmap, size_bitmap);
            printf("An %d-bit bitmap was created\n", ((&ptr)[count_bitmap]->bits));
            
            count_bitmap++;
            break;
        case 2:
            int value = input_value();
            create_bitmap((&ptr)+count_bitmap, (log2(value)+1));
            for (int f = 0; f < bits_to_byte((unsigned)(log2(value)+1)); f++)
            {
                (&ptr)[count_bitmap]->bits_arr[f].raw = invert(num_to_bytes(value, ((bits_to_byte((unsigned)(log2(value)+1))-1)-f)));
                
            }
            printf("A %d-bit bitmap was created from the number %d\n", ((&ptr)[count_bitmap]->bits), value);

            count_bitmap++;
            break;
        case 3:
            printf("Bitmap number\n");
            number_bitmap = input_value();
            if (number_bitmap >= count_bitmap || number_bitmap <= -1){
                printf("Bitmap not found\n");
                break;
            }

            show_bitmap((&ptr)[number_bitmap]);
            break;
        case 4:
            printf("Bitmap number\n");
            number_bitmap = input_value();
            if (number_bitmap >= count_bitmap || number_bitmap <= -1){
                printf("Bitmap not found\n");
                break;
            }

            printf("Bit number\n");
            num_bit = input_value();
            if (num_bit >= (int)((&ptr)[number_bitmap]->bits) || num_bit <= -1){
                printf("Specify bits from 0 to %d\n", ((&ptr)[number_bitmap]->bits)-1);
                break;
            }

            printf("Bit value\n");
            val_bit = input_value();
            if ((val_bit <= -1) || (val_bit >= 2)){
                printf("You can only use 0 or 1\n");
                break;
            }

            set_bit((&ptr)[number_bitmap], num_bit, val_bit);
            
            printf("Bitmap %d has been changed\n", number_bitmap);
            break;
        
        case 5:
            if(count_bitmap == 0){
                printf("No bitmaps\n");
                break;
            }

            for(int i = 0; i < count_bitmap; i++)
            {
                printf("bitmap %d - ", i);
                show_bitmap((&ptr)[i]);
            }
            break;
        case 6:
            printf("The first bitmap\n");
            number_bitmap = input_value();
            if (number_bitmap >= count_bitmap || number_bitmap <= -1){
                printf("bitmap not found\n");
                break;
            }

            printf("The second bitmap\n");
            number_bitmap_2 = input_value();
            if (number_bitmap_2 >= count_bitmap || number_bitmap_2 <= -1){
                printf("bitmap not found\n");
                break;
            }

            and_op((&ptr)[number_bitmap], (&ptr)[number_bitmap_2]);
            
            printf("Bitmap %d has been changed\n", number_bitmap);
            break;
        
        case 7:
            printf("The first bitmap\n");
            number_bitmap = input_value();
            if (number_bitmap >= count_bitmap || number_bitmap <= -1){
                printf("bitmap not found\n");
                break;
            };

            printf("The second bitmap\n");
            number_bitmap_2 = input_value();
            if (number_bitmap_2 >= count_bitmap || number_bitmap_2 <= -1){
                printf("bitmap not found\n");
                break;
            }

            or_op((&ptr)[number_bitmap], (&ptr)[number_bitmap_2]);
            
            printf("Bitmap %d has been changed\n", number_bitmap);
            break;

        case 8:
            printf("The first bitmap\n");
            number_bitmap = input_value();
            if (number_bitmap >= count_bitmap || number_bitmap <= -1){
                printf("bitmap not found\n");
                break;
            };
            printf("The second bitmap\n");
            number_bitmap_2 = input_value();
            if (number_bitmap_2 >= count_bitmap || number_bitmap_2 <= -1){
                printf("bitmap not found\n");
                break;
            }
            
            xor_op((&ptr)[number_bitmap], (&ptr)[number_bitmap_2]);
            
            printf("Bitmap %d has been changed\n", number_bitmap);
            break;

        case 9:
            printf("Bitmap number\n");
            number_bitmap = input_value();
            if (number_bitmap >= count_bitmap || number_bitmap <= -1){
                printf("bitmap not found\n");
                break;
            }
            not_op((&ptr)[number_bitmap]);

            printf("Bitmap %d has been changed\n", number_bitmap);
            break;

        case 10:
            printf("The number of the bitmap to which you are copying\n");
            number_bitmap = input_value();
            if (number_bitmap >= count_bitmap || number_bitmap <= -1){
                printf("bitmap not found\n");
                break;
            }

            printf("Which bitmap are you copying\n");
            number_bitmap_2 = input_value();
            if (number_bitmap_2 >= count_bitmap || number_bitmap_2 <= -1){
                printf("bitmap not found\n");
                break;
            }

            copy_bitmap((&ptr)[number_bitmap], (&ptr)[number_bitmap_2]);

            printf("Bitmap %d has been changed\n", number_bitmap);
            break;
        case 11:
            printf("Bitmap number\n");
            number_bitmap = input_value();
            if (number_bitmap >= count_bitmap || number_bitmap <= -1){
                printf("bitmap not found\n");
                break;
            }

            clone_bitmap((&ptr)+count_bitmap, (&ptr)[number_bitmap]);

            
            printf("A clone of the %d bitmap was created\n", number_bitmap);
            count_bitmap++;
            break;
        
        case 12:
            printf("Bitmap number\n");
            number_bitmap = input_value();
            if (number_bitmap >= count_bitmap || number_bitmap <= -1){
                printf("bitmap not found\n");
                break;
            }

            printf("Bit number\n");
            num_bit = input_value();
            if (num_bit >= (int)((&ptr)[number_bitmap]->bits) || num_bit <= -1){
                printf("Specify bits from 0 to %d\n", ((&ptr)[number_bitmap]->bits)-1);
                break;
            }
            printf("%d bits in %d bitmap = %d\n", num_bit, number_bitmap, get_bit((&ptr)[number_bitmap], num_bit));
            break;

        case 13:
            printf("The first bitmap\n");
            number_bitmap = input_value();
            if (number_bitmap >= count_bitmap || number_bitmap <= -1){
                printf("bitmap not found\n");
                break;
            }

            printf("The second bitmap\n");
            number_bitmap_2 = input_value();
            if (number_bitmap_2 >= count_bitmap || number_bitmap_2 <= -1){
                printf("bitmap not found\n");
                break;
            }
            glue_bitmap((&ptr)[number_bitmap], (&ptr)[number_bitmap_2]);

            printf("Combined two bitmaps %d with %d", number_bitmap, number_bitmap_2);
            break;

        case 14:
            printf("Bitmap number\n");
            number_bitmap = input_value();
            if (number_bitmap >= count_bitmap || number_bitmap <= -1){
                printf("bitmap not found\n");
                break;
            }
            
            printf("Specify the number of bits\n");
            size_bitmap = input_value();
            if (size_bitmap < -(int)((&ptr)[number_bitmap]->bits)){
                printf("Min number bit = %d\n", -((&ptr)[number_bitmap]->bits)+8);
                break;
            }
            add_bit_to_bitmap((&ptr)[number_bitmap], size_bitmap);

            printf("Bitmap %d has been changed\n", number_bitmap);
            break;
        case 15:

            for(int i = 0; i < count_bitmap; i++)
            {
                destroy_bits((&ptr)[i]);
            }
            return 0;
            break;

        
        
        default:
            break;
        }
    }


    return 0;
}