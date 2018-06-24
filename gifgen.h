#ifndef __GIFGEN_H
#define __GIFGEN_H
#include "grid.h"
#include <stdint.h>

void gifgen_start(char *filename, uint16_t width, uint16_t height);

void gifgen_add_frame(uint8_t *data, uint16_t width, uint16_t height);

void gifgen_finish(void);

#endif