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

int get_bit(
	bitmap_t *ptr, 
	int num_bits);

myError_e to_default_value(
	bitmap_t *ptr, 
	int val);

myError_e show_bitmap(bitmap_t *ptr);

myError_e set_bit(
	bitmap_t *ptr, 
	int num, 
	int val);

myError_e compare_bitmaps_length(
	bitmap_t *ptr_1, 
	bitmap_t *ptr_2);

myError_e and_op(
	bitmap_t *ptr_1, 
	bitmap_t *ptr_2);

myError_e or_op(
	bitmap_t *ptr_1, 
	bitmap_t *ptr_2);

myError_e xor_op(
	bitmap_t *ptr_1, 
	bitmap_t *ptr_2);

myError_e not_op(bitmap_t *ptr);

myError_e create_bitmap(
	bitmap_t **ptr_new, 
	int bits);

myError_e copy_bitmap(
	bitmap_t *ptr, 
	bitmap_t *ptr_copied);

myError_e clone_bitmap(
	bitmap_t **ptr_clone, 
	bitmap_t *ptr);

myError_e glue_bitmap(
	bitmap_t *ptr_1, 
	bitmap_t *ptr_2);

myError_e add_bit_to_bitmap(
	bitmap_t *ptr_1, 
	int bits);

myError_e destroy_bits(bitmap_t *ptr);