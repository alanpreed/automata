#ifndef __CODE_TABLE_H
#define __CODE_TABLE_H

#include <stdint.h>

// TODO: support long codes for large files - should go up to 4096
// TODO: support running out of codes (using cc to regen table)
#define MAX_CODE_LEN 4096
#define MAX_NUM_CODES 4096

typedef struct {
  uint16_t code_len;
  uint8_t *code;
} code_t;

typedef struct{
  uint16_t table_len;
  // Number of bits required to store the largest code index
  uint16_t code_bitlength;
  // Location in table of clear code and end of info
  uint16_t cc_index;
  uint16_t eoi_index;
  // Array of arrays of numbers
  code_t data[MAX_NUM_CODES];
} code_table_t;

void code_table_setup(code_table_t *table, uint8_t num_codes);

void code_table_add(code_table_t *table, code_t *code);

void code_table_free(code_table_t *table);

void code_alloc(code_t *code, uint16_t length);

void code_free(code_t *code);

#endif
