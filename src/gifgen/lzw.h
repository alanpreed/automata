#ifndef __LZW_H
#define __LZW_H

#include <stdint.h>

uint64_t lzw_compress_data(uint8_t *input, uint8_t **output, uint64_t length, uint8_t num_values);

#endif
