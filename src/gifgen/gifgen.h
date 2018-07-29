#ifndef __GIFGEN_H
#define __GIFGEN_H
#include <stdint.h>
#include "colour.h"

void gifgen_start(char *filename, uint16_t width, uint16_t height, colour_t *palette);

void gifgen_add_frame(uint8_t *data, uint16_t width, uint16_t height);

void gifgen_finish(void);

#endif
