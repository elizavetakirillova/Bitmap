#include <stdio.h>
#include "bitmap.h"

int main()
{
    bitmap_t *ptr;
    bitmap_t *ptr1;
    
    printf("Created bitmap 0 with 7 bits - %d\n", create_bitmap(&ptr, 7));
    printf("Created bitmap 1 with 14 bits- %d\n", create_bitmap(&ptr1, 14));
    printf("Bitmap 0: ");
    show_bitmap(ptr);
    printf("Bitmap 1: ");
    show_bitmap(ptr1);
    printf("\n");
    
    printf("Bitmap 0 to default value 1 - %d\n", to_default_value(ptr, 1));
    printf("Bitmap 1 to default value 0 - %d\n", to_default_value(ptr1, 0));
    printf("Bitmap 0: ");
    show_bitmap(ptr);
    printf("Bitmap 1: ");
    show_bitmap(ptr1);
    printf("\n");
    printf("<< Wrong values >>\n");
    printf("To default wrong value 8 - %d\n", to_default_value(ptr, 8));
    printf("\n");
    
    printf("Set %d bit in bitmap 0 - %d\n", 2, set_bit(ptr, 2, 0));
    printf("Bitmap 0: ");
    show_bitmap(ptr);
    printf("\n");
    printf("Set %d bit in bitmap 1 - %d\n", 5, set_bit(ptr1, 5, 1));
    printf("Bitmap 1: ");
    show_bitmap(ptr1);
    printf("\n");
    printf("<< Wrong values >>\n");
    printf("Set %d bit in bitmap to the wrong value 5 - %d\n", 2, set_bit(ptr, 2, 5));
    printf("\n");
    
    bitmap_t *ptr2;
    printf("Clone bitmap 0 into new bitmap 2 - %d\n", clone_bitmap(&ptr2, ptr));
    printf("Bitmap 2: ");
    show_bitmap(ptr2);
    printf("\n");

    printf("Glue bitmap 2 and bitmap 0 - %d\n", glue_bitmap(ptr2, ptr));
    printf("Bitmap 2: ");
    show_bitmap(ptr2);
    printf("\n");

    printf("Get 2 bit from bitmap 2 -> 2 bit = %d\n", get_bit(ptr2, 2));
    printf("\n");
    printf("Get 5 bit from bitmap 2 -> 5 bit = %d\n", get_bit(ptr2, 5));
    printf("\n");
    printf("<< Wrong values >>\n");
    printf("Get wrong 105 bit from Bitmap 0 - %d\n", get_bit(ptr, 105));
    printf("\n");

    printf("Bitmap 0: ");
    show_bitmap(ptr);

    printf("Bitmap 1: ");
    show_bitmap(ptr1);
    printf("Compare bitmaps 0 and 1 - %d\n", compare_bitmaps_length(ptr, ptr1));
    printf("\n");
    
    printf("Bitmap 2: ");
    show_bitmap(ptr2);
    printf("Bitmap 1: ");
    show_bitmap(ptr1);
    printf("And op bitmaps 2 and 1 - %d\n", and_op(ptr2, ptr1));
    printf("\n");
    
    printf("Bitmap 2: ");
    show_bitmap(ptr2);
    printf("Bitmap 1: ");
    show_bitmap(ptr1);
    printf("\n");
    
    printf("Set %d bit in bitmap 2 to the 1 - %d\n", 11, set_bit(ptr2, 11, 1));
    printf("Set %d bit in bitmap 2 to the 1 - %d\n", 7, set_bit(ptr2, 7, 1));
    printf("Set %d bit in bitmap 1 to the 1 - %d\n", 13, set_bit(ptr1, 13, 1));
    printf("Set %d bit in bitmap 1 to the 1 - %d\n", 4, set_bit(ptr1, 4, 1));
    printf("\n");

    printf("Bitmap 2: ");
    show_bitmap(ptr2);
    printf("Bitmap 1: ");
    show_bitmap(ptr1);
    printf("Or op bitmaps 2 and 1 - %d\n", or_op(ptr2, ptr1));
    printf("\n");

    printf("Bitmap 2: ");
    show_bitmap(ptr2);
    printf("Bitmap 1: ");
    show_bitmap(ptr1);
    printf("Xor op bitmaps 2 and 1 - %d\n", xor_op(ptr2, ptr1));
    printf("\n");

    printf("Bitmap 2: ");
    show_bitmap(ptr2);
    printf("Bitmap 1: ");
    show_bitmap(ptr1);
    printf("Not op bitmap 1 - %d\n", not_op(ptr1));
    printf("\n");
    
    printf("Bitmap 1: ");
    show_bitmap(ptr1);
    printf("\n");

    printf("Copy bitmap 1 into 0  - %d\n", copy_bitmap(ptr, ptr1));
    printf("Bitmap 0: ");
    show_bitmap(ptr);
    printf("Bitmap 1: ");
    show_bitmap(ptr1);
    printf("Bitmap 2: ");
    show_bitmap(ptr2);
    printf("\n");

    printf("Add bit to bitmap 1 10 bits - %d\n", add_bit_to_bitmap(ptr1, 10));
    printf("Bitmap 1: ");
    show_bitmap(ptr1); 
    printf("\n");

    destroy_bits(ptr);
    destroy_bits(ptr1);
    destroy_bits(ptr2);

    return 0;
}
