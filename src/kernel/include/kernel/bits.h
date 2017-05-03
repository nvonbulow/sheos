#ifndef BITS_H
#define BITS_H

//Creates a value that contains exactly 'size' ones in binary
#define bit_mask(size) ((uint64_t)((((uint64_t)1) << (size)) - 1))
//Extracts the specified bits from the value
#define get_bits(in, start, size) (((in) >> (start)) & bit_mask(size + 1))
//Clears the bits starting at 'start' and ending at 'start + size' to zero
#define clear_bits(in, start, size) ((in) & ~(bit_mask(size) << (start)))
//Creates a value where the bits from 'start' to 'start + size' are set to 'value'
#define set_bits(in, start, size, value) (clear_bits(in, start, size) | (((value) & bit_mask(size)) << (start)))

#endif /* BITS_H */

