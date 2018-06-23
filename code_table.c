#include "code_table.h"
#include <stddef.h>
#include <stdio.h>

static size_t bitsize(size_t number);

void code_table_setup(code_table_t *table, uint8_t num_codes)
{
  *table = (code_table_t){0};
  // Two extra codes, for clear code and end of info code
  for(int i = 0; i < num_codes + 2; i++)
  {
    code_t new_code = (code_t){0};

    // Last two codes (CC and EOI) are special and have no length
    if(i < num_codes)
    {
      new_code = (code_t){
        .code_len = 1,
        .code[0] = i
      };
    }
    code_table_add(table, new_code);
  }
  // cc and eoi are the last two codes in the table
  table->cc_index = table->table_len - 2;
  table->eoi_index= table->table_len - 1;
}

void code_table_add(code_table_t *table, code_t code)
{
  if(table->table_len < MAX_NUM_CODES - 1)
  {
    printf("Adding code to table: row %u, code: ", table->table_len);
    for(size_t i = 0; i < code.code_len; i++)
    {
      printf("%u, ", code.code[i]);
    }
    printf("\r\n");

    table->data[table->table_len] = code;
    table->table_len += 1;
    table->code_bitlength = bitsize(table->table_len);
  }
  else
  {
    printf("Out of space in code table!\r\n");
  }
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
