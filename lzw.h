#ifndef __LZW_H
#define __LZW_H

#include <stdint.h>

void lzw_compress_data(uint8_t *input, uint16_t length, uint8_t num_values);

#endif