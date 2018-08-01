#include "code_table.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t bitsize(size_t number);

void code_table_setup(code_table_t *table, uint8_t num_codes)
{
  *table = (code_table_t){0};
  code_t new_code;
  code_alloc(&new_code, MAX_CODE_LEN);

  // Two extra codes, for clear code and end of info code
  for(int i = 0; i < num_codes + 2; i++)
  {
    // Last two codes (CC and EOI) are special and have no length
    if(i < num_codes)
    {
      new_code.code_len = 1;
      new_code.code[0] = i;
    }
    else
    {
      new_code.code_len = 0;
    }
    code_table_add(table, &new_code);
  }
  // cc and eoi are the last two codes in the table
  table->cc_index = table->table_len - 2;
  table->eoi_index= table->table_len - 1;
  code_free(&new_code);
}

void code_table_add(code_table_t *table, code_t *code)
{
  if(table->table_len < MAX_NUM_CODES)
  {
    code_alloc(&(table->data[table->table_len]), code->code_len);
    memcpy(table->data[table->table_len].code, code->code, table->data[table->table_len].code_len);

    table->code_bitlength = bitsize(table->table_len);
    table->table_len += 1;
  }
  else
  {
    printf("Out of space in code table!\r\n");
  }
}

void code_table_free(code_table_t *table)
{
  for(size_t i = 0; i < table->table_len; i++)
  {
    code_free(&(table->data[i]));
  }
}

void code_alloc(code_t *code, uint16_t length)
{
  code->code_len = length;
  code->code = calloc(code->code_len, sizeof(uint8_t));
}

void code_free(code_t *code)
{
  free(code->code);
}

static size_t bitsize(size_t number)
{
  // http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogObvious
  size_t msb_position = 1;
  while (number >>= 1)
  {
    msb_position++;
  }
  return msb_position;
}
