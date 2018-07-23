#ifndef __LZW_H
#define __LZW_H

#include <stdint.h>

uint16_t lzw_compress_data(uint8_t *input, uint8_t *output, uint16_t length, uint8_t num_values);

#endif
