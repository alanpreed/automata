#include "lzw.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CODE_LEN 100
#define MAX_NUM_CODES 100

typedef struct {
  uint16_t code_len;
  uint8_t code[MAX_CODE_LEN];
} code_t;

typedef struct{
  uint16_t table_len;
  // Location in table of clear code and end of info
  uint16_t cc_index;
  uint16_t eoi_index;
  // Array of arrays of numbers
  code_t data[MAX_NUM_CODES];
} code_table_t;

static void code_table_setup(code_table_t *table, uint8_t num_codes);

static void code_table_add(code_table_t *table, code_t code);

void lzw_compress_data(uint8_t *input, uint16_t length, uint8_t num_values)
{
  code_table_t code_table;
  code_t input_buffer;

  size_t output_len = 100;

  uint8_t *output_codes = calloc(output_len, sizeof(uint8_t));
  uint8_t output_position = 0;
  uint8_t next_output_code = 0;

  code_table_setup(&code_table, num_values);

  // Start with clear code:
  output_codes[0] = code_table.cc_index;
  output_position++;

  for(int i = 0; i < length; i++)
  {
    // Read input byte into buffer, and save previous buffer state so that it can be output if needed
    input_buffer.code[input_buffer.code_len] = input[i];
    input_buffer.code_len++;

    bool code_match = false;
    uint16_t code_table_location = 0;

    // Check each entry in code table to see if it matches input buffer
    for(int j = 0; j < code_table.table_len; j++)
    {
      code_t test_code = code_table.data[j];

      // Only check for a match if the code is the same length as the input buffer
      if(test_code.code_len == input_buffer.code_len)
      {
        code_match = true;
        for(size_t k = 0; k < input_buffer.code_len; k++)
        {
          if(test_code.code[k] != input_buffer.code[k])
          {
            code_match = false;
            break;
          }
        }
      }

      // If we've found a matching code, no need to keep searching the code table
      if(code_match)
      {
        next_output_code = j;
        break;
      }
    }

    // If no match found, add to code table and output code for buffer excluding this character
    if(!code_match)
    {
      code_table_add(&code_table, input_buffer);

      input_buffer = (code_t){0};
      // Last character isn't included in output code, so we need to go over it again
      i--;

      output_codes[output_position] = next_output_code;
      output_position++;
    }
    // If match was found, return this code if there are no more bytes. Otherwise continue reading
    if(i == length - 1)
    {
      output_codes[output_position] = next_output_code;
      output_position++;
    }
  }

  // Add end-of-info code
  output_codes[output_position] = code_table.eoi_index;
  output_position++;

  // Pack code stream
  printf("Final output code stream: ");
  for(size_t i = 0; i < output_position; i++)
  {
    printf("%u, ", output_codes[i]);
  }
  printf("\r\n");
}

static void code_table_setup(code_table_t *table, uint8_t num_codes)
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

static void code_table_add(code_table_t *table, code_t code)
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
  }
  else
  {
    printf("Out of space in code table!\r\n");
  }
}
